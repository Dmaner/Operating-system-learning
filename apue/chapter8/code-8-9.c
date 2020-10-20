#include "apue.h"

static void charatatime(char *);

int main() {
  pid_t pid;
  TELL_WAIT();
  if ((pid = fork()) < 0) {
    err_sys("fork error");
  } else if (pid == 0) {
    WAIT_PARENT();
    charatatime("output from child\n");
    // child first
    // TELL_PARENT(getpid());
  } else {
    // WAIT_CHILD();
    charatatime("output from parent\n");
    // parent first
    TELL_CHILD(pid);
  }
  exit(0);
}

static void charatatime(char *str) {
  char *ptr;
  int c;

  setbuf(stdout, NULL); /* 设置 stdout 为无缓冲 */
  for (ptr = str; (c = *ptr++) != 0;) {
    putc(c, stdout);
  }
}