#include <fcntl.h>

#include "apue.h"

int main(int argc, char const *argv[]) {
  int fd;
  char buf1[] = "abcdefghij";
  char buf2[] = "ABCDEFGHIJ";

  if ((fd = creat("hole.file", FILE_MODE)) < 0) err_sys("create failed");

  if (write(fd, buf1, 10) != 10) err_sys("wirte buf 1 failed");

  if (lseek(fd, 16394, SEEK_CUR) == -1) err_sys("seek failed");

  if (write(fd, buf2, 10) != 10) err_sys("write buf 2 failed");

  return 0;
}
