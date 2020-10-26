#include <stdio.h>

#include "apue.h"

static void sig_int(int signo) { pr_mask("'n function in sig_int:"); }
int main(void) {
  sigset_t newmask, oldmask, waitmask;
  pr_mask("program start:");
  if (signal(SIGINT, sig_int) == SIG_ERR) err_sys("signal SIGINT error");

  sigemptyset(&waitmask);
  sigaddset(&waitmask, SIGUSR1);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGINT);

  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask)) err_sys("SIG_BLOCK error");
  pr_mask("in the critical region:");

  if (sigsuspend(&waitmask) != -1) err_sys("sigsuspen error");
  pr_mask("after return from sigsuspend");

  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK errror");
  pr_mask("program exit: ");
  exit(0);
}