#include <stdio.h>

/* print one word per line */
main()
{
    int c, prevc;
    prevc = EOF;

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\t')
            putchar(c);
        else if (prevc != ' ' && prevc != '\t')
            putchar('\n');
        prevc = c;
    }
}
