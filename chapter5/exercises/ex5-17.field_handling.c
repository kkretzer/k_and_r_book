#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quicksort(void *lineptr[], int left, int right, int whichfield, int islast, int reverse, int (*comp)(void *, void *));
int numcmp(char *, char *);
int strcmpdirord(char *, char *);
int isnumeric(short fieldoptions);
int shouldreverse(short fieldoptions);
int ignorecase(short fieldoptions);
int directoryorder(short fieldoptions);

static int (*basestringcmp)(void*,void*) = NULL;

/* sort input lines */
main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */
    short fieldoptions[argc-1]; /* right-most 4 bits: numeric|reverse|ignorecase|directory */
    int i, j, groupstart, groupend, numfields = 0;

    for (i = 0, argv++; i < argc-1; i++, argv++) {
        if ((*argv)[0] != '-') {
            printf("invalid argument");
            exit(1);
        }
        for (j = 1; j < strlen(*argv); j++) {
            if ((*argv)[j] == 'n') {
                fieldoptions[i] &= 0x1000;
            } else if ((*argv)[j] == 'r') {
                fieldoptions[i] &= 0x0100;
            } else if ((*argv)[j] == 'f') {
                fieldoptions[i] &= 0x0010;
            } else if ((*argv)[j] == 'd') {
                fieldoptions[i] &= 0x0001;
            }
        }
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        for (i = 0; i < argc-1; i++) {
            basestringcmp = ignorecase(fieldoptions[i]) ? strcasecmp : strcmp;
            quicksort((void **) lineptr, 0, nlines-1, i, (i == argc-2), shouldreverse(fieldoptions[i]),
                (int (*)(void*,void*))(isnumeric(fieldoptions[i]) ? numcmp : directoryorder(fieldoptions[i]) ? strcmpdirord : *basestringcmp));
            groupstart = groupend = 0;
            for (j=1; j < nlines; j++) {
                if (field(i, lineptr[groupstart]) != field(i, lineptr[j])) {
                    groupend = j-1;
                    if (groupend > groupstart) {
                        quicksort((void **) lineptr, groupstart, groupend, i, (i == argc-2), shouldreverse(fieldoptions[i]),
                            (int (*)(void*,void*))(isnumeric(fieldoptions[i]) ? numcmp : directoryorder(fieldoptions[i]) ? strcmpdirord : *basestringcmp));
                    }
                    groupstart = groupend = j;
                }
            }
        }
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

int isnumeric(short fieldoptions)
{
    return (fieldoptions & 0x1000) >> 3;
}

int shouldreverse(short fieldoptions)
{
    return (fieldoptions & 0x0100) >> 2;
}

int ignorecase(short fieldoptions)
{
    return (fieldoptions & 0x0010) >> 1;
}

int directoryorder(short fieldoptions)
{
    return fieldoptions & 0x0001;
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

/* quicksort: sort v[left]...v[right] into increasing order, by field, return number of groups */
void quicksort(void *v[], int left, int right, int whichfield, int islast, int reverse, int (*comp)(void *, void *))
{
    int i, last, comparison, direction;
    void swap(void *v[], int, int);

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */

    swap(v, left, (left + right)/2);
    last = left;

    direction = reverse ? -1 : 1; /* 1 = normal sort, -1 = reverse */
    for (i = left+1; i <= right; i++)
    {
        if ((*comp)(v[i], v[left])*direction < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    quicksort(v, left, last-1, whichfield, islast, reverse, comp);
    quicksort(v, last+1, right, whichfield, islast, reverse, comp);
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
