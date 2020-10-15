#include "apue.h"

int main()
{
    struct stat buf;
    if (stat("test-4-9", &buf) < 0) err_sys("stat failed");

    if (chmod("test-4-9", buf.st_mode & ~ S_IWGRP) < 0) err_sys("chmod failed");

    return 0;
}