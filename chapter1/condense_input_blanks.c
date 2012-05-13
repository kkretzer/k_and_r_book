#include <stdio.h>

/* replace multiple blank chars with a single blank */
main()
{
    int c, prevc;
    prevc = EOF;

    while ((c = getchar()) != EOF)
    {
        if (c != ' ' || prevc != ' ')
            putchar(c);
        prevc = c;
    }
}
