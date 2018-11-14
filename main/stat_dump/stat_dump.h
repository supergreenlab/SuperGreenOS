/*
 * =====================================================================================
 *
 *       Filename:  stat_dump.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/30/2018 11:26:52 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef STAT_DUMP_H_
#define STAT_DUMP_H_

void add_kvs_dump(const char *k);
void add_kvi_dump(const char *k);

void init_stat_dump();
void init_stat_dump_queues();

#endif
