#define DEFAULT_STR "leeeeeeeeeeeeeeeeetcodeee"

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fancy_str(char *s);

int main(int ac, char **av) {
  char *s;

  if (ac == 3 && strcmp(av[1], "-s") == 0) {
    s = av[2];
  } else {
    s = strdup(DEFAULT_STR);
  }
  printf("Input string: %s\n", s);
  fancy_str(s);
  printf("Output string: %s\n", s);
  return 0;
}

void fancy_str(char *s) {
  char last;
  int len = strlen(s);
  int cnt = 0;
  int p_old = 0;
  int p_new = 0;
  while (p_old < len) {
    s[p_new] = s[p_old];
    if (s[p_new] == last) {
      cnt++;
    } else {
      cnt = 0;
    }
    last = s[p_new];
    if (cnt < 2) {
      p_new++;
    }
    p_old++;
  }
  s[p_new] = 0;
}
