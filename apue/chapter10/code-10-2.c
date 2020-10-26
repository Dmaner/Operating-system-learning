#include "apue.h"

static void sig_handler(int);

int main(int argc, char const *argv[]) {
  if (signal(SIGUSR1, sig_handler) == SIG_ERR) err_sys("can't catch usr 1");
  if (signal(SIGUSR2, sig_handler) == SIG_ERR) err_sys("can't catch usr 2");
  for (;;) pause();
  return 0;
}

static void sig_handler(int signum) {
  if (signum == SIGUSR1)
    printf("received siguser 1\n");
  else if (signum == SIGUSR2)
    printf("received siguser 2\n");
  else
    err_dump("receviced signal %d\n", signum);
}