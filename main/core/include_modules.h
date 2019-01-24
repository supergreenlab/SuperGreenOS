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

#ifndef INCLUDE_MODULES_H_
#define INCLUDE_MODULES_H_

/*
* [GENERATED]
*/

// Core modules
#include "wifi/wifi.h"
#include "ble/ble.h"
#include "kv/kv.h"
#include "ota/ota.h"
#include "httpd/httpd.h"
#include "stat_dump/stat_dump.h"
#include "time/time.h"
#include "mqtt/mqtt.h"
#include "i2c/i2c.h"

// Custom modules
#include "../blower/blower.h"
#include "../led/led.h"
#include "../mixer/mixer.h"
#include "../state/state.h"
#include "../status_led/status_led.h"
#include "../timer/timer.h"
#include "../onoff/onoff.h"
#include "../manual/manual.h"
#include "../box/box.h"

/*
* [/GENERATED]
*/

#endif
