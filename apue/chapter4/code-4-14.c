#include "apue.h"
#include <fcntl.h>
int main()
{
    if (open("test-4-9", O_RDWR) < 0) err_sys("open error");
    
    if (unlink("test-4-9") < 0) err_sys("error unlink");

    printf("file unlink\n");
    sleep(5);
    printf("done\n");
    return 0;
}