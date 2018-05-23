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
#include "../core/kv.h"

/* UUID string: 8ff6dfd2-3bd6-feb4-43ec-de5663122894 */
const uint8_t STATE_UUID[ESP_UUID_LEN_128] = {0x94,0x28,0x12,0x63,0x56,0xde,0xec,0x43,0xb4,0xfe,0xd6,0x3b,0xd2,0xdf,0xf6,0x8f};

void init_state() {
  defaulti(STATE, FIRST_RUN);
}

// BLE Callbacks

void on_set_state(enum state value) {
  seti(STATE, value);
}
