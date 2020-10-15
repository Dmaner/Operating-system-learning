#include "apue.h"

int main()
{
    char *ptr;
    size_t size;
    if (chdir("/tmp") < 0) err_sys("change directory failed");

    ptr = path_alloc(&size);
    
    if (getcwd(ptr, size) == NULL) err_sys("getcwd failed");
    printf("path: %s\n", ptr);
}