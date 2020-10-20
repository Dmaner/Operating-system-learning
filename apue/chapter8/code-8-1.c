#include "apue.h"

int global_val = 2;
char buffer[] = "a write to stdout\n";

int main(int argc, char const *argv[]) {
  int var;
  pid_t pid;
  var = 88;
  if (write(STDOUT_FILENO, buffer, sizeof(buffer) - 1) != sizeof(buffer) - 1)
    err_sys("write error");

  printf("before fork\n");
  if ((pid = fork()) < 0)
    err_sys("fork failed");
  else if (pid == 0) {
    var++;
    global_val++;
  } else {
    sleep(2);
  }

  printf("pid = %ld, var = %d, global var = %d\n", (long)getpid(), var,
         global_val);

  return 0;
}
