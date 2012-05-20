#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000    /* maximum input line size */

void squeeze(char s1[], char s2[]);

main()
{
    int len;
    char s1[MAXLINE], s2[MAXLINE];

    printf("%s:\n", "Enter string to squeeze:");
    len = getline(s1, MAXLINE);
    printf("%s:\n", "Enter squeeze characters:");
    len = getline(s2, MAXLINE);
    squeeze(s1, s2);

    printf("after squeezing:\n%s\n", s1);
}

/* squeeze: delete all chars in s2 from s1 */
void squeeze(char s1[], char s2[])
{
    int i, j, k, is_squeeze;

    for (i = j = 0; s1[i] != '\0'; i++)
    {
        k = 0;
        is_squeeze = 0;
        while (s2[k] != '\0')
        {
            if (is_squeeze = (s1[i] == s2[k++]))
            {
                break;
            }
        }
        if (!is_squeeze)
        {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
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
