#include <sys/wait.h>

#include "apue.h"

#define DEF_PAGER "/bin/more"

int main(int argc, char const *argv[]) {
  int n;
  int fd[2];
  pid_t pid;
  char buffer[MAXLINE];
  FILE *fp;
  char *pager, *argv0;

  if (argc != 2) err_sys("usage: a.out <pathname>");

  if ((fp = fopen(argv[1], "r")) == NULL) err_sys("open failed");

  if (pipe(fd) < 0) err_sys("pip failed");

  if ((pid = fork()) < 0)
    err_sys("fork failed");
  else if (pid > 0) {
    close(fd[0]);
    while (fgets(buffer, MAXLINE, fp) != NULL) {
      n = strlen(buffer);
      if (write(fd[1], buffer, n) != n) err_sys("write failed to pipe");
    }
    if (ferror(fp)) err_sys("fgets failed");

    close(fd[1]);
    if (waitpid(pid, NULL, 0) < 0) err_sys("waitpid() failed");
    return 0;
  } else {
    close(fd[1]);
    if (fd[0] != STDIN_FILENO) {
      if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) err_sys("dup2 failed");
      close(fd[0]);
    }

    if ((pager = getenv("PAGER")) == NULL) {
      pager = DEF_PAGER;
    }
    if ((argv0 = strrchr(pager, '/')) != NULL)
      argv0++;
    else
      argv0 = pager;

    if (execl(pager, argv0, (char *)0) < 0) err_sys("execl failed");
  }

  return 0;
}
