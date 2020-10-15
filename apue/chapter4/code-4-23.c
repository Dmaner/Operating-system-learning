#include "apue.h"

int main()
{
    if (chdir("/asasd") < 0) err_sys("failed");
    printf("chdir to /tmp succeeded\n");
    return 0;
}