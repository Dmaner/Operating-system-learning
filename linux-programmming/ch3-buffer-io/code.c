#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>

#define LINE_MAX 30

int main(int argc, char const* argv[]) {
  char s[LINE_MAX];
  FILE* fp = fopen("./test.txt", "r");
  FILE* fp2 = fopen("./test2.txt", "w");

  if (fp == NULL) {
    perror("Can't open file");
    return -1;
  }
  if (fgets(s, LINE_MAX, fp) != NULL) {
    puts(s);
    fputs(s, fp2);
  }
  fclose(fp);
  return 0;
}
