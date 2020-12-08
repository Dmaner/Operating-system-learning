#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define MAXLINE 512

void do_more(FILE*);
int handle_cmd(FILE*);

int main(int argc, char const* argv[]) {
  FILE* fp;
  if (argc == 1) {
    do_more(stdin);
  } else {
    for (int i = 1; i < argc; i++) {
      if ((fp = fopen(argv[1], "r")) != NULL) {
        do_more(fp);
        fclose(fp);
      } else {
        perror("do more");
        exit(1);
      }
    }
  }
  return 0;
}

void do_more(FILE* fp) {
  char line[MAXLINE];
  int num_of_lines = 0;
  int reply;
  FILE* ftty;
  if ((ftty = fopen("/dev/tty", "r")) == NULL) {
    perror("open /dev/tty");
    exit(1);
  }
  while (fgets(line, MAXLINE, fp)) {
    if (num_of_lines == PAGELEN) {
      reply = handle_cmd(ftty);
      if (reply == 0) break;
      num_of_lines -= reply;
    }
    if (fputs(line, stdout) == EOF) exit(1);
    num_of_lines++;
  }
}

int handle_cmd(FILE* fp) {
  int c;
  printf("\033[7m more?\033[m");
  while ((c = getc(fp)) != EOF) {
    if (c == 'q')
      return 0;
    else if (c == ' ')
      return PAGELEN;
    else if (c == '\n')
      return 1;
    else {
      perror("handle cmd");
      exit(1);
    }
  }
  return 0;
}