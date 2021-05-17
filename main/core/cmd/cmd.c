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

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"

#include "../log/log.h"
#include "../kv/kv.h"

#define CMD_LENGTH 256

static QueueHandle_t cmd;
static char buf_cmd[CMD_LENGTH] = {0};

void execute_cmd(int length, const char *cmdData) {
  if (length > CMD_LENGTH-1) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Sending command failed, too long.");
  } else {
    char cmdStr[CMD_LENGTH] = {0};
    memcpy(cmdStr, cmdData, length);
    xQueueSend(cmd, cmdStr, 0);
  }
}

static struct {
  struct arg_int *value;
  struct arg_end *end;
} test_args;

static int test(int argc, char **argv) {
  int nerrors = arg_parse(argc, argv, (void **) &test_args);
  if (nerrors != 0) {
    arg_print_errors(stderr, test_args.end, argv[0]);
    return 1;
  }
  ESP_LOGI(SGO_LOG_NOSEND, "@CMD test %d", test_args.value->ival[0]);
  return 0;
}

static void cmd_task(void *param) {
  test_args.value = arg_int0("v", "value", "<n>", "Value");
  test_args.end = arg_end(2);

  const esp_console_cmd_t test_cmd = {
    .command = "test",
    .help = "Test stuff",
    .hint = NULL,
    .func = &test,
    .argtable = &test_args,
  };
  ESP_ERROR_CHECK( esp_console_cmd_register(&test_cmd) );

  esp_console_config_t console_config = {
    .max_cmdline_args = 8,
    .max_cmdline_length = CMD_LENGTH,
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

    memset(buf_cmd, 0, CMD_LENGTH);
  }
}

void init_cmd() {
  ESP_LOGI(SGO_LOG_EVENT, "@CMD Intializing CMD task");

  cmd = xQueueCreate(1, CMD_LENGTH);
  if (cmd == NULL) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Unable to create cmd queue");
  }

  BaseType_t ret = xTaskCreatePinnedToCore(cmd_task, "CMD", 8192, NULL, 10, NULL, 1);
  if (ret != pdPASS) {
    ESP_LOGE(SGO_LOG_EVENT, "@CMD Failed to create task");
  }
}
