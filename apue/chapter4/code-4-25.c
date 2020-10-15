#include "apue.h"
#define MINORBITS 20
#define MINORMASK ((1U << MINORBITS) - 1)
#define MAJOR(dev) ((unsigned int)((dev) >> MINORBITS))
#define MINOR(dev) ((unsigned int)((dev)&MINORMASK))
#define MKDEV(ma, mi) (((ma) << MINORBITS) | (mi))

int main(int argc, char const *argv[]) {
  int i;
  struct stat buf;
  for (i = 1; i < argc; i++) {
    printf("%s ", argv[i]);
    if (stat(argv[i], &buf) < 0) {
      err_ret("stat failed");
      continue;
    }
    printf("dev = %d/%d ", MAJOR(buf.st_dev), MINOR(buf.st_dev));
    if (S_ISCHR(buf.st_mode) == 0 || S_ISBLK(buf.st_mode) == 0) {
      printf(" (%s) rdev = %d/%d", S_ISCHR(buf.st_mode) ? "character" : "block",
             MAJOR(buf.st_dev), MINOR(buf.st_dev));
    }
    printf("\n");
  }
  return 0;
}
