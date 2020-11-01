#include "apue.h"

int main() {
  int n, a, b;
  char line[MAXLINE];

  if (setvbuf(stdin, NULL, _IOLBF, 0) != 0) err_sys("setvbuf failed");
  if (setvbuf(stdout, NULL, _IOLBF, 0) != 0) err_sys("setvbuf failed");

  while (fgets(line, MAXLINE, stdin) != NULL) {
    if (sscanf(line, "%d %d", &a, &b) == 2) {
      if (printf("sum = %d\n", a + b) == EOF) err_sys("printf failed");
    } else {
      if (printf("invalid args\n") == EOF) err_sys("printf failed");
    }
  }
}