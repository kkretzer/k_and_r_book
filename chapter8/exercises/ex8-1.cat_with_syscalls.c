#include <stdio.h>
#include <fcntl.h>

#define BUFFSIZE 1000

/* cat:  concatenate files, version 2 */
main(int argc, char *argv[])
{
    int fd;
    void filecopy(int, int);
    if (argc ==1) { /* no args; copy standard input */
        filecopy(0, 1);
    } else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                printf("cat: can't open %s\n", *argv);
                return 1;
            } else {
                filecopy(fd, 1);
                close(fd);
            }
        }
    }
    return 0;
}


/* filecopy:    copy file ifd to file ofd */
void filecopy(int ifd, int ofd)
{
    char buf[BUFFSIZE];
    int n;

    while ((n = read(ifd, buf, BUFFSIZE)) > 0) {
        write(ofd, buf, n);
    }
}
