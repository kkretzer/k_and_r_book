#include <stdio.h>
#include <stdlib.h>

#define MAXLINE     1000  /* maximum input line size */
#define TABSTOPS    4     /* number of blanks per tab */

int getline(char line[], int maxline);
void replace_tabs(char line[], char replaced_tabs[], int length, int tabstops);

/* replace tabs with blanks */
main(int argc, char *argv[])
{
    int len, tabstops = TABSTOPS;
    char line[MAXLINE], replaced_tabs[MAXLINE];

    if (argc == 2) {
        tabstops = atoi(argv[1]);
    }

    while ((len = getline(line, MAXLINE)) > 0)
    {
        replace_tabs(line, replaced_tabs, len, tabstops);
        printf("%s\n", replaced_tabs);
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

/* build new line of text replacing all tabs with blanks */
void replace_tabs(char line[], char replaced_tabs[], int len, int tabstops)
{
    int i, j, t;
    j = 0;

    for (i = 0; i < len - 1; ++i)
    {
        if (line[i] == '\t')
        {
            for (t = 0; t < tabstops; ++t)
            {
                replaced_tabs[j] = ' ';
                ++j;
            }
        } else {
            replaced_tabs[j] = line[i];
            ++j;
        }
    }
    replaced_tabs[j] = '\0';
}
