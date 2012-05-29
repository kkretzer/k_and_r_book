#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    static int hold[100];
    static int h = 0;

    while ((s[0] = c = (h>0) ? hold[h-- - h] : getch()) == ' ' || c == '\t')
    {
        ;
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-' && c != '+')
    {
        if (c == ':')
        {
            s[0] = (h>0) ? hold[h-- - h] : getch();
            return ASSIGNVAR;
        }
        return c;   /* not a number */
    }
    i = 0;
    if (c == '-' || c == '+')
    {
        c = (h>0) ? hold[h-- - h] : getch();
        if (c == ' ' || c == '\t' || c == '\n')
        {
            hold[h++] = c;
            return s[i];
        }
        s[++i] = c;
    }
    if (isdigit(c)) /* collect integer part */
    {
        while (isdigit(s[++i] = c = (h>0) ? hold[h-- - h] : getch()))
        {
            ;
        }
    }
    if (c == '.')   /* collect fraction part */
    {
        while (isdigit(s[++i] = c = (h>0) ? hold[h-- - h] : getch()))
        {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF)
    {
        hold[h++] = c;
    }
    return NUMBER;
}
