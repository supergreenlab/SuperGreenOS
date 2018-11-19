/*
 * =====================================================================================
 *
 *       Filename:  httpd_kv_handlers.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/14/2018 11:24:27 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "httpd_kv_handlers.h"

#include "../state/state.h"
#include "../time/time.h"
#include "../timers/timer.h"
#include "../wifi/wifi.h"
#include "../led/led.h"
#include "../timers/onoff/onoff.h"
#include "../timers/season/season.h"
#include "../mixer/mixer.h"
#include "../blower/blower.h"

// This is a fucking mess, will be fixed with ble stack

// STATE, DEV_NAME, BLWR, WSSID, WPASS, ON_H, ON_M, OFF_H, OFF_M, TIMER_T, TIMER_O, ST_AT, SIM_S_M, SIM_S_D, DUR_D, SIM_DUR_D, TIME, LED_DIM, STRETCH, NOSEND, MSG, EVENT, METRIC

const kvi_handler kvi_handlers[] = {
  {
    .name = "STATE",
    .handler = on_set_state,
  },
  {
    .name = "TIME",
    .handler = on_set_time,
  },
  {
    .name = "TIMER_T",
    .handler = on_set_timer_type,
  },
  {
    .name = "TIMER_O",
    .handler = on_set_timer_output,
  },
  {
    .name = "SIM_S_M",
    .handler = on_set_start_date_month,
  },
  {
    .name = "SIM_S_D",
    .handler = on_set_start_date_day,
  },
  {
    .name = "DUR_D",
    .handler = on_set_duration_days,
  },
  {
    .name = "SIM_DUR_D",
    .handler = on_set_simulation_duration_days,
  },
  {
    .name = "ST_AT",
    .handler = on_set_started_at,
  },
  {
    .name = "ON_H",
    .handler = on_set_on_hour,
  },
  {
    .name = "ON_M",
    .handler = on_set_on_min,
  },
  {
    .name = "OFF_H",
    .handler = on_set_off_hour,
  },
  {
    .name = "OFF_M",
    .handler = on_set_off_min,
  },
  //
  {
    .name = "LED_DIM",
    .handler = on_set_led_dim,
  },
  {
    .name = "STRETCH",
    .handler = on_set_stretch,
  },
  {
    .name = "BLWR",
    .handler = on_set_blower,
  },
  {
    .name = NULL,
    .handler = NULL,
  },
};

const kvi_handler *get_kvi_handler(const char *name) {
  for (int i = 0; kvi_handlers[i].name != NULL; ++i) {
    if (strcmp(kvi_handlers[i].name, name) == 0) {
      return &kvi_handlers[i];
    }
  }
  return NULL;
}

const kvs_handler kvs_handlers[] = {
  {
    .name = "DEV_NAME",
    .handler = on_set_device_name,
  },
  {
    .name = "WIFI_SSD",
    .handler = on_set_wifi_ssid,
  },
  {
    .name = "WIFI_PASS",
    .handler = on_set_wifi_password,
  },
  {
    .name = NULL,
    .handler = NULL,
  }
};

const kvs_handler *get_kvs_handler(const char *name) {
  for (int i = 0; kvs_handlers[i].name != NULL; ++i) {
    if (strcmp(kvs_handlers[i].name, name) == 0) {
      return &kvs_handlers[i];
    }
  }
  return NULL;
}
