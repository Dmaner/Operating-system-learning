#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

#include "apue.h"

int system(const char* cmdstring) {
  pid_t pid;
  int status;

  if (cmdstring == NULL) return 1;

  if ((pid = fork()) < 0)
    status = -1;
  else if (pid == 0) {
    execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
    _exit(127);  // 防止缓冲区在子进程中被冲洗
  } else {
    while (waitpid(pid, &status, 0) < 0) {
      if (errno != EINTR) {
        status = -1;
        break;
      }
    }
  }

  return status;
}

int main(int argc, char const* argv[]) {
  int status;
  if ((status = system("date")) < 0) err_sys("system failed");
  pr_exit(status);

  if ((status = system("nocmd")) < 0) err_sys("system failed");
  pr_exit(status);

  if ((status = system("ls -l .")) < 0) err_sys("system failed");
  pr_exit(status);

  return 0;
}
