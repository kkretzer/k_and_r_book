#include <stdio.h>
#define MAXLINE 1000

int getline(char s[], int lim);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

/* find all lines matching pattern
   using strrindex for finding 
   right-most match in the line
 */
main()
{
    char line[MAXLINE];
    int found = 0, rindex;

    while (getline(line, MAXLINE) > 0)
    {
        rindex = strrindex(line, pattern);
        if (rindex >= 0) {
            printf("Found at index %d\n", rindex);
            found++;
        }
    }
    return found;
}

/* strrindex: return right-most index of t in s, -1 if none */
int strrindex(char s[], char t[])
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++)
    {
        ;
    }

    for (; i >= 0; i--)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
        {
            ;
        }
        if (k > 0 && t[k] == '\0')
        {
            return i;
        }
    }

    return -1;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c=getchar()) !=EOF && c != '\n')
    {
        s[i++] = c;
    }

    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}
