#include "apue.h"

static void my_exit_1(void);
static void my_exit_2(void);

int main(int argc, char const *argv[]) {
  if (atexit(my_exit_2) != 0) err_sys("can't exit my exit 2");
  if (atexit(my_exit_1) != 0) err_sys("can't exit my exit 1");
  if (atexit(my_exit_1) != 0) err_sys("can't exit my exit 1");
  printf("main finish\n");
  return 0;
}

static void my_exit_1(void) { printf("test 1\n"); }

static void my_exit_2(void) { printf("test 2\n"); }
