#include <sys/wait.h>

#include "apue.h"

char* env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main() {
  int status;
  pid_t pid;
  if ((pid = fork()) < 0)
    err_sys("fork failed");
  else if (pid == 0) {
      printf("pid = %ld execle\n", (long)getpid());
    if (execle("/mnt/a/Linux/Operating-system-learning/apue/chapter8/echoall",
               "echoall", "myarg1", "MY ARG2", (char*)0, env_init))
      err_sys("execle failed");
  }
  if (waitpid(pid, NULL, 0) < 0) err_sys("wait failed");
  if ((pid = fork()) < 0)
    err_sys("failed");
  else if (pid == 0) {
      printf("pid = %ld execlp\n", (long)getpid());
    if (execlp("./echoall", "echoall", "only 1 arg", (char*)0))
      err_sys("execlp error");
  }
  if (waitpid(pid, NULL, 0) < 0) err_sys("wait failed");
  exit(0);
}