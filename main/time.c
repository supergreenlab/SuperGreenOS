/*
 * =====================================================================================
 *
 *       Filename:  time.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2018 19:26:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "apps/sntp/sntp.h"

#include "time.h"
#include "kv.h"
#include "ble.h"
#include "ble_db.h"
#include "wifi.h"

// "126528f3-7b17-4fd1-ac63-210c9078958e"
const uint8_t TIME_SERVICE[ESP_UUID_LEN_128] = {0x8e,0x95,0x78,0x90,0x0c,0x21,0x63,0xac,0xd1,0x4f,0x17,0x7b,0xf3,0x28,0x65,0x12};
// "40f9ee4f-e19e-4a8a-aa33-b4aae23b6a9b"
const uint8_t TIME_UUID[ESP_UUID_LEN_128] = {0x9b,0x6a,0x3b,0xe2,0xaa,0xb4,0x33,0xaa,0x8a,0x4a,0x9e,0xe1,0x4f,0xee,0xf9,0x40};
// "3867a37c-85a9-338c-40ac-96d4ee586841"
const uint8_t SIMULATED_TIME_UUID[ESP_UUID_LEN_128] = {0x41,0x68,0x58,0xee,0xd4,0x96,0xac,0x40,0x8c,0x33,0xa9,0x85,0x7c,0xa3,0x67,0x38};
// "829bfbd2-a7e1-4c16-b7e2-4a8fd6261f40"
const uint8_t START_DATE_MONTH_UUID[ESP_UUID_LEN_128] = {0x40,0x1f,0x26,0xd6,0x8f,0x4a,0xe2,0xb7,0x16,0x4c,0xe1,0xa7,0xd2,0xfb,0x9b,0x82};
// "547af7e1-6a8c-4fbc-b568-9c3f194cdc1e"
const uint8_t START_DATE_DAY_UUID[ESP_UUID_LEN_128] = {0x1e,0xdc,0x4c,0x19,0x3f,0x9c,0x68,0xb5,0xbc,0x4f,0x8c,0x6a,0xe1,0xf7,0x7a,0x54};
// "495600fd-947d-4157-a996-20780ad1d81a"
const uint8_t DURATION_DAYS_UUID[ESP_UUID_LEN_128] = {0x1a,0xd8,0xd1,0x0a,0x78,0x20,0x96,0xa9,0x57,0x41,0x7d,0x94,0xfd,0x00,0x56,0x49};
// "6f01cd48-a405-45e5-99db-0de8b5ca2e7f"
const uint8_t SIMULATION_DURATION_DAYS_UUID[ESP_UUID_LEN_128] = {0x7f,0x2e,0xca,0xb5,0xe8,0x0d,0xdb,0x99,0xe5,0x45,0x05,0xa4,0x48,0xcd,0x01,0x6f};
// "1f450234-f101-4f57-ba39-304b053b95a2"
const uint8_t STARTED_AT_UUID[ESP_UUID_LEN_128] = {0xa2,0x95,0x3b,0x05,0x4b,0x30,0x39,0xba,0x57,0x4f,0x01,0xf1,0x34,0x02,0x45,0x1f};

#define TIME "TIME"

#define START_DATE_MONTH "SIM_S_M"
#define START_DATE_DAY "SIM_S_D"
#define DURATION_DAYS "DUR_D"
#define SIMULATION_DURATION_DAYS "SIM_DUR_D"
#define STARTED_AT "ST_AT"

void time_task(void *param);
void ntp_task(void *param);
static void setup(void);
void print_time(time_t t);
void print_timeinfo(struct tm timeinfo);

void init_time() {
  defaulti(TIME, 4);
  defaulti(START_DATE_MONTH, 4);
  defaulti(START_DATE_DAY, 1);
  defaulti(DURATION_DAYS, 195);
  defaulti(SIMULATION_DURATION_DAYS, 75);
  defaulti(STARTED_AT, 0);

  seti(STARTED_AT, (int)1518912000); // 02
  //seti(STARTED_AT, (int)1521331200); // 03

  xTaskCreate(time_task, "Time Task", 2048, NULL, 10, NULL);
}

time_t get_box_time() {
  int start_date_month = geti(START_DATE_MONTH);
  int start_date_day = geti(START_DATE_DAY);
  int duration_days = geti(DURATION_DAYS);
  int simulation_duration_days = geti(SIMULATION_DURATION_DAYS);
  int started_at = geti(STARTED_AT);

  time_t now;
  struct tm tm_now;
  time(&now);
  localtime_r(&now, &tm_now); 

  time_t started_at_t = (time_t)started_at;
  struct tm tm_started_at;
  localtime_r(&started_at_t, &tm_started_at);

  double duration = (double)((int)now - (int)started_at_t) / (double)(24 * 60 * 60);
  double adv = (double)duration / (double)simulation_duration_days;

  struct tm tm_simulated;
  memset(&tm_simulated, 0, sizeof(tm_simulated));
  tm_simulated.tm_year = tm_started_at.tm_year;
  tm_simulated.tm_mon = start_date_month;
  tm_simulated.tm_mday = start_date_day;
  tm_simulated.tm_hour = tm_now.tm_hour;
  tm_simulated.tm_min = tm_now.tm_min;
  tm_simulated.tm_sec = tm_now.tm_sec;

  time_t simulated_time = mktime(&tm_simulated);
  int seconds_to_adv = adv * duration_days * 24 * 60 * 60;
  simulated_time += seconds_to_adv - (seconds_to_adv % (24 * 60 * 60));
  localtime_r(&simulated_time, &tm_simulated);

  return simulated_time;
}

void time_task(void *param) {
  if (hasi(TIME)) {
    time_t now = (time_t)geti(TIME);
    struct timeval tv = { .tv_sec = now, .tv_usec = 0 };
    settimeofday(&tv, NULL);
    print_time(now);
    xTaskCreate(ntp_task, "NTP task", 2048, NULL, 10, NULL);
  } else {
    wait_connected();
    setup();
  }
  while(true) {
    time_t now;
    time(&now);
    print_time(now);
    seti(TIME, (int)now);
    set_attr_value(IDX_CHAR_VAL_TIME, (uint8_t *)&now, sizeof(time_t));
    notify_attr(IDX_CHAR_VAL_TIME);

    printf("Simulated time: ");
    time_t box_time = get_box_time();
    print_time(box_time);
    set_attr_value(IDX_CHAR_VAL_SIMULATED_TIME, (uint8_t *)&box_time, sizeof(time_t));
    notify_attr(IDX_CHAR_VAL_SIMULATED_TIME);

    vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
  }
}

void print_time(time_t t) {
  struct tm timeinfo;
  localtime_r(&t, &timeinfo); 

  print_timeinfo(timeinfo);
}

void print_timeinfo(struct tm timeinfo) {
  char buffer[26] = {0};
  strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", &timeinfo);
  printf("%s\n", buffer);
}

void ntp_task(void *param) {
  wait_connected();
  setup();
  vTaskDelete(NULL);
}

static void setup(void) {
  const char *NTP_SERVER = "pool.ntp.org";
  printf("Initializing SNTP\n");
  sntp_setoperatingmode(SNTP_OPMODE_POLL);
  sntp_setservername(0, (char *)NTP_SERVER);
  sntp_init();
}
