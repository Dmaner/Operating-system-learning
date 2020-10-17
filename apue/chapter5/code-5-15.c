#include "apue.h"

#define BSZ 48

void initbuffer(char*, char, int);

int main()
{
    FILE* fp;
    char buf[BSZ];

    initbuffer(buf, 'a', BSZ);

    if ((fp = fmemopen(buf, BSZ, "w+")) == NULL) err_sys("fmemopen failed");
    printf("initial buffer contents: %s\n", buf);
    fprintf(fp, "hello, world");
    printf("before flush: %s\n", buf);
    fflush(fp);
    printf("after flush: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    initbuffer(buf, 'b', BSZ);
    fprintf(fp, "hello, world");
    fseek(fp, 0, SEEK_SET);
    printf("after fseek: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));
    
    initbuffer(buf, 'c', BSZ-2);
    fprintf(fp, "hello, world");
    fclose(fp);
    printf("after fclose: %s\n", buf);
    printf("len of string in buf = %ld\n", (long)strlen(buf));

    return 0;
}

void initbuffer(char* buf, char c, int size)
{
    memset(buf, c, size-2);
    buf[size-2] = '\0';
    buf[size-1] = 'X';
}