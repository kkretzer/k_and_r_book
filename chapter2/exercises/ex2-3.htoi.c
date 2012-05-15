#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000    /* maximum input line size */

main()
{
    char hex[MAXLINE], h;
    int dec, d, len, i;
    i = dec = 0;

    printf("%s:\n", "Enter hex number");
    len = getline(hex, MAXLINE);

    if (len >= 2 && hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
    {
        i = 2;
    }

    for (; i < len; ++i)
    {
        if (hex[i] == '\n')
        {
            break;
        }
        h = hex[i];
        if (h >= '0' && h <= '9')
        {
            d = h - '0';
        }
        else if (h >= 'a' && h <= 'f')
        {
            d = 10 + h - 'a';
        }
        else if (h >= 'A' && h <= 'F')
        {
            d = 10 + h - 'A';
        } else
        {
            printf("%s\n", "error: invalid hexadecimal number");
            exit(1);
        }
        dec = dec*16 + d;
    }

    printf("Decimal:\n%d\n", dec);
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    {
        s[i] = c;
    }

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
