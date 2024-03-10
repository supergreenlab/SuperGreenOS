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

#include <math.h>
#include "mqtt.h"
#include "mqtt_client.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "sodium/utils.h"
#include "mbedtls/sha256.h"

#include "../log/log.h"
#include "../kv/kv.h"
#include "../wifi/wifi.h"



bool connected = false;


#include "../cmd/cmd.h"




#include "../../sgl/sgl.h"

#include "mbedtls/aes.h"
#include "mbedtls/md.h"

static unsigned char key[16] = { 0 };

int generate_key_from_uuid(const char *uuid, unsigned char *key) {
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
  const size_t key_len = 16; // 128 bits

  mbedtls_md_init(&ctx);

  if (mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0) != 0) {
    return -1; // Handle error
  }

  mbedtls_md_starts(&ctx);
  mbedtls_md_update(&ctx, (const unsigned char *) uuid, strlen(uuid));
  mbedtls_md_finish(&ctx, key);

  mbedtls_md_free(&ctx);

  // Truncate the SHA-256 hash to 128 bits
  memset(key + key_len, 0, 32 - key_len);

  return 0;
}

int aes_encrypt_msg(const unsigned char *input, size_t input_len, unsigned char *output, const unsigned char *key) {
  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);

  if (mbedtls_aes_setkey_enc(&aes, key, 128) != 0) {
    return -1; // Handle error
  }

  // Note: Since we are using ECB mode, input_len must be a multiple of the block size (16 bytes).
  // If it's not, you'll need to pad the input to be a multiple of the block size.

  for (size_t i = 0; i < input_len; i += 16) {
    if (mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, input + i, output + i) != 0) {
      mbedtls_aes_free(&aes);
      return -1; // Handle error
    }
  }

  mbedtls_aes_free(&aes);
  return 0;
}

int aes_decrypt_msg(const unsigned char *input, size_t input_len, unsigned char *output, const unsigned char *key) {
  mbedtls_aes_context aes;
  mbedtls_aes_init(&aes);

  if (mbedtls_aes_setkey_dec(&aes, key, 128) != 0) {
    return -1; // Handle error
  }

  // Note: Since we are using ECB mode, input_len must be a multiple of the block size (16 bytes).
  // Ensure the encrypted input complies with this.

  for (size_t i = 0; i < input_len; i += 16) {
    if (mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, input + i, output + i) != 0) {
      mbedtls_aes_free(&aes);
      return -1; // Handle error
    }
  }

  mbedtls_aes_free(&aes);
  return 0;
}

void update_key() {
  char enckey[MAX_KVALUE_SIZE] = { 0 };
  get_broker_enckey(enckey, MAX_KVALUE_SIZE-1);
  if (strlen(enckey) == 0) {
    ESP_LOGI(SGO_LOG_NOSEND, "Empty encryption key");
    return;
  }
  if (generate_key_from_uuid(enckey, key) != 0) {
    ESP_LOGI(SGO_LOG_NOSEND, "Unable to generate key");
    return;
  }
}



#define MAX_REMOTE_CMD_LENGTH MAX_CMD_LENGTH-10 // keeps some space for the -r true parameter

static esp_mqtt_client_handle_t client;

static QueueHandle_t cmd;
static QueueHandle_t log_queue;

static int CMD_MQTT_CONNECTED = 1;
static int CMD_MQTT_FORCE_FLUSH = 2;

#define MAX_LOG_QUEUE_ITEMS 25
static uint8_t buf_out[MAX_QUEUE_ITEM_SIZE] = {0};



  typedef struct {
    int len;
    uint8_t buf_out[MAX_QUEUE_ITEM_SIZE];
  } ScreenCmd;

  static QueueHandle_t scr_queue;
  #define MAX_SCR_QUEUE_ITEMS 5

  static int CMD_MQTT_CHANGE_SCR_CHANNEL = 3;




