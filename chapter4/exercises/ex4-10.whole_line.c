#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXLINE 1000
#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define ASSIGNVAR ':' /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100

int getline(char s[], int lim);
int getop(char line[], int linepos, char s[]);
void push(double);
double pop(void);
void printtop();
void duptop();
void swaptop2();

int optype;
/* reverse Polish calculator */
main()
{
    int linelen, linepos;
    double op2, last, vars[26];
    char line[MAXLINE], s[MAXOP], varname;

    while ((linelen = getline(line, MAXLINE)) > 0)
    {
        linepos = 0;
        while ((linepos = getop(line, linepos, s)) <= linelen)
        {
            switch (optype)
            {
                case NUMBER:
                    push(atof(s));
                    break;
                case '"':
                    duptop();
                    break;
                case '\'':
                    printtop();
                    break;
                case '!':
                    swaptop2();
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
                case '%':
                    op2 = pop();
                    if (op2 != 0.0)
                    {
                        push(((int) pop()) % (int) op2);
                    }
                    else
                    {
                        printf("error: zero divisor\n");
                    }
                    break;
                case '^':
                    op2 = pop();
                    push(pow(pop(), op2));
                    break;
                case '#':
                    push(exp(pop()));
                    break;
                case '$':
                    push(sin(pop()));
                    break;
                case ASSIGNVAR:
                    varname = s[0];
                    duptop();
                    vars[varname - 'a'] = pop();
                    break;
                case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
                case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
                case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
                case 'v': case 'w': case 'x': case 'y': case 'z':
                    push(vars[optype - 'a']);
                    break;
                case '?':
                    push(last);
                    break;
                case '\n':
                    last = pop();
                    printf("\t%.8g\n", last);
                    break;
                default:
                    printf("error: unknown command %s\n", s);
                    break;
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

void printtop()
{
    if (sp > 0)
    {
        printf("top of operand stack:\t%g\n", val[sp-1]);
    } else {
        printf("(there is no top of stack right now, it's empty)\n");
    }
}

void duptop()
{
    if (sp > 0)
    {
        push(val[sp-1]);
    }
}

void swaptop2()
{
    int tmp;
    if (sp > 1)
    {
        tmp = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = tmp;
    }
}

/* getop: get next operator or numeric operand */
int getop(char line[], int linepos, char s[])
{
    int i, c;

    while ((s[0] = c = line[linepos++]) == ' ' || c == '\t')
    {
        ;
    }

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-' && c != '+')
    {
        if (c == ':')
        {
            s[0] = line[linepos++];
            optype = ASSIGNVAR;
            return linepos;
        }
        optype = c;   /* not a number */
        return linepos;
    }
    i = 0;
    if (c == '-' || c == '+')
    {
        c = line[linepos++];
        if (c == ' ' || c == '\t' || c == '\n')
        {
            linepos--;
            optype = s[i];
            return linepos;
        }
        s[++i] = c;
    }
    if (isdigit(c)) /* collect integer part */
    {
        while (isdigit(s[++i] = c = line[linepos++]))
        {
            ;
        }
    }
    if (c == '.')   /* collect fraction part */
    {
        while (isdigit(s[++i] = c = line[linepos++]))
        {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF)
    {
        linepos--;
    }
    optype = NUMBER;
    return linepos;
}
