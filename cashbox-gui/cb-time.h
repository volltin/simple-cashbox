/* 
 * @FILENAME    cb-time.h
 * @DESCRIPTION headers for cb-time.c
 * @AUTHOR      hejiyan
 * @VERSION     0.1
 */
#include <stdio.h>
#include <time.h>
#ifndef _CB_TIME_
#define _CB_TIME_

void   time_to_str(time_t t, char* s);

time_t str_to_time(const char* s);

time_t get_cur_time();

#endif
