/* 
 * @FILENAME    cb-time.c
 * @DESCRIPTION functions about time
 * @AUTHOR      hejiyan
 * @VERSION     0.1
 */
#include <time.h>
#include <string.h>
#include "cb-time.h"

/* return current time */
time_t get_cur_time()
{
	return time(NULL);
}

/* convert time_t to string */
void time_to_str(time_t t, char* s)
{
	struct tm* now_time;
	now_time = localtime(&t);
	sprintf(
		s,
		"%04d/%02d/%02d-%02d:%02d:%02d",
		1900 + now_time->tm_year,
		now_time->tm_mon,
		now_time->tm_mday,
		now_time->tm_hour,
		now_time->tm_min,
		now_time->tm_sec
	);
}

/* convert string to time_t(uint) */
time_t str_to_time(const char* s)
{
	/* template: 1998/04/11-12:34:56 */
	struct tm tmp, *now_time = &tmp;
	memset(&tmp, 0, sizeof(tmp));
	sscanf(
		s,
		"%d/%d/%d-%d:%d:%d",
		&now_time->tm_year,
		&now_time->tm_mon,
		&now_time->tm_mday,
		&now_time->tm_hour,
		&now_time->tm_min,
		&now_time->tm_sec
	);
	now_time->tm_year -= 1900;
	return mktime(now_time);
}
