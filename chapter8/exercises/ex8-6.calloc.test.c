#include "ex8-6.calloc.h"
#include <stdio.h>

main()
{
    struct foo {
        int i;
        long l;
        char c;
    };
    struct foo *p;
    int i;

    p = (struct foo *) mycalloc(10, sizeof(struct foo));
    for (i=0; i<9; i++) {
        printf("%d - p = {%d, %ld, %c}\n", i, (p+i)->i, (p+i)->l, (p+i)->c);
    }

    for (i=0; i<9; i++) {
        (p+i)->i = i;
        (p+i)->l = i*7777;
        (p+i)->c = 'Z' - i;
    }
    for (i=0; i<9; i++) {
        printf("%d - p = {%d, %ld, %c}\n", i, (p+i)->i, (p+i)->l, (p+i)->c);
    }

    myfree(p);
}
