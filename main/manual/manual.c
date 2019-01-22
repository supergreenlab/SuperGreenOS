/*
 * Copyright (C) 2018  SuperGreenLab <towelie@supergreenlab.com>
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

#include "manual.h"

#include "../core/log/log.h"

void start_manual(int boxId) {
  ESP_LOGI(SGO_LOG_EVENT, "@MANUAL_%d start_manual", boxId);
}

void stop_manual(int boxId) {
  ESP_LOGI(SGO_LOG_EVENT, "@MANUAL_%d stop_manual", boxId);
}

void manual_task(int boxId) {
  ESP_LOGI(SGO_LOG_EVENT, "@MANUAL_%d manual_task", boxId);
}
