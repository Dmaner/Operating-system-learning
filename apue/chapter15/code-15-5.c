#include "apue.h"

int main(int argc, char const *argv[])
{
    int n;
    int fd[2];
    pid_t pid;
    char buffer[MAXLINE];
    
    if (pipe(fd) < 0) err_sys("pipe() failed");
    
    if ((pid = fork()) < 0) err_sys("fork failed");
    else if (pid == 0) 
    {
        close(fd[0]); // close parent's read
        write(fd[1], "sent: hello world\n", 18);
    }
    else {
        close(fd[1]);
        n = read(fd[0], buffer, MAXLINE);
        write(STDOUT_FILENO, buffer, n);
    }

    return 0;
}
