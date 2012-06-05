#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define NUMBER  '0' /* signal that a number was found */
#define BUFSIZE 100

int getline(char *s, int lim);
void itoa(int n, char *s);
void reverse(char *s);
int strindex(char *source, char *searchfor);
int getop(char *);
int getch(void);
void ungetch(int);

main()
{
    char s[MAXLINE], s2[MAXLINE], s3[] = "ahoy hoy", s4[] = "oy", s5[MAXLINE];
    int len, n = 12345, op;
    printf("Enter some text, testing getline:\n");
    len = getline(s, MAXLINE);
    printf("echoing:\n%s\n", s);

    printf("converting the number %d to a string:\t", n);
    itoa(n, s2);
    printf("%s\n", s2);

    printf("index of '%s' in '%s': %d\n", s4, s3, strindex(s3, s4));
    printf("index of '%s' in '%s': %d\n", s4, s, strindex(s, s4));

    printf("Enter reverse Polish notation calculator input:\n");
    while ((op = getop(s5)) != EOF)
    {
        printf("op = ");
        if (op)
        {
            printf("%c", op);
        }
        else
        {
            printf("%s", s5);
        }
        printf("\n");
    }
}

/* getline: read a line into s, return length */
int getline(char *s, int lim)
{
    int c;
    char *sbeg = s;

    while (--lim > 0 && (c=getchar()) !=EOF && c != '\n')
    {
        *s++ = c;
    }

    if (c == '\n')
    {
        *s++ = c;
    }
    *s = '\0';
    return s - sbeg;
}

/* convert n to characters in s, handle maximum negative value for ints */
void itoa(int n, char *s)
{
    int sign;
    char *sbeg = s;

    sign = (n < 0) ? -1 : 1;
    do {
        *s++ = (n % 10 * sign) + '0';
    } while ((n /= 10) != 0);
    if (sign == -1)
        *s++ = '-';
    *s = '\0';
    reverse(sbeg);
}

/* reverse: reverse string s in place */
void reverse(char *s)
{
    int c;
    char *e;

    for (e = s + strlen(s)-1; s < e; s++, e--)
    {
        c = *s;
        *s = *e;
        *e = c;
    }
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
    char *g, *sbeg = s, *tbeg = t;

    for (; *s != '\0'; s++)
    {
        for (g = s, t = tbeg; *t != '\0' && *g == *t; g++, t++)
        {
            ;
        }
        if (t > tbeg && *t == '\0')
        {
            return s - sbeg;
        }
    }

    return -1;
}


/* getop: get next operator or numeric operand */
int getop(char *s)
{
    int i, c;

    while ((*s = c = getch()) == ' ' || c == '\t')
    {
        ;
    }

    *(s+1) = '\0';
    if (!isdigit(c) && c != '.')
    {
        return c;   /* not a number */
    }
    i = 0;
    if (isdigit(c)) /* collect integer part */
    {
        while (isdigit(*++s = c = getch()))
        {
            ;
        }
    }
    if (c == '.')   /* collect fraction part */
    {
        while (isdigit(*++s = c = getch()))
        {
            ;
        }
    }
    *s = '\0';
    if (c != EOF)
    {
        ungetch(c);
    }
    return NUMBER;
}

char buf[BUFSIZE];  /* buffer for ungetch */
char *bufp = buf;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > buf) ? *--bufp : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if ((bufp - buf) >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    } else {
        *bufp++ = c;
    }
}
