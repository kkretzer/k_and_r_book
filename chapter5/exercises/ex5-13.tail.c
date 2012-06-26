#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUTLINES   10000 /* max number of lines of input */
#define MAXLEN          1000  /* maximum input line size */
#define DEFAULTNUMLINES 10    /* default number of lines to tail */

int readlines(char *lineptr[], int maxlines);
int getline(char line[], int maxline);
char *alloc(int n);
void usage(char *program);

main(int argc, char *argv[]) {
    int i, numlines = DEFAULTNUMLINES, inputlength;
    char *program = *argv, *lineptr[MAXINPUTLINES], **lineptrptr;
    lineptrptr = lineptr;

    for (i = 1; i < argc; ++i) {
        switch (argv[i][1]) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                numlines = -1 * atoi(argv[i]);
                break;
            case 'h':
                usage(program);
                exit(0);
                break;
            default:
                usage(program);
                exit(1);
                break;
        }
    }

    inputlength = readlines(lineptr, MAXLEN);
    if (numlines < inputlength) {
        lineptrptr += inputlength - numlines;
    }
    for (i = 0; i < numlines && i < inputlength; ++i) {
        printf("%s\n", *lineptrptr++);
    }
}

void usage(char *program) {
    printf("Usage: %s -n <numlines> [-h]\n", program);
    printf("\t-<numlines>\tnumber of lines from end of input to output, default is %d\n", DEFAULTNUMLINES);
    printf("\t-h         \tprint this help info\n");
}

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
