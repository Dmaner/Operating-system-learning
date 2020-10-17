## <font face="Consolas">Exercise 5.1</font>
> <font face="Consolas">see the code exc-5-1.c</font>
```c++
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
```

## <font face="Consolas">Exercise 5.2</font>
> <font face="楷体">fgets直到缓冲区满或者遇到换行符才停止，只是增加了fgets和fputs运行的次数</font>

## <font face="Consolas">Exercise 5.3</font>
> <font face="楷体">打印了空字符串</font>

## <font face="Consolas">Exercise 5.4</font>
> <font face="楷体">因为在C/C++标准中并没有char类型做出有无符号的说明，对于字符类型C/C++标准定义了三种类型：unsigned char、char、signed char。对于第一种和最后一种明确指明了其符号，而第二种则由平台自己决定。因此char可能是无符号类型，而EOF是负数，当getchar( )返回负数的EOF时，该负数EOF会被隐式转换到无符号的char，从而变成正值，因此循环条件始终成立从而导致死循环</font>


## <font face="Consolas">Exercise 5.5</font>
> <font face="楷体">当需要用getc、fgetc、getchar、fgets、gets等输入函数进行输入时，printf的内容会被刷新</font>


## <font face="Consolas">Exercise 5.5</font>
> <font face="楷体">未完成</font>
