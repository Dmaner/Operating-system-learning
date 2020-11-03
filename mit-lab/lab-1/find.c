#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

#define STDDER_FILENO 2
#define O_RDONLY 0

char* fmtname(char * path)
{
    static char buf[DIRSIZ+1];
    char *p;
    
    for (p = path + strlen(path); p >= path && *p != '/'; p--);
    p ++;
    if (strlen(p) >= DIRSIZ) return p;
    memmove(buf, p, strlen(p));
    buf[strlen(p)] = 0;
    return buf;
}

void find(char* path, char *name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    
    if ((fd = open(path, O_RDONLY)) < 0)
    {
        fprintf(STDDER_FILENO, "find open %s error\n", path);
        exit(1);
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(STDDER_FILENO, "fstat %s error\n", path);
        close(fd);
        exit(1);
    }

    switch (st.type)
    {
    case T_FILE: // if file check the name
        if (strcmp(fmtname(path), name) == 0) printf("%s\n", path);
        break;
    
    case T_DIR: // if directory recursive call find
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf))
        {
            fprintf(STDDER_FILENO, "find: path too long\n");
            break;
        }

        // add '/'
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            // inum == 0 means invalid directory entry
            if (de.inum == 0) continue;

            // add de.name to path
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            
            // don't find . and ..
            if (!strcmp(de.name, ".") || !strcmp(de.name, "..")) continue;
            
            // recursive call find
            find(buf, name);
        }
        break;
    }
    close(fd);
}


int main(int argc, char *argv[])
{
    if (argc != 3) 
    {
        fprintf(STDDER_FILENO, "usage: find <path> <name>\n");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}
