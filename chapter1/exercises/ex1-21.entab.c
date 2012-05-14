#include <stdio.h>

#define MAXLINE     1000  /* maximum input line size */
#define TABSTOPS    4     /* number of blanks per tab */

int getline(char line[], int maxline);
void replace_blanks(char line[], char replaced_blanks[], int length);

/* replace blanks with tabs */
main()
{
    int len;
    char line[MAXLINE], replaced_blanks[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0)
    {
        replace_blanks(line, replaced_blanks, len);
        printf("%s\n", replaced_blanks);
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

/* build new line of text replacing all blanks with tabs */
void replace_blanks(char line[], char replaced_blanks[], int len)
{
    int i, j, k, t, blank_count;
    j = blank_count = 0;

    for (i = 0; i < len - 1; ++i)
    {
        if (line[i] == ' ')
        {
            ++blank_count;
            if (blank_count == TABSTOPS)
            {
                blank_count = 0;
                replaced_blanks[j] = '\t';
                ++j;
            }
        } else {
            for (k = 0; k < blank_count; ++k)
            {
                replaced_blanks[j] = ' ';
                ++j;
            }
            blank_count = 0;
            replaced_blanks[j] = line[i];
            ++j;
        }
    }
    replaced_blanks[j] = '\0';
}
