/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/10/2018 20:32:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "utils.h"

#include "../misc/log.h"

void print_time(time_t t) {
  struct tm timeinfo;
  localtime_r(&t, &timeinfo); 

  print_timeinfo(timeinfo);
}

void print_timeinfo(struct tm timeinfo) {
  char buffer[26] = {0};
  strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", &timeinfo);
  ESP_LOGI(TAG, "%s", buffer);
}
