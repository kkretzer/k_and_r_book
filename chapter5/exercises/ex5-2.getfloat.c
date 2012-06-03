#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

int getfloat(float *);
int getch(void);
void ungetch(int);

main()
{
    float *pn, x = 0.0;
    pn = &x;
    printf("Enter some text with floats:\n");
    while (getfloat(pn) != EOF)
    {
        printf("Parsed %g from your input.\n", *pn);
    }
}

/* getfloat: get next float from input into *pn */
int getfloat(float *pn)
{
    int c, sign, fraction;
    fraction = 1;

    while (isspace(c = getch())) /* skip white space */
    {
        printf("skipping white space\n");
        ;
    }
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
    {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
        char s = c;
        c = getch();
        if (!isdigit(c) && c != '.')
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
    if (c == '.')
    {
        c = getch();
        for (; isdigit(c); c = getch(), fraction *= 10)
        {
            *pn = 10 * *pn + (c - '0');
        }
    }
    *pn /= fraction;
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
