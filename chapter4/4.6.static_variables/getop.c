#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
    {
        ;
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-' && c != '+')
    {
        if (c == ':')
        {
            s[0] = getch();
            return ASSIGNVAR;
        }
        return c;   /* not a number */
    }
    i = 0;
    if (c == '-' || c == '+')
    {
        c = getch();
        if (c == ' ' || c == '\t' || c == '\n')
        {
            ungetch(c);
            return s[i];
        }
        s[++i] = c;
    }
    if (isdigit(c)) /* collect integer part */
    {
        while (isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    if (c == '.')   /* collect fraction part */
    {
        while (isdigit(s[++i] = c = getch()))
        {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }
    return NUMBER;
}
