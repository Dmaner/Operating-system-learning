#include <fcntl.h>

#include "apue.h"

int main(int argc, char const *argv[]) {
  mode_t RWRWRW = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  umask(0);
  if (creat("test-4-9", RWRWRW) < 0) err_sys("creat failed");
  umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  if (creat("test-4-9-2", RWRWRW) < 0) err_sys("creat failed");
  return 0;
}
