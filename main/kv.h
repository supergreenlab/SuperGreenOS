/*
 * =====================================================================================
 *
 *       Filename:  kv.h
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  04/16/2018 15:47:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef KV_H_
#define KV_H_

void init_kv();

int geti(const char * key);
void seti(const char * key, int value);
bool hasi(const char * key);
void defaulti(const char * key, int value);

void getstr(const char * key, char *value, const size_t length);
void setstr(const char * key, const char * value);
bool hasstr(const char * key);
void defaultstr(const char * key, const char * value);

#endif
