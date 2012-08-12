#include <stdlib.h>

#include <sys/dir.h>

#undef DIRSIZ
#define DIRSIZ 14

/* my_opendir:  open a directory for my_readdir calls */
MY_DIR *my_opendir(char *dirname)
{
    int fd;
    struct stat stbuf;
    MY_DIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1
            || fstat(fd, &stbuf) == -1
            || (stbuf.st_mode & S_IFMT) != S_IFDIR
            || (dp = (MY_DIR *) malloc(sizeof(MY_DIR))) == NULL) {
        return NULL;
    }
    dp->fd = fd;
    return dp;
}

/* my_closedir:  close directory opened by my_opendir */
void my_closedir(MY_DIR *dp)
{
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

/* my_readdir:  read directory entries in sequence */
Dirent *my_readdir(MY_DIR *dp)
{
    struct direct dirbuf;   /* local directory structure */
    static Dirent d;        /* return: portable structure */

    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) {    /* slot not in use */
            continue;
        }
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0';  /* ensure termination */
        return &d;
    }
    return NULL;
}

