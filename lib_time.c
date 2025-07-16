#include <stdio.h>
#include <sys/time.h>

long tv_dif(struct timeval *dif, struct timeval *start, struct timeval *end) {
  dif->tv_sec = end->tv_sec - start->tv_sec;
  dif->tv_usec = end->tv_usec - start->tv_usec;
  if (dif->tv_usec < 0) {
    dif->tv_usec += 1000000;
    dif->tv_sec -= 1;
  }
  long res = dif->tv_sec * 1000000 + dif->tv_usec;
#ifdef DEBUG
  printf("Result time dif: %ld\n", res);
#endif
  return res;
}