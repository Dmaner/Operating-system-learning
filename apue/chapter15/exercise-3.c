#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp = popen("dman", "r");
    if (fp == NULL) {
        printf("popen returned a null pointer ");
    } else {
        printf("popen returned a non-null pointer ");
    }
    return 0;
}