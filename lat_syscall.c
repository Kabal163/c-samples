#include "lib_time.h"
#include <fcntl.h>
#include <malloc/malloc.h>
#include <sched.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

static struct timeval dif, start, end;

int main(int ac, char **av) {
  int iterations;
  void *buf[0];

  if (ac < 3) {
    write(STDERR_FILENO, "Usage: fork_example [-I iterations]\n", 36);
    exit(1);
  }

  for (int i = 1; i < ac; i++) {
    if (strcmp(av[i], "-I") == 0) {
      iterations = atoi(av[++i]);
    }
  }
#ifdef DEBUG
  printf("Amount of iterations: %d\n", iterations);
#endif

  gettimeofday(&start, (struct timezone *)0);
  for (int i = 0; i < iterations; i++) {
    read(STDIN_FILENO, buf, 0);
  }
  gettimeofday(&end, (struct timezone *)0);

  double avg_time = tv_dif(&dif, &start, &end) / ((double)iterations);
  printf("Average time: %lf\n", avg_time);

  return 0;
}