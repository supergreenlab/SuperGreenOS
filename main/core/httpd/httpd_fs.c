/*
 * Copyright (C) 2019  SuperGreenLab <towelie@supergreenlab.com>
 * Author: Constantin Clauzel <constantin.clauzel@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "esp_err.h"

#include "../log/log.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "esp_http_server.h"

#define FILE_BASE_PATH "/spiffs"

/* Max length a file path can have on storage */
#define FILE_PATH_MAX (ESP_VFS_PATH_MAX + CONFIG_SPIFFS_OBJ_NAME_LEN)

/* Scratch buffer size */
#define FILE_BUFSIZE  8192
char file_buffer[FILE_BUFSIZE] = {0};

#define MAX_FILE_SIZE (15*1024)
#define MAX_FILE_SIZE_STR "15KB"

/* Send HTTP response with a run-time generated html consisting of
 * a list of all files and folders under the requested path */
static esp_err_t http_resp_dir_html(httpd_req_t *req)
{
    char fullpath[FILE_PATH_MAX];
    char entrysize[16];
    const char *entrytype;

    DIR *dir = NULL;
    struct dirent *entry;
    struct stat entry_stat;

    /* Retrieve the base path of file storage to construct the full path */
    strcpy(fullpath, FILE_BASE_PATH);

    /* Concatenate the requested directory path */
    strcat(fullpath, &(req->uri[3]));
    dir = opendir(fullpath);
    const size_t entrypath_offset = strlen(fullpath);

    ESP_LOGI(SGO_LOG_NOSEND, "http_resp_dir_html %s", fullpath);

    if (!dir) {
        /* If opening directory failed then send 404 server error */
        httpd_resp_send_404(req);
        return ESP_OK;
    }

    httpd_resp_set_type(req, "text/plain");
    /* Iterate over all files / folders and fetch their names and sizes */
    while ((entry = readdir(dir)) != NULL) {
        entrytype = (entry->d_type == DT_DIR ? "directory" : "file");

        strncpy(fullpath + entrypath_offset, entry->d_name, sizeof(fullpath) - entrypath_offset);
        if (stat(fullpath, &entry_stat) == -1) {
            ESP_LOGE(SGO_LOG_NOSEND, "Failed to stat %s : %s", entrytype, entry->d_name);
            continue;
        }
        sprintf(entrysize, "%ld", entry_stat.st_size);
        ESP_LOGI(SGO_LOG_NOSEND, "Found %s : %s (%s bytes)", entrytype, entry->d_name, entrysize);

        /* Send chunk of HTML file containing table entries with file name and size */
        httpd_resp_sendstr_chunk(req, req->uri);
        httpd_resp_sendstr_chunk(req, entry->d_name);
        if (entry->d_type == DT_DIR) {
            httpd_resp_sendstr_chunk(req, "/");
        }
        httpd_resp_sendstr_chunk(req, ";");
        httpd_resp_sendstr_chunk(req, entry->d_name);
        httpd_resp_sendstr_chunk(req, ";");
        httpd_resp_sendstr_chunk(req, entrytype);
        httpd_resp_sendstr_chunk(req, ";");
        httpd_resp_sendstr_chunk(req, entrysize);
        httpd_resp_sendstr_chunk(req, "\n");
    }
    closedir(dir);

    /* Send empty chunk to signal HTTP response completion */
    httpd_resp_sendstr_chunk(req, NULL);
    return ESP_OK;
}

#define IS_FILE_EXT(filename, ext) \
    (strcasecmp(&filename[strlen(filename) - sizeof(ext) + 1], ext) == 0)

/* Set HTTP response content type according to file extension */
static esp_err_t set_content_type_from_file(httpd_req_t *req)
{
    if (IS_FILE_EXT(req->uri, ".html")) {
        return httpd_resp_set_type(req, "text/html");
    } else if (IS_FILE_EXT(req->uri, ".jpeg")) {
        return httpd_resp_set_type(req, "image/jpeg");
    } else if (IS_FILE_EXT(req->uri, ".png")) {
        return httpd_resp_set_type(req, "image/png");
    } else if (IS_FILE_EXT(req->uri, ".yml")) {
        return httpd_resp_set_type(req, "application/x-yaml");
    } else if (IS_FILE_EXT(req->uri, ".gz")) {
        return httpd_resp_set_type(req, "application/x-gzip");
    }

    /* This is a limited set only */
    /* For any other type always set as plain text */
    return httpd_resp_set_type(req, "text/plain");
}

