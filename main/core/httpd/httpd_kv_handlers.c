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

#include "../kv/kv_helpers_internal.h"
#include "httpd_kv_handlers.h"
#include "../include_modules.h"

const kvi_handler kvi_handlers[] = {
/*
* [GENERATED]
*/
  
  {
    .name = "TIME",
    .handler = internal_set_time,
  },
  {
    .name = "TIMER_TYPE",
    .handler = internal_set_timer_type,
  },
  {
    .name = "STRETCH",
    .handler = internal_set_stretch,
  },
  {
    .name = "LED_DIM",
    .handler = internal_set_led_dim,
  },
  {
    .name = "BLOWER",
    .handler = internal_set_blower,
  },
  {
    .name = "LED_0_DUTY",
    .handler = internal_set_led_0_duty,
  },
  {
    .name = "LED_1_DUTY",
    .handler = internal_set_led_1_duty,
  },
  {
    .name = "LED_2_DUTY",
    .handler = internal_set_led_2_duty,
  },
  {
    .name = "LED_3_DUTY",
    .handler = internal_set_led_3_duty,
  },
  {
    .name = "LED_4_DUTY",
    .handler = internal_set_led_4_duty,
  },
  {
    .name = "LED_5_DUTY",
    .handler = internal_set_led_5_duty,
  },

/*
* [/GENERATED]
*/
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
/*
* [GENERATED]
*/

  {
    .name = "WIFI_SSID",
    .handler = internal_set_wifi_ssid,
  },
  {
    .name = "WIFI_PASS",
    .handler = internal_set_wifi_password,
  },

/*
* [/GENERATED]
*/
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
