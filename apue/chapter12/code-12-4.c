#include <pthread.h>

#include "apue.h"

int makethread(void* (*fn)(void*), void* arg) {
  int err;
  pthread_t tid;
  pthread_attr_t attr;

  if ((err = pthread_attr_init(&attr)) != 0) return err;
  if ((err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)) == 0)
    err = pthread_create(&tid, &attr, fn, arg);
  pthread_attr_destroy(&attr);
  return err;
}