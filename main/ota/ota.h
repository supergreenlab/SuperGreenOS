/*
 * =====================================================================================
 *
 *       Filename:  ota.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/18/2018 17:46:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef OTA_H_
#define OTA_H_

extern const char *OTA_SERVER_IP;
extern const char *OTA_SERVER_PORT;
extern const char *OTA_VERSION_FILENAME;
extern const char *OTA_FILENAME;

void init_ota();

#endif
