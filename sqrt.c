#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int l = 0;
static int r = 46340;

int mySqrt(int x);

int main(int ac, char **av) {
  if (ac < 2) {
    err(EXIT_FAILURE, "Usage: sqrt [-v value]");
  }
  if (0 == (strcmp(av[1], "-v"))) {
    int in = atoi(av[2]);
    int res = mySqrt(in);
    printf("The approximate square root of %d is %d\n", in, res);
  }
  return 0;
}

int mySqrt(int x) {
  int m;
  while (r >= l) {
    m = l + (r - l) / 2;
#ifdef DEBUG
    printf("l: %d, r:%d, p: %d, x: %d\n", l, r, m, x);
#endif
    if (x / m > m) {
      l = m + 1;
    } else if (x / m < m) {
      r = m - 1;
    } else {
      return m;
    }
  }
  if (l * l > x) {
    return l - 1;
  }
  return l;
}
