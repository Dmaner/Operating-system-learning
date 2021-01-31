#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 4096

static void sig_int(int);

int main() {
  char buf[MAXLINE];
  pid_t pid;
  int status;

  if (signal(SIGINT, sig_int) == SIG_ERR) {
    fprintf(stderr, "signal error\n");
    exit(1);
  }

  printf("%% ");
  while (fgets(buf, MAXLINE, stdin) != NULL) {
    if (buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = 0;
    if ((pid = fork()) < 0) {
      fprintf(stderr, "fork error!\n");
    } else if (pid == 0) {
      execlp(buf, buf, (char *)0);
      fprintf(stderr, "couldn't execute: %s\n", buf);
      exit(127);
    }

    // parents
    if ((pid = waitpid(pid, &status, 0)) < 0) {
      fprintf(stderr, "waitpid error\n");
      exit(1);
    }
    printf("%% ");
  }
  exit(0);
}

void sig_int(int signo) { printf("\ninterrupt\n"); }