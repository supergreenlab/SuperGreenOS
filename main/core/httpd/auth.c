/*
 * Copyright (C) 2021  SuperGreenLab <towelie@supergreenlab.com>
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

#include <esp_http_server.h>

#include "../kv/kv.h"
#include "../log/log.h"

bool auth_request(httpd_req_t *req) {
  if (!hasstr(HTTPD_AUTH)) {
    return true;
  }
  char auth[MAX_KVALUE_SIZE] = {0};
  getstr(HTTPD_AUTH, auth, MAX_KVALUE_SIZE);

  if (strlen(auth) == 0) {
    return true;
  }

  char reqAuth[MAX_KVALUE_SIZE] = {0};
  if(httpd_req_get_hdr_value_str(req, "Authorization", reqAuth, MAX_KVALUE_SIZE) != ESP_OK) {
    httpd_resp_set_hdr(req, "WWW-Authenticate", "Basic realm=\"Please login\"");
    httpd_resp_set_status(req, "401");
    httpd_resp_send(req, "NOK", 3);
    return false;
  }
  if (strlen(reqAuth) != 6 + strlen(auth) || strncmp(auth, &(reqAuth[6]), MAX_KVALUE_SIZE-6) != 0) {
    httpd_resp_set_status(req, "403");
    httpd_resp_send(req, "NOK", 3);
    return false;
  }
  return true;
}
