#include <dirent.h>
#include <limits.h>

#include "apue.h"

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_FNS 4

/*contains full pathname for every file*/
static char* fullpath;
static size_t pathlen;

typedef int Myfunc(const char*, const struct stat*, int);

static Myfunc myfunc;
static int myftw(char*, Myfunc*);
static int dopath(Myfunc*);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char* argv[]) {
  int ret;
  if (argc != 2) err_quit("usage: ftw <starting-pathname>");
  ret = myftw(argv[1], myfunc);
  ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
  if (ntot == 0) ntot = 1;
  printf("regular files = %7ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
  printf("directories   = %7ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
  printf("block special = %7ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
  printf("char special  = %7ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
  printf("FIFOs         = %7ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
  printf("symbolic link = %7ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
  printf("sockets       = %7ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

  return ret;
}

static int myftw(char* pathname, Myfunc* fuc) {
  fullpath = path_alloc(&pathlen);

  if (pathlen <= strlen(pathname)) {
    pathlen = strlen(pathname) * 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL)
      err_sys("realloc failed");
  }
  strcpy(fullpath, pathname);
  return dopath(fuc);
}

static int dopath(Myfunc* func) {
  struct stat statbuf;
  struct dirent* dirp;
  DIR* dp;
  int ret, n;

  // stat error
  if (lstat(fullpath, &statbuf) < 0) return func(fullpath, &statbuf, FTW_FNS);

  // it's not directory
  if (S_ISDIR(statbuf.st_mode) == 0) return func(fullpath, &statbuf, FTW_F);

  if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) return ret;

  n = strlen(fullpath);

  // expand name
  if (n + NAME_MAX + 2 > pathlen) {
    pathlen *= 2;
    if ((fullpath = realloc(fullpath, pathlen)) == NULL)
      err_sys("realloc failed");
  }

  fullpath[n++] = '/';
  fullpath[n] = 0;

  if (chdir(".") < 0) err_quit("change to . failed");

  if ((dp = opendir(".")) == NULL)
    return func(fullpath, &statbuf, FTW_DNR);  // can't open file

  while ((dirp = readdir(dp)) != NULL) {
    if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, "..")) continue;
    strcpy(&fullpath[n], dirp->d_name);
    if ((ret = dopath(func)) != 0) break;
  }

  fullpath[n - 1] = 0;
  if (closedir(dp) < 0) err_ret("can't close directory %s", fullpath);
  if (chdir("..") < 0) err_quit("change to .. failed");
  return ret;
}

static int myfunc(const char* pathname, const struct stat* statptr, int type) {
  switch (type) {
    case FTW_F:
      switch (statptr->st_mode & S_IFMT) {
        case S_IFREG:
          nreg++;
          break;
        case S_IFBLK:
          nblk++;
          break;
        case S_IFCHR:
          nchr++;
          break;
        case S_IFIFO:
          nfifo++;
          break;
        case S_IFLNK:
          nslink++;
          break;
        case S_IFSOCK:
          nsock++;
          break;
        case S_IFDIR:
          err_dump("for S_IFDIR for %s", pathname);
      }
      break;
    case FTW_D:
      ndir++;
      break;
    case FTW_DNR:
      err_ret("can't read directory %s", pathname);
      break;
    case FTW_FNS:
      err_ret("stat error for %s", pathname);
      break;
    default:
      err_dump("error type for pathname: %s", pathname);
  }
  return 0;
}