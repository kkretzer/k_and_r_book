#include <stdio.h>
#define MAXLINE 1000    /* maximum input line size */

int getline(char line[], int maxline);
void reverse(char line[], int len);

/* reverse each line of input */
main()
{
    int len;    /* current line length */
    char line[MAXLINE];     /* current input line */

    while ((len = getline(line, MAXLINE)) > 0)
    {
        reverse(line, len);
        printf("%s", line);
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

void reverse(char line[], int len)
{
    char tmp;
    int mid, i;
    mid = (len-2)/2;

    for (i = 0; i <= mid; ++i)
    {
        tmp = line[i];
        line[i] = line[len - 2 - i];
        line[len - 2 - i] = tmp;
    }
}
