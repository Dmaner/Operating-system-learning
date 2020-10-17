#include "apue.h"

void my_set_buf(FILE* restrict fp, char* restrict buf) {
  if (buf == NULL || fp == stderr) {
    if (setvbuf(fp, NULL, _IONBF, 0) != 0) err_sys("setbuf _IONBF failure");
    return;
  }
  int file = fileno(fp);
  struct stat st;
  if (fstat(file, &st) == -1) err_sys("fstat failed");
  if (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode) || S_ISCHR(st.st_mode) ||
      S_ISBLK(st.st_mode)) {
    if (setvbuf(fp, buf, _IO_LINE_BUF, BUFSIZ) != 0)
      err_sys("setvbuf _IO_LBF failed");
  } else {
    if (setvbuf(fp, buf, _IOFBF, BUFSIZ) != 0) err_sys("setvbuf _IOFBF failed");
  }
}