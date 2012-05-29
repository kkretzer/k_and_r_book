#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include "calc.h"
#define MAXOP   100 /* max size of operand or operator */

/* reverse Polish calculator */
main()
{
    int type;
    double op2, last, vars[26];
    char s[MAXOP], varname;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
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
                push(vars[type - 'a']);
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
    return 0;
}
