/*
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

#ifndef WATERING_H_
#define WATERING_H_

#include <stdlib.h>

void init_watering();

// KV callbacks

int on_set_box_watering_duty(int boxId, int value);
int on_set_box_watering_period(int boxId, int value);
int on_set_box_watering_duration(int boxId, int value);
int on_set_box_watering_last(int boxId, int value);
int on_set_box_watering_power(int boxId, int value);

#endif

