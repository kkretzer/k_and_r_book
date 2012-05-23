#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

void lower(char s[]);

main()
{
    char s[MAXLINE];
    int len;

    puts("Enter some text:\n");
    len = getline(s, MAXLINE);

    lower(s);
    printf("lower case:\t%s", s);
}

void lower(char s[])
{
    int i;
    for (i = 0; s[i] != '\0'; ++i)
    {
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] - ('A'-'a') : s[i];
    }
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
