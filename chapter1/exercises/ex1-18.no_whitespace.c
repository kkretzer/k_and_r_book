#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);
int rm_whitespace(char line[], int len);

/* remove trailing blanks and tabs, as well as blank lines */
main()
{
    int len;    /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = getline(line, MAXLINE)) > 0)
    {
        len = rm_whitespace(line, len);
        if (len > 0)
        {
            printf("%s", line);
        }
    }
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
    {
        s[i] = c;
    }

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int rm_whitespace(char line[], int len)
{
    int i;
    for (i = len - 1; i >=0; --i)
    {
        if (line[i] != '\n' && line[i] != ' ' && line[i] != '\t')
        {
            break;
        }
    }
    line[i+1] = '\0';
    return i;
}
