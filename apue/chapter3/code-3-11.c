#include <fcntl.h>

#include "apue.h"

int main(int argc, char* argv[]) {
  int val;
  if (argc != 2) err_quit("lack arg");

  // 获取文件状态
  if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) err_sys("fcntl failed");

  switch (val & O_ACCMODE) {
    case O_RDONLY:
      printf("can read");
      break;
    case O_WRONLY:
      printf("can wirte");
      break;
    case O_RDWR:
      printf("can read and write");
      break;
    default:
      err_dump("unknown mode");
      break;
  }

  if (val & O_APPEND) printf(", append");
  if (val & O_NONBLOCK) printf(", nonblocking");
  if (val & O_SYNC) printf(", synchronous wirtes");

#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
  if (val & O_FSYNC) printf(", synchronous wirtes");
#endif
  printf("\n");
  return 0;
}