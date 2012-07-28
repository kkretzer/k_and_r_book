#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

#define NKEYS (sizeof(keytab)/sizeof(keytab[0]))

int getword(char *, int);
int binsearch(char *, struct key *, int);

char openstring = 0;    /* flags if currently processed words are part of a string,
                            and whether it's a single or double quoted constant */
char comment = 0;       /* flags if currently processed words are part of a comment,
                            1=//-style comment, 2=block comment */
int preprocessor = 0;   /* flags if currently processed words are part of preprocessor control line,
                            both 1 and 2 mean 'these are preprocessing words',
                            2 also means 'we *just* started a preprocessor line' */

/* count C keywords */
main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !openstring && !comment && !preprocessor) {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    return 0;
}

/* binsearch:  find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
    /* needs to handle:
        underscores
        string constants
        comments
        preprocessor control lines
    */

    int c, getch(void);
    void ungetch(int);
    char *w = word;
    int newline = 0;

    while (isspace(c = getch())) {
        if (c == '\n') {
            newline = 1;
            preprocessor = 0;       /* preprocessor lines end after newline */
            if (comment == 1) {     /* if we see newline at end of a //-style comment */
                comment = 0;
            }
        }
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c)) {
        if (!comment && !openstring && newline && c == '#') {
            preprocessor = 2; /* 2 = last word found was the start of a preprocessor line */
        }
        if (!comment && !preprocessor && (c == '"' || c == '\'')) {
            openstring = (openstring == c) ? 0 : c;
        }
        if (!openstring && !preprocessor) {
            if (!comment && c == '/') {
                if ((c = getch()) == '/') {
                    comment = 1;    /* we've found the start of a //-style comment */
                } else if (c == '*') {
                    comment = 2;    /* we've found the start of a block comment */
                } else {
                    ungetch(c);
                }
            } else if (comment == 2 && c == '*') {
                if ((c = getch()) == '/') {
                    comment = 0;    /* we've found the end of a block comment */
                } else {
                    ungetch(c);
                }
            }
        }
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            if (*w != '_') {
                ungetch(*w);
                break;
            }
        }
    }
    *w = '\0';
    if (preprocessor == 2) {
        if (strcmp(word, "define") == 0) {
            preprocessor = 0;   /* we do want to find keywords in #define macros */
        } else {
            preprocessor = 1;
        }
    }
    return word[0];
}

#define BUFSIZE 100
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
