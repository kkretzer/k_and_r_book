#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN    100
#define BUFSIZE     100

enum { NAME, PARENS, BRACKETS, CONST };

void dcl(void);
void dirdcl(void);
void funcdcl(void);

int gettoken(void);
void ungetch(int);
int tokentype;              /* type of last token */
int prevtokentype;          /* type of previous token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc, */
char constant[10];          /* will either be empty string or ' constant' */
char out[1000];             /* output string */

main() /* convert declaration to words */
{
    int c;
    while ((tokentype = gettoken()) != EOF) {     /* 1st token on line */
        if (tokentype == CONST) {
            tokentype = gettoken();
            if (tokentype != NAME) {
                printf("syntax error, expecting datatype following 'const'\n");
                continue;
            }
            strcpy(constant, " constant");
        }
        tokentype = prevtokentype = 0;
        strcpy(datatype, token);    /* is the datatype */
        out[0] = '\0';
        dcl();      /* parse rest of line */
        if (tokentype != '\n') {
            printf("syntax error\n");
            while ((c = getch()) != '\n' && c != EOF) { ; }
            ungetch(c);
        } else {
            printf("%s: %s%s %s\n", name, constant, out, datatype);
        }
        strcpy(token, "");
        strcpy(name, "");
        strcpy(datatype, "");
        strcpy(out, "");
        strcpy(constant, "");
    }
    return 0;
}

/* dcl:  parse a declarator */
void dcl(void)
{
    int ns;
    
    for (ns = 0; gettoken() == '*'; ) { /* count *'s */
        ns++;
    }
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/* dirdcl:   parse a direct declarator */
void dirdcl(void)
{
    int type;

    printf("huzzah: %c\n", tokentype);
    printf("doh:    %c\n", prevtokentype);
    if (tokentype == '(') { /* ( dcl ) */
        if (prevtokentype == NAME || prevtokentype == PARENS) {
            funcdcl();
        } else {
            dcl();
            if (tokentype != ')') {
                printf("error: missing )\n");
            }
        }
    } else if (tokentype == NAME) { /* variable name */
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
        return;
    }
    while ((type=gettoken()) == PARENS || type == BRACKETS || ((prevtokentype == NAME || prevtokentype == PARENS) && type == '(')) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else if (type == '(') {
            funcdcl();
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

/* funcdcl:  parse a function's argument types */
void funcdcl(void)
{
    int type;
    char arglist[MAXTOKEN];

    gettoken();
    while (tokentype != ')') {
        if (tokentype == '*') {
            strcat(arglist, "pointer to ");
            gettoken();
        }
        if (tokentype != NAME) {
            printf("syntax error: expected datatype inside function argument list");
            return;
        }
        strcat(arglist, token);
        if (gettoken() != ',' && tokentype != ')') {
            printf("syntax error: function argument list must be separated with commas and be closed with ')'");
            return;
        }
    }
    strcat(out, " function with arg signature (");
    strcat(out, arglist);
    strcat(out, ") returning");
}

int gettoken(void) /* return next token */
{
    int c, getch(void);
    char *p = token;
    prevtokentype = tokentype;

    while ((c = getch()) == ' ' || c == '\t') { ; }
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; ) { ; }
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        if (strcmp(token, "const") == 0) {
            return tokentype = CONST;
        } else {
            return tokentype = NAME;
        }
    } else {
        return tokentype = c;
    }
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
