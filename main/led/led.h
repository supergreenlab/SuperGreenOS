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

#ifndef LED_H_
#define LED_H_

// see https://docs.google.com/document/d/1z05o7xFu0v3u1SpW2AymakgdP0owED07dASqW3xkCCo/edit?usp=sharing

typedef enum {
  LED_FULLSPECTRUM,
  LED_UVA,
  LED_DB,
  LED_DR,
  LED_FR,
} led_type;

void init_led();
void refresh_led(int boxId, int ledId);

/* KV Callbacks */

int on_set_led_duty(int ledId, int value);
int on_set_led_dim(int ledId, int value);
int on_set_led_type(int led_id, int value);
int on_set_led_box(int ledId, int boxId);

#endif

