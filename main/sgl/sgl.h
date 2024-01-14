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

#ifndef SGL_H_
#define SGL_H_

#include <stdint.h>

typedef void (*UpdateFunction)();

typedef void (*CommandFunction)(const char *msg, int len);

typedef enum {
  GET_SENSORS,
  GET_CHECKLISTS,
  GET_METRICS,
  GET_TIMELAPSE,
  GET_PLANT_DATE,

  SET_SENSORS,
  SET_CHECKLISTS,
  SET_METRICS,
  SET_TIMELAPSE,
  SET_PLANT_DATE,
  
  CMD_COUNT,
} CommandType;

void set_command(CommandType type, CommandFunction fn);
void set_command_update(CommandType type, UpdateFunction fn);

void init_sgl();
void mqtt_message(const char *str, int len);

#endif