static void subscribe_cmd() {
  char cmd_channel[MAX_KVALUE_SIZE] = {0};
  char client_id[MAX_KVALUE_SIZE] = {0};
  get_broker_clientid(client_id, sizeof(client_id) - 1);
  sprintf(cmd_channel, "%s.cmd", client_id);

  ESP_LOGI(SGO_LOG_NOSEND, "@MQTT subscribe_cmd %s", cmd_channel);
  esp_mqtt_client_subscribe(client, cmd_channel, 2);
}

static void parse_cmd(esp_mqtt_event_handle_t event) {
  if (event->data_len > MAX_REMOTE_CMD_LENGTH + 65) {
    ESP_LOGI(SGO_LOG_EVENT, "@MQTT Remote command string can't be larger that %d with signature", MAX_REMOTE_CMD_LENGTH + 65);
    return;
  }
  if (event->data_len < 66) {
    ESP_LOGI(SGO_LOG_EVENT, "@MQTT Remote command disabled: missing signing key");
    return;
  }
  if (hasstr(SIGNING_KEY)) {
    char signingKey[33] = {0};
    getstr(SIGNING_KEY, signingKey, 33);
    char hash[65] = {0};
    strncpy(hash, event->data, 64);
    char cmd[MAX_REMOTE_CMD_LENGTH + 1] = {0};
    strncpy(cmd, &(event->data[65]), event->data_len - 65);

    char cmdSeeded[MAX_REMOTE_CMD_LENGTH + 33 + 1] = {0};
    uint8_t localHashBin[32] = {0};
    sprintf(cmdSeeded, "%s:%s", signingKey, cmd);

    //ESP_LOGI(SGO_LOG_EVENT, "@MQTT Hash: %s - Cmd: %s", hash, cmd);
    mbedtls_sha256_context sha256_ctx;
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts_ret(&sha256_ctx, false);
    mbedtls_sha256_update_ret(&sha256_ctx, (uint8_t *)cmdSeeded, strlen(cmdSeeded));
    mbedtls_sha256_finish_ret(&sha256_ctx, localHashBin);

    char localHash[65] = {0};
    sodium_bin2hex(localHash, sizeof(localHash), localHashBin, sizeof(localHashBin));
    if (strncmp(localHash, hash, 64) != 0) {
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT Command signing check failed.");
      return;
    }

    execute_cmd(event->data_len - 65, cmd, true);
  } else {
    ESP_LOGI(SGO_LOG_EVENT, "@MQTT Remote command disabled: missing signign key");
  }
}





static void subscribe_scr() {
  char scr_channel[MAX_KVALUE_SIZE] = {0};
  char client_id[MAX_KVALUE_SIZE] = {0};
  get_broker_clientid(client_id, sizeof(client_id) - 1);
  sprintf(scr_channel, "%s/scrrep", client_id);

  ESP_LOGI(SGO_LOG_NOSEND, "@MQTT subscribe_scr %s", scr_channel);
  esp_mqtt_client_subscribe(client, scr_channel, 2);
}

static void process_scr_reply(esp_mqtt_event_handle_t event) {
  unsigned char strdec[MAX_QUEUE_ITEM_SIZE] = { 0 };
  if (aes_decrypt_msg((unsigned char*) event->data, event->data_len, strdec, key) == -1) {
    ESP_LOGE(SGO_LOG_NOSEND, "Unable to decrypt");
    return;
  }
  mqtt_message((const char*)strdec, event->data_len);
}



static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) {
  switch (event->event_id) {
    case MQTT_EVENT_BEFORE_CONNECT:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_BEFORE_CONNECT");
      break;
    case MQTT_EVENT_CONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_CONNECTED");
      connected = true;
      xQueueSend(cmd, &CMD_MQTT_CONNECTED, 0);
      break;
    case MQTT_EVENT_DISCONNECTED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_DISCONNECTED");
      connected = false;
      break;
    case MQTT_EVENT_SUBSCRIBED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
      break;
    case MQTT_EVENT_UNSUBSCRIBED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
      break;
    case MQTT_EVENT_PUBLISHED:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
      break;
    case MQTT_EVENT_DATA:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_DATA");

      
        if (event->topic_len > 6 && !strncmp(&(event->topic[event->topic_len-6]), "scrrep", 6)) {
          process_scr_reply(event);
        }
      

      
        if (event->topic_len > 3 && !strncmp(&(event->topic[event->topic_len-3]), "cmd", 3)) {
          parse_cmd(event);
        }
      

      break;
    case MQTT_EVENT_ERROR:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_ERROR");
      break;
    case MQTT_EVENT_ANY:
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT MQTT_EVENT_ANY");
      break;
  }
  return ESP_OK;
}

