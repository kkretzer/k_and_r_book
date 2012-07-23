#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *lineptr[], int left, int right, int reverse, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmpdirord(char *, char *);

static int (*basestringcmp)(void*,void*) = NULL;

/* sort input lines */
main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    int numeric = 0;    /* 1 if numeric sort */
    int reverse = 0;    /* 1 if reverse sort */
    int ignorecase = 0; /* 1 if ignoring case */
    int directory = 0;  /* 1 if directory order */
    int i;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            numeric = 1;
        } else if (strcmp(argv[i], "-r") == 0) {
            reverse = 1;
        } else if (strcmp(argv[i], "-f") == 0) {
            ignorecase = 1;
        } else if (strcmp(argv[i], "-d") == 0) {
            directory = 1;
        }
    }
    basestringcmp = ignorecase ? strcasecmp : strcmp;
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        quicksort((void **) lineptr, 0, nlines-1, reverse,
            (int (*)(void*,void*))(numeric ? numcmp : directory ? strcmpdirord : *basestringcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max lnegth of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
    {
        printf("%s\n", *lineptr++);
    }
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) /* it fits */
    {
        allocp += n;
        return allocp - n; /* old p */
    }
    else
    {
        return 0;
    }
}

/* getline: read a line into s, return length */
int getline(char *s, int lim)
{
    int c;
    char *sbeg = s;

    while (--lim > 0 && (c=getchar()) !=EOF && c != '\n')
    {
        *s++ = c;
    }

    if (c == '\n')
    {
        *s++ = c;
    }
    *s = '\0';
    return s - sbeg;
}

/* quicksort: sort v[left]...v[right] into increasing order */
void quicksort(void *v[], int left, int right, int reverse, int (*comp)(void *, void *))
{
    int i, last, direction = (reverse) ? -1 : 1; /* 1 = normal sort, -1 = reverse */
    void swap(void *v[], int, int);

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
    {
        if ((*comp)(v[i], v[left])*direction < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quicksort(v, left, last-1, reverse, comp);
    quicksort(v, last+1, right, reverse, comp);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* strcmpdirord: compare s1 and s2 in directory order */
int strcmpdirord(char *s1, char *s2)
{
    int i, j;
    char s1cpy[strlen(s1)], s2cpy[strlen(s2)];

    for (i=0, j=0; i < strlen(s1); i++) {
        if (s1[i] == ' ' || (s1[i] >= 'a' && s1[i] <= 'z') || (s1[i] >= 'A' && s1[i] <= 'Z') || (s1[i] >= '0' && s1[i] <= '9')) {
            s1cpy[j++] = s1[i];
        }
    }
    for (i=0, j=0; i < strlen(s2); i++) {
        if (s2[i] == ' ' || (s2[i] >= 'a' && s2[i] <= 'z') || (s2[i] >= 'A' && s2[i] <= 'Z') || (s2[i] >= '0' && s2[i] <= '9')) {
            s2cpy[j++] = s2[i];
        }
    }
    return (*basestringcmp)(s1cpy, s2cpy);
}
