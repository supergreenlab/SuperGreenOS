/*
 * =====================================================================================
 *
 *       Filename:  touch.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2018 12:05:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "../core/kv.h"
#include "../core/kv_ble.h"
#include "timer.h"
#include "../ble_db.h"

/*  UUID string: 5f5ea840-3aa9-0a7b-343d-415ab2faa9f3 */
const uint8_t TIMER_TYPE_UUID[ESP_UUID_LEN_128] = {0xf3,0xa9,0xfa,0xb2,0x5a,0x41,0x3d,0x34,0x7b,0x0a,0xa9,0x3a,0x40,0xa8,0x5e,0x5f};
/*  UUID string: b2286094-8299-a967-db89-ee856e365789 */
const uint8_t TIMER_OUTPUT_UUID[ESP_UUID_LEN_128] = {0x89,0x57,0x36,0x6e,0x85,0xee,0x89,0xdb,0x67,0xa9,0x99,0x82,0x94,0x60,0x28,0xb2};

void init_timer() {
  defaulti(TIMER_TYPE, TIMER_MANUAL);
  defaulti(TIMER_OUTPUT, 0);

  sync_ble_i(TIMER_TYPE, IDX_VALUE(TIMER_TYPE));
  sync_ble_i(TIMER_OUTPUT, IDX_VALUE(TIMER_OUTPUT));
}

// BLE Callbacks

void on_set_timer_type(enum timer t) {
  seti(TIMER_TYPE, t);
}

void on_set_timer_output(int value) {
  if (geti(TIMER_TYPE) != TIMER_MANUAL) return;

  seti(TIMER_OUTPUT, value);
}
