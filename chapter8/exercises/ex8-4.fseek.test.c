#include "ex8-4.fseek.h"

int main()
{
    putc('\n', stderr);
    putc('W', stderr);
    putc('\n', stderr);
    int i;
    int nap = 3;
    FILE *fp = fopen("/tmp/foo", "w");
    for (i = 0; i < 10; i++) {
        putc((i%26)+'a',fp);
    }
    putc('H', stderr);
    sleep(nap);
    fseek(fp, 0, 0);
    putc('H', stderr);
    sleep(nap);
    putc('Z', fp);
    sleep(nap);
    fseek(fp, 2, 1);
    putc('Z', fp);
    putc('H', stderr);
    sleep(nap);
    fseek(fp, -1, 2);
    putc('Z', fp);

    /* setup the foo file for read fseek testing */
    fseek(fp, 0, 0);
    for (i = 0; i < 10; i++) {
        putc('0'+i, fp);
    }
    fclose(fp);

    putc('\n', stderr);
    putc('R', stderr);
    putc('\n', stderr);
    fp = fopen("/tmp/foo", "r");
    putc(getc(fp), stderr);
    fseek(fp, 2, 1);
    putc(getc(fp), stderr);
    fseek(fp, -2, 2);
    putc(getc(fp), stderr);
    fseek(fp, 1, 0);
    putc(getc(fp), stderr);
    fclose(fp);
}
