#include <stdio.h>

#define MAXLINE 1000

int getline(char s[], int lim);
void expand(char s1[], char s2[]);

main()
{
    int len;
    char s1[MAXLINE], s2[MAXLINE];
    puts("Enter some shorthand text (a-z, F-M, 3-8):\n");
    len = getline(s1, MAXLINE);
    expand(s1, s2);
    printf("After expansion:\n%s\n", s2);
}

void expand(char s1[], char s2[])
{
    int i, j, c, expanding;
    expanding = 0;
    
    for (i = j = 0; s1[i] != '\0' && s1[i] != '\n'; i++)
    {
        if (expanding)
        {
            expanding = 0;
            for (c = s1[i-2] + 1; c <= s1[i]; c++)
            {
                s2[j++] = c;
            }
        }
        else
        {
            if (s1[i] == '-' && i > 0)
            {
                expanding = 1;
            }
            else
            {
                s2[j++] = s1[i];
            }
        }
    }
    if (expanding)
    {
        puts("still expanding");
        s2[j++] = '-';
    }
    s2[j] = '\0';
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
