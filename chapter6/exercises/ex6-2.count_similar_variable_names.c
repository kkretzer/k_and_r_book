#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100

struct wnode {          /* the word tree node */
    char *word;           /* pointes to the text */
    int count;            /* number of occurrences */
    struct wnode *left;   /* left child */
    struct wnode *right;  /* right child */
};

struct tnode {          /* the tree node: */
    char *varprefix;        /* points to the unique variable prefix; */
    struct wnode *words;    /* binary tree of variables starting with varprefix */
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};

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
struct key *binsearch(char *, struct key *, int);
struct tnode *addtree(struct tnode *, char *, char *);
struct wnode *addwordtree(struct wnode *, char *);
char *mystrdup(char *);
struct tnode *talloc(void);
struct wnode *walloc(void);
void wordtreeprint(struct wnode *);
void treeprint(struct tnode *);

char openstring = 0;    /* flags if currently processed words are part of a string,
                            and whether it's a single or double quoted constant */
char comment = 0;       /* flags if currently processed words are part of a comment,
                            1=//-style comment, 2=block comment */
int preprocessor = 0;   /* flags if currently processed words are part of preprocessor control line,
                            both 1 and 2 mean 'these are preprocessing words',
                            2 also means 'we *just* started a preprocessor line' */
int identicalchars = 6; /* number of first chars of variable names to match
                            can be changed by command line param */

/* print groups of variable names
    where the first N chars of the name are identical
    but the rest are different */
main(int argc, char **argv)
{
    /* ignore
        keywords
        words within strings
        words within comments */

    int intconverror;
    char *argremainder;
    char word[MAXWORD];
    struct tnode *root = NULL;
    
    if (argc == 2) {
        identicalchars = (int) strtol(argv[1], &argremainder, 0);
        intconverror = errno;
        if (intconverror > 0) {
            printf("error converting %s into an integer\n", argv[1]);
            exit(intconverror);
        } else if (strlen(argremainder) > 0) {
            printf("error - %s can't be converted to an integer\n", argv[1]);
            exit(1);
        }

    } else if (argc > 2) {
        printf("error - too many command line parameters\n");
        exit(1);
    }

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) && binsearch(word, keytab, NKEYS) == NULL && !openstring && !comment && !preprocessor) {
            root = addtree(root, word, NULL);
        }
    }
    treeprint(root);
    return 0;
}

/* binsearch:  find word in tab[0]...tab[n-1] */
struct key *binsearch(char *word, struct key *tab, int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;

    while (low < high) {
        mid = low + (high-low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0) {
            high = mid;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return NULL;
}

/* treeprint:  in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%s:\n", p->varprefix);
        wordtreeprint(p->words);
        treeprint(p->right);
    }
}

/* wordtreeprint:  in-order print of word tree p */
void wordtreeprint(struct wnode *p)
{
    if (p != NULL) {
        wordtreeprint(p->left);
        printf("\t%4d %s\n", p->count, p->word);
        wordtreeprint(p->right);
    }
}

struct tnode *addtree(struct tnode *p, char *w, char *varprefix)
{
    int cond;
    if (varprefix == NULL) {
        varprefix = (char *) malloc(identicalchars);
        strncpy(varprefix, w, identicalchars);
    }

    if (p == NULL) {
        p = talloc();
        p->varprefix = mystrdup(varprefix);
        p->words = addwordtree(p->words, w);
        p->left = p->right = NULL;
    } else {
        cond = strcmp(varprefix, p->varprefix);
        if (cond == 0) {
            addwordtree(p->words, w);
        } else if (cond < 0) {
            p->left = addtree(p->left, w, varprefix);
        } else {
            p->right = addtree(p->right, w, varprefix);
        }
    }
    return p;
}

struct wnode *addwordtree(struct wnode *p, char *w)
{
    int cond;

    if (p == NULL) {    /* a new word has arrived */
        p = walloc();   /* make a new node */
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;         /* repeated word */
    } else if (cond < 0) {  /* less than into left subtree */
        p->left = addwordtree(p->left, w);
    } else {        /* greater than into right subtree */
        p->right = addwordtree(p->right, w);
    }
    return p;
}

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
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
