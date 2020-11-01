#include "apue.h"

static int pfd1[2], pfd2[2];

void TELL_WAIT(void) {
  if (pipe(pfd1) < 0 || pipe(pfd2) < 0) err_sys("pipe failed");
}

void TELL_PARENT(pid_t pid) {
  if (write(pfd2[1], "c", 1) != 1) err_sys("child write failed");
}

void WAIT_PARENT(void) {
  char c;
  if (read(pfd1[0], &c, 1) != 1) err_sys("wait for parent failed");
  if (c != 'p') err_sys("child recevied error character");
}

void TELL_CHILD(pid_t pid) {
  if (write(pfd1[1], "p", 1) != 1) err_sys("parent write failed");
}

void WAIT_CHILD(void) {
  char c;
  if (read(pfd2[0], &c, 1) != 1) err_sys("wait for child failed");
  if (c != 'c') err_sys("parent recevied error character");
}