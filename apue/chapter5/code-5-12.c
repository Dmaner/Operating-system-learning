#include "apue.h"

int main(int argc, char const *argv[])
{
    char name[L_tmpnam];
    char line[MAXLINE];
    FILE* fp;

    printf("%s\n", tmpnam(NULL));
    tmpnam(name);
    printf("%s\n", name);
    if ((fp = tmpfile()) == NULL) err_sys("tmpfile failed");
    fputs("one line of output\n", fp);
    
    rewind(fp); // 回到文件开头

    if (fgets(line, sizeof(line), fp) == NULL) err_sys("fgets failed");

    fputs(line, stdout);

    return 0;
}
