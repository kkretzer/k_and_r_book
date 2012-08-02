#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct nlist {      /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

char openstring = 0;    /* flags if currently processed words are part of a string,
                            and whether it's a single or double quoted constant */
char comment = 0;       /* flags if currently processed words are part of a comment,
                            1=//-style comment, 2=block comment */
int preprocessor = 0;   /* flags if currently processed words are part of preprocessor control line,
                            both 1 and 2 mean 'these are preprocessing words',
                            2 also means 'we *just* started a preprocessor line' */
int isdefine= 0;        /* flags if we've found a #define macro definition */

char *mystrdup(char *);
unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int getword(char *, int);

main()
{
    char word[MAXWORD], defn[MAXWORD], temp[MAXWORD];
    struct nlist *macro;
    while (getword(word, MAXWORD) != EOF) {
        if (isdefine) {
            printf("%s", word);
            getword(word, MAXWORD);
            printf("%s", word);
            getword(temp, MAXWORD);
            for (; isdefine; getword(temp, MAXWORD)) {
                strcat(defn, temp);
            }
            printf("%s", defn);
            install(word, defn);
        } else {
            macro = lookup(word);
            if (macro != NULL) {
                printf("%s", macro->defn);
            } else {
                printf("%s", word);
            }
        }
    }
}

/* hash:  form hash value for string */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;  /* found */
        }
    }
    return NULL; /* not found */
}

/* install:  put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {  /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = mystrdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {    /* already here */
        free((void *) np->defn);    /* free previous defn */
    }
    if ((np->defn = mystrdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

/* NOTE mystrdup is function part of string.h, so renaming it to mystrdup */
/* mystrdup:  make a duplicate of s */
char *mystrdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{

    int c, getch(void);
    void ungetch(int);
    char *w = word;
    int newline = 0;

    while (isspace(c = getch())) {
        if (c == '\n') {
            if (isdefine) {
                ungetch(c);
                isdefine = 0;
                *w = '\0';
                return '\0';
            }
            newline = 1;
            preprocessor = 0;       /* preprocessor lines end after newline */
            if (comment == 1) {     /* if we see newline at end of a //-style comment */
                comment = 0;
            }
        }
        printf("%c", c);
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalnum(c)) {
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
            isdefine = 1;
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
