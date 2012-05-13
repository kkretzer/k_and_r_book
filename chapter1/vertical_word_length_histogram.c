#include <stdio.h>

#define MAX_WORDS 100  /* artificial upper limit on number of words this program can handle */

/* print vertical histogram for the length of each word */
main()
{
    int c, prevc, i, j, k, current, max_length;
    int wl[MAX_WORDS];
    prevc = EOF;
    current = max_length = 0;
    for (i = 0; i < MAX_WORDS; ++i)
        wl[i] = 0;

    // read in all input before outputting vertical histogram
    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n')
        {
            ++wl[current];
        }
        else if (prevc != ' ' && prevc != '\t' && prevc != '\n')
        {
            if (max_length < wl[current])
                max_length = wl[current];
            ++current;
        }
        prevc = c;
    }

    // for each row of the histogram, top to bottom
    for (i = max_length; i > 0; --i)
    {
        for (j = 0; j < current; ++j)
        {
            // fill in this bar if the jth word was as long (or as 'tall') as the ith row of the histogram
            if (wl[j] >= i)
                putchar('*');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}
