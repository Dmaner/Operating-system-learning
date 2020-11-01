#include <sys/wait.h>

#include "apue.h"

#define DEF_PAGER "${PAGER:-more}"

int main(int argc, char const *argv[]) {
  char buffer[MAXLINE];
  FILE *fpin, *fpout;

  if (argc != 2) err_sys("usage: ./a.out <pathname>");

  if ((fpin = fopen(argv[1], "r")) == NULL) err_sys("read %s failed", argv[1]);

  if ((fpout = popen(DEF_PAGER, "w")) == NULL) err_sys("popen failed");

  while (fgets(buffer, MAXLINE, fpin) != NULL) {
    if (fputs(buffer, fpout) == EOF) err_sys("fputs failed");
  }

  if (ferror(fpin)) err_sys("fgets failed");

  if (pclose(fpout) == -1) err_sys("close failed");

  return 0;
}
