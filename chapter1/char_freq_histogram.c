#include <stdio.h>

#define ASCII_CHARS 256 /* number of available ascii characters */

/* print histogram for frequency of each character */
main()
{
    int c, i, j;
    int char_freq[ASCII_CHARS];
    for (i = 0; i < ASCII_CHARS; ++i)
    {
        char_freq[i] = 0;
    }

    while ((c = getchar()) != EOF)
    {
        if (c != ' ' && c != '\t' && c != '\n')
            ++char_freq[c];
    }

    for (i = 0; i < ASCII_CHARS; ++i)
    {
        if (char_freq[i] > 0)
        {
            putchar(i);
            putchar(' ');
            for (j = 0; j < char_freq[i]; ++j)
                putchar('-');
            putchar('\n');
        }
    }
}
