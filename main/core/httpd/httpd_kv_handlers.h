/*
 * =====================================================================================
 *
 *       Filename:  httpd_kv_handlers.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/14/2018 11:26:01 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef HTTPD_KV_HANDLERS_H_
#define HTTPD_KV_HANDLERS_H_

typedef struct {
  const char *name;
  const char *nvs_key;
  void (*handler)(int);
} kvi_handler;

extern const kvi_handler kvi_handlers[];
const kvi_handler *get_kvi_handler(const char *name);

typedef struct {
  const char *name;
  const char *nvs_key;
  void (*handler)(const char *);
} kvs_handler;

extern const kvs_handler kvs_handlers[];
const kvs_handler *get_kvs_handler(const char *name);

#endif
