#define MSG "Hello process!"
#define MSG_SIZE 14

#include "lib_time.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

int main(int ac, char **av) {
  int iter, procs;

  if (ac < 5) {
    err(EXIT_FAILURE, "Usage: lat_ctxswtch [-p processes] [-i iterations]");
  }

  for (int i = 1; i < ac; i++) {
    char *arg = av[i];
    if (strcmp(arg, "-i") == 0) {
      iter = atoi(av[++i]);
    }
    if (strcmp(arg, "-p") == 0) {
      procs = atoi(av[++i]);
    }
  }

#ifdef DEBUG
  printf("Number of iterations: %d, number of processes: %d\n", iter, procs);
#endif

  int **sp = malloc((sizeof(int *) + (2 * sizeof(int))) * procs);
  if (sp == NULL) {
    err(EXIT_FAILURE, "malloc(): pipes");
  }
  int *p = (int *)&sp[procs];
  char *bufs = malloc(MSG_SIZE * procs);
  if (bufs == NULL) {
    err(EXIT_FAILURE, "malloc(): message buffers");
  }

#ifdef DEBUG
  printf("Allocated memory for pipes and message buffers\n");
#endif

  for (int i = 0; i < procs; i++) {
    sp[i] = p;
    p += 2;
    if (pipe(sp[i]) < 0) {
      err(EXIT_FAILURE, "pipe()");
    }
  }

#ifdef DEBUG
  printf("All pipes has been initialized\n");
#endif

  for (int i = 0; i < procs - 1; i++) {
    pid_t pid = fork();
    if (pid < 0) {
      err(EXIT_FAILURE, "fork()");
    }
    if (pid > 0) {
#ifdef DEBUG
      printf("Process #%d has been initialized\n", i);
#endif
      int rfd, wfd;
      for (int j = 0; j < procs; j++) {
        if (j == i) {
          rfd = sp[j][0];
          close(sp[j][1]);
        } else if (j == i + 1) {
          wfd = sp[j][1];
          close(sp[j][0]);
        } else {
          close(sp[j][0]);
          close(sp[j][1]);
        }
      }
      char *buf = &bufs[i * MSG_SIZE];
      ssize_t br;
      while (1) {
        br = read(rfd, buf, MSG_SIZE);
#ifdef DEBUG
        printf("Process #%d read message: %s\n", i, buf);
#endif
        if (br == 0) {
#ifdef DEBUG
          printf("Zero bytes has been read from pipe by process #%d\n", i);
#endif
          break;
        }
        write(wfd, MSG, MSG_SIZE);
      }
      close(rfd);
      close(wfd);
      exit(0);
    }
  }

  int rfd, wfd;
  for (int i = 0; i < procs; i++) {
    if (i == procs - 1) {
      rfd = sp[i][0];
      close(sp[i][1]);
    } else if (i == 0) {
      wfd = sp[i][1];
      close(sp[i][0]);
    } else {
      close(sp[i][0]);
      close(sp[i][1]);
    }
  }
  char *buf = &bufs[(procs - 1) * MSG_SIZE];
  struct timeval *t = malloc(sizeof(struct timeval) * 3);
  if (t == NULL) {
    err(EXIT_FAILURE, "malloc(): timeval");
  }
  struct timeval *start = t;
  struct timeval *end = &t[1];
  struct timeval *dif = &t[2];
  long usec_spent;
#ifdef DEBUG
  printf("Control process is ready to send messages\n");
#endif
  for (int i = 0; i < iter; i++) {
    gettimeofday(start, NULL);
    write(wfd, MSG, MSG_SIZE);
    read(rfd, buf, MSG_SIZE);
#ifdef DEBUG
    printf("Control process read message: %s\n", buf);
#endif
    gettimeofday(end, NULL);
    usec_spent += tv_dif(dif, start, end) / procs;
  }
#ifdef DEBUG
  printf("Control process has been finished\n");
#endif
  close(rfd);
  close(wfd);

  for (int i = 0; i < procs - 1; i++) {
    wait(NULL);
  }

  double avg_time = (double)usec_spent / iter;
  printf("Elapsed time (microsec) for context switch: %f\n", avg_time);
}