/* Send HTTP response with the contents of the requested file */
static esp_err_t http_resp_file(httpd_req_t *req)
{
    char filepath[FILE_PATH_MAX];
    FILE *fd = NULL;
    struct stat file_stat;

    /* Retrieve the base path of file storage to construct the full path */
    strcpy(filepath, FILE_BASE_PATH);

    /* Concatenate the requested file path */
    strcat(filepath, &(req->uri[3]));
    ESP_LOGI(SGO_LOG_NOSEND, "http_resp_file %s", filepath);
    if (stat(filepath, &file_stat) == -1) {
        ESP_LOGE(SGO_LOG_NOSEND, "Failed to stat file : %s", filepath);
        /* If file doesn't exist respond with 404 Not Found */
        httpd_resp_send_404(req);
        return ESP_OK;
    }

    ESP_LOGI(SGO_LOG_NOSEND, "Sending file : %s (%ld bytes)...", filepath, file_stat.st_size);
    set_content_type_from_file(req);
    httpd_resp_set_hdr(req, "Content-Encoding", "gzip");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");

    fd = fopen(filepath, "r");
    if (!fd) {
        ESP_LOGE(SGO_LOG_NOSEND, "Failed to read existing file : %s", filepath);
        /* If file exists but unable to open respond with 500 Server Error */
        httpd_resp_set_status(req, "500 Server Error");
        httpd_resp_sendstr(req, "Failed to read existing file!");
        return ESP_OK;
    }

    /* Retrieve the pointer to file_buffer buffer for temporary storage */
    size_t chunksize;
    do {
        /* Read file in chunks into the file_buffer buffer */
        chunksize = fread(file_buffer, 1, FILE_BUFSIZE, fd);
        ESP_LOGI(SGO_LOG_NOSEND, "%d", chunksize);

        /* Send the buffer contents as HTTP response chunk */
        if (httpd_resp_send_chunk(req, file_buffer, chunksize) != ESP_OK) {
            fclose(fd);
            ESP_LOGE(SGO_LOG_NOSEND, "File sending failed!");
            /* Abort sending file */
            httpd_resp_sendstr_chunk(req, NULL);
            /* Send error message with status code */
            httpd_resp_set_status(req, "500 Server Error");
            httpd_resp_sendstr(req, "Failed to send file!");
            return ESP_OK;
        }

        /* Keep looping till the whole file is sent */
    } while (chunksize != 0);

    /* Close file after sending complete */
    fclose(fd);
    ESP_LOGI(SGO_LOG_NOSEND, "File sending complete");

    /* Respond with an empty chunk to signal HTTP response completion */
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

/* Handler to download a file kept on the server */
esp_err_t download_get_handler(httpd_req_t *req)
{
	ESP_LOGI(SGO_LOG_NOSEND, "download_get_handler");
	// Check if the target is a directory
	if (req->uri[strlen(req->uri) - 1] == '/') {
		// In so, send an html with directory listing
		http_resp_dir_html(req);
	} else {
		// Else send the file
		http_resp_file(req);
	}
	return ESP_OK;
}

esp_err_t upload_post_handler(httpd_req_t *req)
{
	char filepath[FILE_PATH_MAX];
	FILE *fd = NULL;
	//struct stat file_stat;

	/* Skip leading "/upload" from URI to get filename */
	/* Note sizeof() counts NULL termination hence the -1 */
	const char *filename = req->uri + sizeof("/fs") - 1;

	/* Filename cannot be empty or have a trailing '/' */
	if (strlen(filename) == 0 || filename[strlen(filename) - 1] == '/') {
		ESP_LOGE(SGO_LOG_EVENT, "Invalid file name : %s", filename);
		/* Respond with 400 Bad Request */
		httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid file name");
		return ESP_FAIL;
	}

	/* Retrieve the base path of file storage to construct the full path */
	strcpy(filepath, FILE_BASE_PATH);

	/* Concatenate the requested file path */
	strcat(filepath, filename);
	/*if (!stat(filepath, &file_stat) == 0) {
		ESP_LOGE(SGO_LOG_EVENT, "File already exists : %s", filepath);
		httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "File already exists");
		return ESP_FAIL;
	}*/

	/* File cannot be larger than a limit */
	if (req->content_len > MAX_FILE_SIZE) {
		ESP_LOGE(SGO_LOG_EVENT, "File too large : %d bytes", req->content_len);
		/* Respond with 400 Bad Request */
		httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST,
				"File size must be less than " MAX_FILE_SIZE_STR " !");
		/* Return failure to close underlying connection else the
		 * incoming file content will keep the socket busy */
		return ESP_FAIL;
	}

	fd = fopen(filepath, "w");
	if (!fd) {
		ESP_LOGE(SGO_LOG_EVENT, "Failed to create file : %s", filepath);
		/* Respond with 500 Internal Server Error */
		httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to create file");
		return ESP_FAIL;
	}

	ESP_LOGI(SGO_LOG_EVENT, "Receiving file : %s...", filename);

	/* Retrieve the pointer to scratch buffer for temporary storage */
	char *buf = file_buffer;
	int received;

	/* Content length of the request gives
	 * the size of the file being uploaded */
	int remaining = req->content_len;

	while (remaining > 0) {

		ESP_LOGI(SGO_LOG_EVENT, "Remaining size : %d", remaining);
		/* Receive the file part by part into a buffer */
		if ((received = httpd_req_recv(req, buf, MIN(remaining, FILE_BUFSIZE))) <= 0) {
			if (received == HTTPD_SOCK_ERR_TIMEOUT) {
				/* Retry if timeout occurred */
				continue;
			}

			/* In case of unrecoverable error,
			 * close and delete the unfinished file*/
			fclose(fd);
			unlink(filepath);

			ESP_LOGE(SGO_LOG_EVENT, "File reception failed!");
			/* Respond with 500 Internal Server Error */
			httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to receive file");
			return ESP_FAIL;
		}

		/* Write buffer content to file on storage */
		if (received && (received != fwrite(buf, 1, received, fd))) {
			/* Couldn't write everything to file!
			 * Storage may be full? */
			fclose(fd);
			unlink(filepath);

			ESP_LOGE(SGO_LOG_EVENT, "File write failed!");
			/* Respond with 500 Internal Server Error */
			httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to write file to storage");
			return ESP_FAIL;
		}

		/* Keep track of remaining size of
		 * the file left to be uploaded */
		remaining -= received;
	}

	/* Close file upon upload completion */
	fclose(fd);
	ESP_LOGI(SGO_LOG_EVENT, "File reception complete");

	httpd_resp_sendstr(req, "File uploaded successfully");
	return ESP_OK;
}

esp_err_t init_spiffs(void) {
  ESP_LOGI(SGO_LOG_EVENT, "Initializing SPIFFS");

  esp_vfs_spiffs_conf_t conf = {
    .base_path = "/spiffs",
    .partition_label = NULL,
    .max_files = 5,
    .format_if_mount_failed = true
  };

  esp_err_t ret = esp_vfs_spiffs_register(&conf);
  if (ret != ESP_OK) {
    if (ret == ESP_FAIL) {
      ESP_LOGE(SGO_LOG_EVENT, "Failed to mount or format filesystem");
    } else if (ret == ESP_ERR_NOT_FOUND) {
      ESP_LOGE(SGO_LOG_EVENT, "Failed to find SPIFFS partition");
    } else {
      ESP_LOGE(SGO_LOG_EVENT, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
    }
    return ESP_FAIL;
  }

  size_t total = 0, used = 0;
  ret = esp_spiffs_info(NULL, &total, &used);
  if (ret != ESP_OK) {
    ESP_LOGE(SGO_LOG_EVENT, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    return ESP_FAIL;
  }

  ESP_LOGI(SGO_LOG_METRIC, "@FS total=%d, used=%d", total, used);
  return ESP_OK;
}
