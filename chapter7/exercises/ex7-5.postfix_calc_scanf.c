#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXLINE 1000

int getop(double *, char *);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int getline(char s[], int lim);

/* reverse Polish calculator */
main()
{
    int type, i=0;
    double op2, f;
    char aline[MAXLINE], *line;
    line = aline;

    while (getline(line, MAXLINE) > 0) {
        if ((i = sscanf(line, "%lf", &f)) != EOF && i != 0) {
            line += i;
            type = NUMBER;
        } else {
            type = getchar();
        }
        while (type != EOF)
        {
            switch (type)
            {
                case NUMBER:
                    push(f);
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                    {
                        push(pop() / op2);
                    }
                    else
                    {
                        printf("error: zero divisor\n");
                    }
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break;
                default:
                    printf("error: unknown command %c\n", type);
                    break;
            }
            if ((i = sscanf(line, "%lf", &f)) != EOF && i != 0) {
                line += i;
                type = NUMBER;
            } else {
                type = getchar();
            }
        }
    }
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) !=EOF && c != '\n')
    {
        s[i++] = c;
    }

    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int sp = 0;     /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
    {
        val[sp++] = f;
    }
    else
    {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
    {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next operator or numeric operand */
int getop(double *f, char *line)
{
}

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
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
