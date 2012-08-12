#define NAME_MAX  14    /* longest filename component */
                                /* system-dependent */

typedef struct {        /* portable directory entry: */
    long ino;               /* inode number */
    char name[NAME_MAX+1];  /* name + '\0' terminator */
} Dirent;

typedef struct {        /* minimal MY_DIR: no buffering, etc */
    int fd;                 /* file descriptor for directory */
    Dirent d;               /* the directory entry */
} MY_DIR;

MY_DIR *my_opendir(char *dirname);
Dirent *my_readdir(MY_DIR *dfd);
void my_closedir(MY_DIR *dfd);
