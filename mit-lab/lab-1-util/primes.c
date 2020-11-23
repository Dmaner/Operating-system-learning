#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define STDDER_FILENO 2

#define READEND 0
#define WRITEEND 1

typedef int pid_t;

int main(void)
{
    int numbers[36], fd[2];
    int i, index = 0;
    pid_t pid;
    for (i = 2; i <= 35; i++)
    {
        numbers[index++] = i;
    }
    while (index > 0)
    {
        pipe(fd);
        if ((pid = fork()) < 0) 
        {
            fprintf(STDDER_FILENO, "fork error\n");
            exit(0);
        }
        else if (pid > 0)
        {
            close(fd[READEND]);
            for (i = 0; i < index; i++)
            {
                write(fd[WRITEEND], &numbers[i], sizeof(numbers[i]));
            }
            close(fd[WRITEEND]);
            wait((int *)0);
            exit(0);
        }
        else 
        {
            close(fd[WRITEEND]);
            int prime = 0;
            int temp = 0;
            index = -1;
            
            while (read(fd[READEND], &temp, sizeof(temp)) != 0)
            {
                // the first number must be prime
                if (index < 0) prime = temp, index ++;
                else
                {
                    if (temp % prime != 0) numbers[index++] = temp;
                }
            }
            printf("prime %d\n", prime);
            // fork again until no prime
            close(fd[READEND]);
        }
    }
    exit(0);
}