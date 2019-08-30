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

#ifndef HTTPD_KV_HANDLERS_H_
#define HTTPD_KV_HANDLERS_H_

#include <string.h>
#include <stdint.h>

typedef struct {
  const char *name;
  void (*handler)(int8_t);
  int8_t (*getter)();
} kvi8_handler;

extern const kvi8_handler kvi8_handlers[];
const kvi8_handler *get_kvi8_handler(const char *name);

typedef struct {
  const char *name;
  void (*handler)(int16_t);
  int16_t (*getter)();
} kvi16_handler;

extern const kvi16_handler kvi16_handlers[];
const kvi16_handler *get_kvi16_handler(const char *name);

typedef struct {
  const char *name;
  void (*handler)(int32_t);
  int32_t (*getter)();
} kvi32_handler;

extern const kvi32_handler kvi32_handlers[];
const kvi32_handler *get_kvi32_handler(const char *name);

typedef struct {
  const char *name;
  void (*handler)(const char *);
  void (*getter)(char *, size_t);
} kvs_handler;

extern const kvs_handler kvs_handlers[];
const kvs_handler *get_kvs_handler(const char *name);

#endif
