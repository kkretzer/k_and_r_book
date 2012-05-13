#include <stdio.h>

/* print horizontal histogram for the length of each word */
main()
{
    int c, prevc, wl, i;
    prevc = EOF;
    wl = 0;

    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n')
        {
            ++wl;
        }
        else if (prevc != ' ' && prevc != '\t' && prevc != '\n')
        {
            for (i = 0; i < wl; ++i)
            {
                putchar('-');
            }
            putchar('\n');
            wl = 0;
        }
        prevc = c;
    }
}
