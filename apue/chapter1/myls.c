#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *drip;
    if (argc != 2)
    {
        fprintf(stderr, "Usage : ls any directory name\n");
        exit(1);
    }
    if ((dp = opendir(argv[1])) == NULL)
        fprintf(stderr, "Can't open %s\n", argv[1]);
    while ((drip = readdir(dp)) != NULL)
        printf("%s\n", drip->d_name);
    closedir(dp);
    exit(0);
}