static void mqtt_task(void *param) {
  int c;
  bool first_connect = true;

  uint64_t _chipmacid;
  esp_efuse_mac_get_default((uint8_t*) (&_chipmacid));

  char client_id[MAX_KVALUE_SIZE] = {0};
  get_broker_clientid(client_id, sizeof(client_id) - 1);
  if (strlen(client_id) == 0) {
    snprintf(client_id, sizeof(client_id)-1, "%llx", _chipmacid);
    set_broker_clientid(client_id);
  } else if (strlen(client_id) == 1 && client_id[0] == '-') {
    client_id[0] = 0;
  }
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Log clientid: %s", client_id);

  char log_channel[MAX_KVALUE_SIZE] = {0};
  get_broker_channel(log_channel, sizeof(log_channel) - 1);
  if (strlen(log_channel) == 0) {
    snprintf(log_channel, sizeof(log_channel)-1, "%s.log", client_id);
    set_broker_channel(log_channel);
  }
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Log channel: %s", log_channel);

  
    char scr_channel[MAX_KVALUE_SIZE] = {0};
    char scr_token[MAX_KVALUE_SIZE];
    if (strlen(scr_token) != 0) {
      get_broker_scrtoken(scr_token, sizeof(scr_token)-1);
      snprintf(scr_channel, sizeof(scr_channel)-1, "%s/%s/scrcmd", client_id, scr_token);
      ESP_LOGI(SGO_LOG_EVENT, "@MQTT Scr channel: %s", scr_channel);
    }

    unsigned char msgenc[MAX_QUEUE_ITEM_SIZE] = { 0 };

    update_key();
  

  char broker_url[MAX_KVALUE_SIZE] = {0};
  getstr(BROKER_URL, broker_url, sizeof(broker_url)-1);
  esp_mqtt_client_config_t mqtt_cfg = {
    .uri = broker_url,
    .event_handle = mqtt_event_handler,
    .client_id = client_id,
    // .user_context = (void *)your_context
  };

  vTaskDelay(1000 / portTICK_PERIOD_MS); // Looks like we have a race confition with wifi

  client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_start(client);


  ScreenCmd screenCmd = { 0 };


  while(true) {
    if (xQueueReceive(cmd, &c, 10000 / portTICK_PERIOD_MS)) {
      if (c == CMD_MQTT_CONNECTED) {

        
          subscribe_cmd();
        

        
          subscribe_scr();
        

        if (first_connect) {
          first_connect = false;
          ESP_LOGI(SGO_LOG_EVENT, "@MQTT First connect");
        }
      }  else if (c == CMD_MQTT_CHANGE_SCR_CHANNEL) {
        get_broker_scrtoken(scr_token, sizeof(scr_token)-1);
        if (strlen(scr_token) != 0) {
          snprintf(scr_channel, sizeof(scr_channel)-1, "%s/%s/scrcmd", client_id, scr_token);
          ESP_LOGI(SGO_LOG_EVENT, "@MQTT Scr channel: %s", scr_channel);
        }
        update_key();
      } 
    }
    if (connected) {
      memset(buf_out, 0, MAX_QUEUE_ITEM_SIZE);
      while (xQueueReceive(log_queue, buf_out, 0)) {
        esp_mqtt_client_publish(client, log_channel, (char *)buf_out, 0, 0, 0);
        memset(buf_out, 0, MAX_QUEUE_ITEM_SIZE);
      }

      
        memset(&screenCmd, 0, sizeof(ScreenCmd));
        if (strlen(scr_channel) != 0) {
          while (xQueueReceive(scr_queue, &screenCmd, 0)) {
            int len = (int)(ceilf((float)screenCmd.len/16.0f)*16);

            memset(msgenc, 0, sizeof(msgenc));
            aes_encrypt_msg((const unsigned char *)screenCmd.buf_out, len, msgenc, key);

            esp_mqtt_client_publish(client, scr_channel, (char *)msgenc, len, 0, 0);
            memset(&screenCmd, 0, sizeof(ScreenCmd));
          }
        }
      
    }
  }
}

