/*
 * Copyright (C) 2023  SuperGreenLab <towelie@supergreenlab.com>
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

#include "api.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_http_client.h"

#include "mbedtls/platform.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/esp_debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"

#include "../core/log/log.h"

esp_err_t _http_event_handle(esp_http_client_event_t *evt) {
	switch(evt->event_id) {
		case HTTP_EVENT_ERROR:
			ESP_LOGI(SGO_LOG_NOSEND, "HTTP_EVENT_ERROR");
			break;
		case HTTP_EVENT_ON_CONNECTED:
			ESP_LOGI(SGO_LOG_NOSEND, "HTTP_EVENT_ON_CONNECTED");
			break;
		case HTTP_EVENT_HEADER_SENT:
			ESP_LOGI(SGO_LOG_NOSEND, "HTTP_EVENT_HEADER_SENT");
			break;
		case HTTP_EVENT_ON_HEADER:
			ESP_LOGI(SGO_LOG_NOSEND, "HTTP_EVENT_ON_HEADER");
			printf("%.*s", evt->data_len, (char*)evt->data);
			break;
		case HTTP_EVENT_ON_DATA:
			ESP_LOGI(SGO_LOG_NOSEND, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
			if (!esp_http_client_is_chunked_response(evt->client)) {
				printf("%.*s", evt->data_len, (char*)evt->data);
			}

			break;
		case HTTP_EVENT_ON_FINISH:
			ESP_LOGI(SGO_LOG_NOSEND, "HTTP_EVENT_ON_FINISH");
			break;
		case HTTP_EVENT_DISCONNECTED:
			ESP_LOGI(SGO_LOG_NOSEND, "HTTP_EVENT_DISCONNECTED");
			break;
	}
	return ESP_OK;
}

void https()
{
  uint32_t free_heap_size=0, min_free_heap_size=0;
  free_heap_size = esp_get_free_heap_size();
  min_free_heap_size = esp_get_minimum_free_heap_size(); 
  ESP_LOGI(SGO_LOG_NOSEND, "\n free heap size = %d \t  min_free_heap_size = %d \n", free_heap_size, min_free_heap_size); 


	esp_http_client_config_t config = {
		.url = "https://api2.supergreenlab.com/",
    .event_handler = _http_event_handle,
	};
	esp_http_client_handle_t client = esp_http_client_init(&config);
	esp_err_t err = esp_http_client_perform(client);

	if (err == ESP_OK) {
		ESP_LOGI(SGO_LOG_NOSEND, "Status = %d, content_length = %d",
				esp_http_client_get_status_code(client),
				esp_http_client_get_content_length(client));
	}
	esp_http_client_cleanup(client);
}
