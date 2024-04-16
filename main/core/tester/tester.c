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

#include "tester.h"

#include <sys/param.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"

#include "../reboot/reboot.h"
#include "../log/log.h"
#include "../kv/kv.h"

void init_tester() {
  ESP_LOGI(SGO_LOG_NOSEND, "@TESTER Initializing tester module");

  const char path[] = "/spiffs/tester.html";
  struct stat file_stat;
  if (stat(path, &file_stat) != -1) {
    ESP_LOGI(SGO_LOG_NOSEND, "@TESTER /spiffs/tester.html file found. --- STARTING TEST MODE ---");
    set_tester_enabled(1);
    unlink(path);
  }
}

/*
 * http callback
 */

int on_set_tester_enabled(int value) {
  reboot_esp();
  return value;
}
