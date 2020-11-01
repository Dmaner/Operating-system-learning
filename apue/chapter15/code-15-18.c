#include "apue.h"

static void sig_pipe(int);

int main() {
  int n, fd1[2], fd2[2];
  pid_t pid;
  char buf[MAXLINE];

  if (signal(SIGPIPE, sig_pipe) == SIG_ERR) err_sys("signal failed");

  if (pipe(fd1) < 0 || pipe(fd2) < 0) err_sys("popen failed");

  if ((pid = fork()) < 0)
    err_sys("fork failed");
  else if (pid == 0) {
    close(fd1[1]);
    close(fd2[0]);

    if (fd1[0] != STDIN_FILENO) {
      if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) err_sys("dup2 failed");
      close(fd1[0]);
    }

    if (fd2[1] != STDOUT_FILENO) {
      if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO) err_sys("dup2 failed");
      close(fd2[1]);
    }

    // if (execl("./add2", "add2", (char*) 0) < 0) err_sys("add failed");
    if (execl("./add", "add", (char*)0) < 0) err_sys("execl failed");
    exit(127);
  } else {
    close(fd1[0]);
    close(fd2[1]);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
      n = strlen(buf);
      if (write(fd1[1], buf, n) != n) err_sys("write failed");
      if ((n = read(fd2[0], buf, MAXLINE)) < 0) err_sys("read failed");
      if (n == 0) {
        err_msg("child close pipe");
        break;
      }
      buf[n] = 0;
      if (fputs(buf, stdout) == EOF) err_sys("fputs failed");
    }
    if (ferror(stdout)) err_sys("stdout failed");
    return 0;
  }
}

static void sig_pipe(int signum) {
  printf("SIGPIPE caught\n");
  exit(1);
}