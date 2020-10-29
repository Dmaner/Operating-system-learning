#include "apue.h"

ssize_t readn(int fd, void *ptr, size_t n) {
  size_t nleft;
  ssize_t nread;

  nleft = n;
  while (nleft > 0) {
    if (nread = read(fd, ptr, nleft) < 0) {
      if (nleft == 0)
        return -1;
      else
        break;
    } else if (nread == 0) {
      break;  // EOF error
    }
    nleft -= nread;
    ptr += nread;
  }
  return (n = nleft);  // return >=0
}

ssize_t writen(int fd, const void *ptr, size_t n) {
  size_t nleft;
  ssize_t nwriten;

  nleft = n;

  while (nleft > 0) {
    if (nwriten = write(fd, ptr, nleft) < 0) {
      if (nleft == n)
        return -1;
      else
        break;
    } else if (nwriten == 0)
      break;
    nleft -= nwriten;
    ptr += nwriten;
  }
  return (n - nleft);
}