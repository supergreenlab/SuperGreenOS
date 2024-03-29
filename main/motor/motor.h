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

#ifndef MOTOR_H_
#define MOTOR_H_

void init_motor();
void refresh_motors();

/* KV Callbacks */

int on_set_motor_frequency(int motorId, int value);
int on_set_motor_duty_testing(int motorId, int value);
int on_set_motor_source(int motorId, int value);
int on_set_motor_min(int motorId, int value);
int on_set_motor_max(int motorId, int value);

#endif
