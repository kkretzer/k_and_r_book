#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct lnode {          /* line tree: */
    int line;               /* line number */
    struct lnode *left;     /* left child */
    struct lnode *right;    /* right child */
};

struct wnode {          /* word tree: */
    char *word;             /* the word */
    struct lnode *lines;    /* sorted list of line numbers the word appears on */
    struct wnode *left;     /* left child */
    struct wnode *right;    /* right child */
};

int getword(char *, int);
struct lnode *addlinetree(struct lnode *, int);
struct wnode *addwordtree(struct wnode *, char *, int);
char *mystrdup(char *);
struct lnode *lalloc(void);
struct wnode *walloc(void);
void wordtreeprint(struct wnode *);
void linetreeprint(struct lnode *);
int isnoise(char *);

int linenum = 1;   /* tracks which line number of the document we're on */

/* print all words in document with line numbers they appear on */
main()
{
    char word[MAXWORD];
    struct wnode *root;
    root = NULL;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && !isnoise(word)) {
            root = addwordtree(root, word, linenum);
        }
    }
    wordtreeprint(root);
    return 0;
}

int isnoise(char *w)
{
    int i;
    char *noisewords[] = {
        "the", "a", "an"
    };
    char **iter = noisewords;
    char **end = noisewords + sizeof(noisewords)/sizeof(noisewords[0]);
    for ( ; iter != end; iter++) {
        if (strcmp(*iter, w) == 0) {
            return 1;
        }
    }
    return 0;
}

/* wordtreeprint:  in-order print of word tree p */
void wordtreeprint(struct wnode *p)
{
    if (p != NULL) {
        wordtreeprint(p->left);
        printf("%s:\n", p->word);
        linetreeprint(p->lines);
        wordtreeprint(p->right);
    }
}

/* linetreeprint:  in-order print of line tree p */
void linetreeprint(struct lnode *p)
{
    if (p != NULL) {
        linetreeprint(p->left);
        printf("\t%4d\n", p->line);
        linetreeprint(p->right);
    }
}

struct lnode *addlinetree(struct lnode *p, int line)
{
    int cond;

    if (p == NULL) {
        p = lalloc();
        p->line = line;
        p->left = p->right = NULL;
    } if (line < p->line) {
        p->left = addlinetree(p->left, line);
    } else if (line > p->line) {
        p->right = addlinetree(p->right, line);
    }
    return p;
}

struct wnode *addwordtree(struct wnode *p, char *w, int l)
{
    int cond;

    if (p == NULL) {
        p = walloc();
        p->word = mystrdup(w);
        p->lines = addlinetree(p->lines, l);
        p->left = p->right = NULL;
    } else {
        cond = strcmp(w, p->word);
        if (cond == 0) {
            addlinetree(p->lines, l);
        } else if (cond < 0) {
            p->left = addwordtree(p->left, w, l);
        } else {
            p->right = addwordtree(p->right, w, l);
        }
    }
    return p;
}

/* lalloc:  make a lnode */
struct lnode *lalloc(void)
{
    return (struct lnode *) malloc(sizeof(struct lnode));
}

/* walloc:  make a wnode */
struct wnode *walloc(void)
{
    return (struct wnode *) malloc(sizeof(struct wnode));
}

/* NOTE strdup is function part of string.h, so renaming it to mystrdup */
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

    while (isspace(c = getch())) {
        if (c == '\n') {
            ++linenum;
        }
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c)) {
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
