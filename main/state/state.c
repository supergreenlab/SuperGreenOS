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
#include <stdint.h>

#include "state.h"
#include "../kv/kv.h"
#include "../kv/kv_ble.h"

/* UUID string: 8ff6dfd2-3bd6-feb4-43ec-de5663122894 */
const uint8_t STATE_UUID[ESP_UUID_LEN_128] = {0x94,0x28,0x12,0x63,0x56,0xde,0xec,0x43,0xb4,0xfe,0xd6,0x3b,0xd2,0xdf,0xf6,0x8f};
/*  UUID string: a6317732-8c0e-ee6e-68ee-61f13d4f8b25 */
const uint8_t DEVICE_NAME_UUID[ESP_UUID_LEN_128] = {0x25,0x8b,0x4f,0x3d,0xf1,0x61,0xee,0x68,0x6e,0xee,0x0e,0x8c,0x32,0x77,0x31,0xa6};

#define DEVICE_NAME "DEV_NAME"
#define DEFAULT_DEVICE_NAME "chronic-o-matic"

void init_state() {
  defaulti(STATE, FIRST_RUN);
  defaultstr(DEVICE_NAME, DEFAULT_DEVICE_NAME);

  sync_ble_i(STATE, IDX_VALUE(STATE));
  sync_ble_str(DEVICE_NAME, IDX_VALUE(DEVICE_NAME));
}

// BLE Callbacks

void on_set_state(enum state value) {
  seti(STATE, value);
}

void on_set_device_name(const char *value) {
  setstr(DEVICE_NAME, value);
}
