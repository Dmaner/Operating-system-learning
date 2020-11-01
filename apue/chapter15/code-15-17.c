#include "apue.h"

int main() {
  int n, a, b;
  char line[MAXLINE];

  while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0) {
    line[n] = 0;
    if (sscanf(line, "%d %d", &a, &b) == 2) {
      sprintf(line, "%d\n", a + b);
      n = strlen(line);
      if (write(STDOUT_FILENO, line, n) != n) err_sys("write failed");
    } else {
      if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
        err_sys("failed to write error");
    }
  }
}