#include "apue.h"
#include <sys/wait.h>

int main()
{
    char buf[MAXLINE];
    FILE *fpin;

    if ((fpin = popen("./myuclc", "r")) == NULL) err_sys("popen failed");

    for (; ;)
    {
        fputs("prompt> ", stdout);
        fflush(stdout);
        if (fgets(buf, MAXLINE, fpin) == NULL) break;
        if (fputs(buf, stdout) == EOF) err_sys("puts failed");
    } 

    if (pclose(fpin) == -1) err_sys("pclose error");
    putchar('\n');
    return 0;
}