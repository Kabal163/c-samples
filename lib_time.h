#ifndef LIB_TIME
#define LIB_TIME
#include <sys/time.h>

long tv_dif(struct timeval *dif, struct timeval *start, struct timeval *end); 
#endif