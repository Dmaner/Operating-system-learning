#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 4096
#define true 1
#define false 0
void cp(int, int);

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: cp <file 1> <file 2>\n");
    exit(-1);
  }

  int fd1, fd2;
  if ((fd1 = open(argv[1], O_RDWR)) == -1) {
    fprintf(stderr, "open file 1 failed\n");
    exit(-1);
  }

  if ((fd2 = open(argv[2], O_RDWR | O_CREAT, 0666)) == -1) {
    fprintf(stderr, "open file 2 failed\n");
    exit(-1);
  }
  cp(fd1, fd2);
  return 0;
}

void cp(int fd1, int fd2) {
  char buf[BUFF_SIZE];
  int cnt, all_cnt;
  int flag, i, cur;

  while ((cnt = read(fd1, buf, BUFF_SIZE)) != 0) {
    flag = false;
    cur = 0;
    for (int i = 0; i < cnt; i++) {
      // 空洞遇到非空洞
      if (flag == false && buf[i] != 0) {
        cur = i;
        flag = true;
        if (lseek(fd2, all_cnt + i, SEEK_SET) == -1) {
          fprintf(stderr, "lseek failed\n");
          exit(-1);
        }
      }
      // 非空洞遇到空洞
      else if (flag == true && buf[i] == 0) {
        if (write(fd2, buf + cur, i - cur) == -1) {
          fprintf(stderr, "write failed\n");
          exit(-1);
        }
        flag = false;
      }
    }

    if (cur != cnt) {
      if (write(fd2, buf + cur, cnt - cur) == -1) {
        fprintf(stderr, "write failed\n");
        exit(-1);
      }
    }
    all_cnt += cnt;
  }
}