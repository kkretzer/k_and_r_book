#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct nlist {      /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

char *mystrdup(char *);
unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

main()
{
    install("foo", "1");
    printf("'foo' = %s\n", lookup("foo")->defn);
    install("bar", "2345");
    install("foo", "lakdsjf");

    printf("'foo' = %s\n", lookup("foo")->defn);
    printf("'bar' = %s\n", lookup("bar")->defn);
    if (lookup("baz") == NULL) {
        printf("'baz' = NULL\n");
    }
    
    /* '&' will have same hash value as 'foo', so will cause '&' to be linked to 'foo' */
    install("&", "ahoy hoy");
    printf("'&' = %s\n", lookup("&")->defn);
    printf("undef &\n");
    undef("&");
    if (lookup("&") == NULL) {
        printf("'&' = NULL\n");
    } else {
        printf("'&' = %s\n", lookup("&")->defn);
    }
    printf("'foo' = %s\n", lookup("foo")->defn);
    printf("'bar' = %s\n", lookup("bar")->defn);
}

void undef(char *s)
{
    struct nlist **np, *cp, *tmp;

    tmp = lookup(s);
    np = &tmp;
    if (*np != NULL) {
        if ((cp = (*np)->next) != NULL) {
            hashtab[hash(cp->name)] = cp;
        }
        free((void *) (*np)->name);
        free((void *) (*np)->defn);
        free((void *) *np);
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
