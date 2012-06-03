#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

int getint(int *);
int getch(void);
void ungetch(int);

main()
{
    int *pn, x = 0;
    pn = &x;
    printf("Enter some text with integers:\n");
    while (getint(pn) != EOF)
    {
        printf("Parsed %d from your input.\n", *pn);
    }
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
    {
        printf("skipping white space\n");
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        char s = c;
        c = getch();
        if (!isdigit(c))
        {
            ungetch(s);
            ungetch(c);
            return c;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
    {
        *pn = 10 * *pn + (c - '0');
    }
    *pn *= sign;
    if (c != EOF)
    {
        ungetch(c);
    }
    return c;
}

static char buf[BUFSIZE];  /* buffer for ungetch */
static int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    int bufgtzero = (bufp > 0);
    int ri = bufgtzero ? buf[--bufp] : getchar();
    return ri;
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
