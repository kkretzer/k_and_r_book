#include <stdio.h>
#include "calc.h"

#define MAXVAL  100 /* maximum depth of val stack */

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


