#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000    /* maximum input line size */

int any(char s1[], char s2[]);

main()
{
    int len, idx;
    char s1[MAXLINE], s2[MAXLINE];

    printf("%s:\n", "Enter string to search:");
    len = getline(s1, MAXLINE);
    printf("%s:\n", "Enter characters find:");
    len = getline(s2, MAXLINE);
    idx = any(s1, s2);

    if (idx >= 0)
    {
        printf("first character found at index %d\n", idx);
    } else {
        puts("none found\n");
    }
}

/* find first index in s1 containing any of the characters in s2 */
int any(char s1[], char s2[])
{
    int idx, i, j;
    idx = -1;

    for (i = 0; s1[i] != '\0' && s1[i] != '\n' && idx == -1; i++)
    {
        j = 0;
        while (s2[j] != '\0' && s2[j] != '\n')
        {
            if (s1[i] == s2[j])
            {
                idx = i;
                break;
            }
            ++j;
        }
    }
    return idx;
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
