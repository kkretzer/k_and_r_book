#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct wnode {          /* word tree: */
    char *word;             /* the word */
    int count;              /* number of occurrences */
    struct wnode *left;     /* left child */
    struct wnode *right;    /* right child */
};

int getword(char *, int);
struct wnode *addwordtree(struct wnode *, char *);
struct wnode *addsorttree(struct wnode *, struct wnode *);
void setwnode(struct wnode **, struct wnode *);
struct wnode *walloc(void);
void wordtreeprint(struct wnode *);
char *mystrdup(char *);

struct wnode *rootdesc; /* holds descending count-sorted word tree */

/* count distinct words, display in descending order of count */
main()
{
    char word[MAXWORD];
    struct wnode *rootword;
    rootword = NULL;
    rootdesc = NULL;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            rootword = addwordtree(rootword, word);
        }
    }
    setwnode(&rootdesc, rootword);
    wordtreeprint(rootdesc);
    return 0;
}

struct wnode *addwordtree(struct wnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = walloc();
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else {
        cond = strcmp(w, p->word);
        if (cond == 0) {
            p->count++;
        } else if (cond < 0) {
            p->left = addwordtree(p->left, w);
        } else {
            p->right = addwordtree(p->right, w);
        }
    }
    return p;
}

struct wnode *addsorttree(struct wnode *p, struct wnode *w)
{
    int cond;

    if (w != NULL) {
        if (p == NULL) {
            setwnode(&p, w);
        } else {
            if (w->count >= p->count) {
                p->left = addsorttree(p->left, w);
            } else {
                p->right = addsorttree(p->right, w);
            }
        }
    }
    return p;
}

void setwnode(struct wnode **p, struct wnode *w)
{
    struct wnode *wtemp;
    (*p) = w;
    wtemp = w->left;
    w->left = NULL;
    addsorttree(rootdesc, wtemp);
    wtemp = w->right;
    w->right = NULL;
    addsorttree(rootdesc, wtemp);
}

/* wordtreeprint:  in-order print of word tree p */
void wordtreeprint(struct wnode *p)
{
    if (p != NULL) {
        wordtreeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        wordtreeprint(p->right);
    }
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

struct wnode *walloc(void)
{
    return (struct wnode *) malloc(sizeof(struct wnode));
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())) {
        ;
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
            ungetch(*w);
            break;
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
