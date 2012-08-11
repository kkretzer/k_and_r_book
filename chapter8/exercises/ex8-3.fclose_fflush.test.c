#include "ex8-3.fclose_fflush.h"

int main()
{
    int i;
    int nap = 5;
    FILE *fp = fopen("/tmp/foo", "w");
    putc(fp->fd + '0', stderr);
    for (i = 0; i <= 10; i++) {
        putc((i%26)+'a',fp);
    }
    putc('H', stderr);
    putc('O', stdout);
    putc('O', stdout);
    sleep(nap);
    fflush(NULL);
    putc('H', stderr);
    sleep(nap);
    if (fclose(fp) != 0) {
        putc('?', stderr);
    }
    if (fp->base == NULL) {
        putc('!', stderr);
    }
    fp = fopen("/tmp/bar", "w");
    putc(fp->fd + '0', stderr);
    fclose(fp);
}