static int mqtt_logging_vprintf(const char *str, va_list l) {
  if (strlen(str) <= 9+7 ||
      (strncmp("I (%d) %s", &(str[7]), 9) != 0 &&
       strncmp("W (%d) %s", &(str[7]), 9) != 0 &&
       strncmp("E (%d) %s", &(str[7]), 9) != 0)) {
    return vprintf(str, l); 
  }
  int totalsize = vsnprintf(NULL, 0, str, l);
  if (totalsize >= MAX_QUEUE_ITEM_SIZE - 1) {
    return vprintf(str, l);
  }
  
  va_list nl;
  va_copy(nl, l);
  va_arg(nl, int);
  const char *tag = va_arg(nl, const char *);
  if (strcmp(tag, SGO_LOG_MSG) != 0 &&
      strcmp(tag, SGO_LOG_EVENT) != 0 &&
      strcmp(tag, SGO_LOG_METRIC) != 0) {
    return vprintf(str, l);
  }

  uint8_t buf_in[MAX_QUEUE_ITEM_SIZE] = {0};
  if (uxQueueMessagesWaiting(log_queue) >= MAX_LOG_QUEUE_ITEMS) {
    xQueueReceive(log_queue, buf_in, 0);
  }
  memset(buf_in, 0, MAX_QUEUE_ITEM_SIZE);
  int len = vsnprintf((char*)buf_in, MAX_QUEUE_ITEM_SIZE-1, str, l);
  buf_in[len] = 0;
  xQueueSend(log_queue, buf_in, 0);
  if (cmd/* && uxQueueMessagesWaiting(log_queue) > 5*/) {
    xQueueSend(cmd, &CMD_MQTT_FORCE_FLUSH, 0);
  }
  return vprintf(str, l);
}


  void send_screen_message(const char msg[MAX_QUEUE_ITEM_SIZE], int len) {
    ScreenCmd scrCmd = {
      .len = len,
    };
    memcpy(&scrCmd.buf_out, msg, len);
    xQueueSend(scr_queue, &scrCmd, 0);
    if (cmd/* && uxQueueMessagesWaiting(log_queue) > 5*/) {
      xQueueSend(cmd, &CMD_MQTT_FORCE_FLUSH, 0);
    }
  }

  const char* on_set_broker_scrtoken(const char* value) {
    xQueueSend(cmd, &CMD_MQTT_CHANGE_SCR_CHANNEL, 0);
    return value;
  }

  const char* on_set_broker_enckey(const char* value) {
    xQueueSend(cmd, &CMD_MQTT_CHANGE_SCR_CHANNEL, 0);
    return value;
  }


void mqtt_intercept_log() {
  log_queue = xQueueCreate(MAX_LOG_QUEUE_ITEMS, MAX_QUEUE_ITEM_SIZE);
  if (log_queue == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MQTT Unable to create mqtt log queue");
  }

  esp_log_set_vprintf(mqtt_logging_vprintf);
}

void init_mqtt() {
  ESP_LOGI(SGO_LOG_EVENT, "@MQTT Intializing MQTT task");

  //esp_log_level_set("MQTT_CLIENT", ESP_LOG_NONE);

  cmd = xQueueCreate(10, sizeof(int));
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@MQTT Unable to create mqtt queue");
  }

  
    scr_queue = xQueueCreate(MAX_SCR_QUEUE_ITEMS, sizeof(ScreenCmd));
    if (scr_queue == NULL) {
      ESP_LOGE(SGO_LOG_EVENT, "@MQTT Unable to create mqtt scr queue");
    }
  

  BaseType_t ret = xTaskCreatePinnedToCore(mqtt_task, "MQTT", 8192, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@MQTT Failed to create task");
  }
}

