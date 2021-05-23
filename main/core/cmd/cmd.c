/*
 * Copyright (C) 2021  SuperGreenLab <towelie@supergreenlab.com>
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

#include "cmd.h"

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"

#include "../log/log.h"
#include "../kv/kv.h"
#include "../kv/kv_mapping.h"

static QueueHandle_t cmd;
static char buf_cmd[MAX_CMD_LENGTH] = {0};

void execute_cmd(int length, const char *cmdData) {
  if (length > MAX_CMD_LENGTH-1) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Sending command failed, too long.");
  } else {
    char cmdStr[MAX_CMD_LENGTH] = {0};
    memcpy(cmdStr, cmdData, length);
    xQueueSend(cmd, cmdStr, 0);
  }
}

static struct {
  struct arg_str *id;
  struct arg_str *key;
  struct arg_int *value;
  struct arg_end *end;
} seti_args;

static int seti(int argc, char **argv) {
  int nerrors = arg_parse(argc, argv, (void **) &seti_args);
  if (nerrors != 0) {
    arg_print_errors(stderr, seti_args.end, argv[0]);
    ESP_LOGE(SGO_LOG_EVENT, "@CMD (%s) parameter error", seti_args.id->sval[0]);
    return 1;
  }

  const char *name = seti_args.key->sval[0];
  const kvi8_mapping *hi8 = get_kvi8_mapping(name);
  bool is_i8 = hi8 && hi8->setter;
  const kvui8_mapping *hui8 = get_kvui8_mapping(name);
  bool is_ui8 = hui8 && hui8->setter;
  const kvi16_mapping *hi16 = get_kvi16_mapping(name);
  bool is_i16 = hi16 && hi16->setter;
  const kvui16_mapping *hui16 = get_kvui16_mapping(name);
  bool is_ui16 = hui16 && hui16->setter;
  const kvi32_mapping *hi32 = get_kvi32_mapping(name);
  bool is_i32 = hi32 && hi32->setter;
  const kvui32_mapping *hui32 = get_kvui32_mapping(name);
  bool is_ui32 = hui32 && hui32->setter;

  if (!is_i8 && !is_ui8 && !is_i16 && !is_ui16 && !is_i32 && !is_ui32) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD (%s) %s: Key not found or readonly", seti_args.id->sval[0], name);
    return 1;
  }

  const int value = seti_args.value->ival[0];

  if (is_i8) {
    hi8->setter((int8_t)value);
  } else if (is_ui8) {
    hui8->setter((uint8_t)value);
  } else if (is_i16) {
    hi16->setter((int16_t)value);
  } else if (is_ui16) {
    hui16->setter((uint16_t)value);
  } else if (is_i32) {
    hi32->setter((int32_t)value);
  } else if (is_ui32) {
    hui32->setter((uint32_t)value);
  }

  ESP_LOGI(SGO_LOG_EVENT, "@CMD (%s) done", seti_args.id->sval[0]);
  return 0;
}

static struct {
  struct arg_str *id;
  struct arg_str *key;
  struct arg_str *value;
  struct arg_end *end;
} sets_args;

static int sets(int argc, char **argv) {
  int nerrors = arg_parse(argc, argv, (void **) &sets_args);
  if (nerrors != 0) {
    arg_print_errors(stderr, sets_args.end, argv[0]);
    ESP_LOGE(SGO_LOG_EVENT, "@CMD (%s) parameter error", seti_args.id->sval[0]);
    return 1;
  }

  const char *name = sets_args.key->sval[0];

  const kvs_mapping *h = get_kvs_mapping(name);
  if (!h || !h->setter) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD (%s) %s: Key not found or readonly", sets_args.id->sval[0], name);
    return 1;
  }

  const char *value = sets_args.value->sval[0];
  h->setter(value);

  ESP_LOGI(SGO_LOG_EVENT, "@CMD (%s) done", sets_args.id->sval[0]);
  return 0;
}

static void cmd_task(void *param) {
  {
    seti_args.id = arg_str1("i", "id", "<s>", "Id");
    seti_args.key = arg_str1("k", "key", "<s>", "Key");
    seti_args.value = arg_int1("v", "value", "<n>", "Value");
    seti_args.end = arg_end(2);

    const esp_console_cmd_t seti_cmd = {
      .command = "seti",
      .help = "Sets a kv store key/value as int",
      .hint = NULL,
      .func = &seti,
      .argtable = &seti_args,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&seti_cmd) );
  }

  {
    sets_args.id = arg_str1("i", "id", "<s>", "Id");
    sets_args.key = arg_str1("k", "key", "<s>", "Key");
    sets_args.value = arg_str1("v", "value", "<n>", "Value");
    sets_args.end = arg_end(2);

    const esp_console_cmd_t sets_cmd = {
      .command = "sets",
      .help = "Sets a kv store key/value as string",
      .hint = NULL,
      .func = &sets,
      .argtable = &sets_args,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&sets_cmd) );
  }

  esp_console_config_t console_config = {
    .max_cmdline_args = 8,
    .max_cmdline_length = MAX_CMD_LENGTH,
  };
  ESP_ERROR_CHECK( esp_console_init(&console_config) );

  while (true) {
    if (xQueueReceive(cmd, buf_cmd, portMAX_DELAY) != pdTRUE) {
      continue;
    }
    int ret;
    esp_err_t err = esp_console_run(buf_cmd, &ret);
    if (err == ESP_ERR_NOT_FOUND) {
      printf("Unrecognized command\n");
    } else if (err == ESP_ERR_INVALID_ARG) {
      // command was empty
    } else if (err == ESP_OK && ret != ESP_OK) {
      printf("Command returned non-zero error code: 0x%x (%s)\n", ret, esp_err_to_name(ret));
    } else if (err != ESP_OK) {
      printf("Internal error: %s\n", esp_err_to_name(err));
    }

    memset(buf_cmd, 0, MAX_CMD_LENGTH);
  }
}

void init_cmd() {
  ESP_LOGI(SGO_LOG_EVENT, "@CMD Intializing CMD task");

  cmd = xQueueCreate(1, MAX_CMD_LENGTH);
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Unable to create cmd queue");
  }

  BaseType_t ret = xTaskCreatePinnedToCore(cmd_task, "CMD", 8192, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Failed to create task");
  }
}
