#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int my_dup(int oldfd, int newfd)
{
    int fd = 0;
    if (newfd < 0) 
    {
        fprintf(stderr, "new fd < 0\n");
        exit(-1);
    }
    else if (newfd == oldfd) return oldfd;

    while (1)
    {
        fd = dup(oldfd);
        if (fd == newfd) return newfd;
        else if (fd > newfd) close(newfd);
    }
}


int main(int argc, char const *argv[])
{
    int fd = 0;
    
    if ((fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC)) < 0)
    {
        fprintf(stderr,"can't open file\n");
        exit(1);
    }

    if (my_dup(fd, STDOUT_FILENO) < 0)
    {
        fprintf(stderr, "dup2 error\n");
        exit(-1);
    }

    printf("test ok");

    return 0;
}
