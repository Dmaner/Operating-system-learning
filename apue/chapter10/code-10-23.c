#include "apue.h"
volatile sig_atomic_t quitflag;
static void sig_int(int signo) {
  if (signo == SIGINT)
    printf("\n interrupt SIGINT\n");
  else if (signo == SIGQUIT) {
    quitflag = 1;
    printf("\n interrupt SIGQUIT\n");
  }
}
int main(void) {
  sigset_t newmask, oldmask, zeromask;
  if (signal(SIGINT, sig_int) == SIG_ERR) err_sys("signal sigint error");
  if (signal(SIGQUIT, sig_int) == SIG_ERR) err_sys("signal sigquit error");

  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGQUIT);

  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    err_sys("SIG_BLOCK error");
  while (quitflag == 0) {
    sigsuspend(&zeromask);
  }
  quitflag = 0;
  
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
  exit(0);
}