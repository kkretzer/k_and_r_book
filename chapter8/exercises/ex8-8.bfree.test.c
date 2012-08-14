#include "ex8-8.bfree.h"
#include <stdio.h>

main()
{
    struct foo {
        int i;
        long l;
        char c;
    };
    struct foo p[1000];
    bfree(p, 1000);
}
