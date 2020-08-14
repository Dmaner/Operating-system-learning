#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define NUMS_THREADS 10

void* print_hello_world(void *id)
{
    printf("Hello world --from thread %d\n", id);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUMS_THREADS];
    int status, i;
    for (int i = 0; i < NUMS_THREADS; i++)
    {
        printf("Create thread %d\n", i);
        status = pthread_create(&threads[i], NULL, print_hello_world, (void*)i);

        if (status != 0)
        {
            printf("Error!! --from thread %d",i);
            exit(-1);
        }
    }
    exit(NULL);
}
