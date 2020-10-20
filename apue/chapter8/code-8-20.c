#include <sys/wait.h>

#include "apue.h"

int main(int argc, char const *argv[]) {
  pid_t pid;
  if ((pid = fork()) < 0)
    err_sys("fork failed");
  else if (pid == 0) {
    if (execl("./testinterp",
              "testinterp", "arg1", "arg2", (char *)0) < 0)
      err_sys("execl failed");
  }
  if (waitpid(pid, NULL, 0) < 0) err_sys("waitpid failed");
  return 0;
}
