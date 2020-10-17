#include "apue.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
  int c;
  char buf[4];

  if (argc != 2) err_quit("usage: ./a.out -c or -s");

  if (argv[1] == "c") {
    while ((c == fgetc(stdin)) != EOF) {
      if (fputc(c, stdout) == EOF) err_sys("putc failed");
    }
  } else {
    while (fgets(buf, 4, stdin) != NULL) {
      if (fputs(buf, stdout) == EOF) err_sys("output error");
    }
  }

  if (ferror(stdin)) err_sys("input failed");

  return 0;
}