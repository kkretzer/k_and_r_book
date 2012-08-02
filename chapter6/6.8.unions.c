#include <stdio.h>

main()
{
    union {
        long lval;
        int ival;
        char cval;
    } u;

    u.cval = 'K';
    printf("u.lval = %ld\n", u.lval);
    printf("u.ival = %d\n", u.ival);
    printf("u.cval = %c\n", u.cval);

    u.ival = 69;
    printf("u.lval = %ld\n", u.lval);
    printf("u.ival = %d\n", u.ival);
    printf("u.cval = %c\n", u.cval);

    u.lval = 1000000000000;
    printf("u.lval = %ld\n", u.lval);
    printf("u.ival = %d\n", u.ival);
    printf("u.cval = %c\n", u.cval);
}
