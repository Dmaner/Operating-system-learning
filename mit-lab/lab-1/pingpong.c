#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define STDDER_FILENO 2

#define READEND 0
#define WRITEEND 1

typedef int pid_t;

int main(void)
{
    // build two pipe
    int pfd[2];
    int cfd[2];

    char buf[10];
    pid_t pid;
    
    pipe(pfd);
    pipe(cfd);

    if ((pid = fork()) < 0)
    {
        fprintf(STDDER_FILENO, "fork error\n");
        exit(1);
    }
    else if (pid == 0) // child process
    {
        close(pfd[WRITEEND]);
        close(cfd[READEND]);
        read(pfd[READEND], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
        write(cfd[WRITEEND], "pong", 4);
        close(cfd[WRITEEND]);
    }
    else // parent process
    {
        close(pfd[READEND]);
        close(cfd[WRITEEND]);
        write(pfd[WRITEEND], "ping", 4);
        close(pfd[WRITEEND]);
        read(cfd[READEND], buf, 4);
        printf("%d: received %s\n", getpid(), buf);
    }

    exit(0);
}