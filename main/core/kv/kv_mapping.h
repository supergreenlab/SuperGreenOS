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

#ifndef KV_MAPPING_H_
#define KV_MAPPING_H_

#include <string.h>
#include <stdint.h>

typedef struct {
  const char *name;
  void (*setter)(int8_t);
  int8_t (*getter)();
} kvi8_mapping;

extern const kvi8_mapping kvi8_mappings[];
const kvi8_mapping *get_kvi8_mapping(const char *name);

typedef struct {
  const char *name;
  void (*setter)(uint8_t);
  uint8_t (*getter)();
} kvui8_mapping;

extern const kvui8_mapping kvui8_mappings[];
const kvui8_mapping *get_kvui8_mapping(const char *name);

typedef struct {
  const char *name;
  void (*setter)(int16_t);
  int16_t (*getter)();
} kvi16_mapping;

extern const kvi16_mapping kvi16_mappings[];
const kvi16_mapping *get_kvi16_mapping(const char *name);

typedef struct {
  const char *name;
  void (*setter)(uint16_t);
  uint16_t (*getter)();
} kvui16_mapping;

extern const kvui16_mapping kvui16_mappings[];
const kvui16_mapping *get_kvui16_mapping(const char *name);

typedef struct {
  const char *name;
  void (*setter)(int32_t);
  int32_t (*getter)();
} kvi32_mapping;

extern const kvi32_mapping kvi32_mappings[];
const kvi32_mapping *get_kvi32_mapping(const char *name);

typedef struct {
  const char *name;
  void (*setter)(uint32_t);
  uint32_t (*getter)();
} kvui32_mapping;

extern const kvui32_mapping kviui32_mappings[];
const kvui32_mapping *get_kvui32_mapping(const char *name);

typedef struct {
  const char *name;
  void (*setter)(const char *);
  void (*getter)(char *, size_t);
} kvs_mapping;

extern const kvs_mapping kvs_mappings[];
const kvs_mapping *get_kvs_mapping(const char *name);

#endif
