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

typedef struct {
  const char *name;
  void (*handler)(int);
  int (*getter)();
} kvi_handler;

extern const kvi_handler kvi_handlers[];
const kvi_handler *get_kvi_handler(const char *name);

typedef struct {
  const char *name;
  void (*handler)(const char *);
  void (*getter)(char *, size_t);
} kvs_handler;

extern const kvs_handler kvs_handlers[];
const kvs_handler *get_kvs_handler(const char *name);

#endif
