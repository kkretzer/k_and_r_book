#include "8.7.storage_allocator.h"
#include <stdio.h>

main()
{
    char *p;
    int i;

    p = (char *) mymalloc(10);
    for (i=0; i<9; i++) {
        *(p+i) = i + 'a';
    }
    *(p+i) = '\0';

    printf("p points to %s\n", p);
    myfree(p);
}
