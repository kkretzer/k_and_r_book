#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int trim(char s[]);
int getline(char s[], int lim);

main()
{
    char s[MAXLINE];
    puts("Enter some text with trailing whitespace:\n");
    getline(s, MAXLINE);
    trim(s);
    printf("Trimmed text (surrounded by quotes):\n\"%s\"\n", s);
}

/* trim: remove trailing blanks, tabs, newlines */
int trim(char s[])
{
    int n;

    for (n = strlen(s)-1; n >= 0; n--)
    {
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
        {
            break;
        }
    }
    s[n+1] = '\0';
    return n;
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
