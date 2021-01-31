#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 4096

int main()
{
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = 0;
        if ((pid = fork()) < 0)
        {
            fprintf(stderr, "fork error!\n");
        }
        else if (pid == 0)
        {
            execlp(buf, buf, (char *)0);
            fprintf(stderr, "couldn't execute: %s\n", buf);
            exit(127);
        }

        // parents
        if ((pid = waitpid(pid, &status, 0)) < 0)
            fprintf(stderr, "waitpid error\n");
        printf("%% ");
    }
    exit(0);
}