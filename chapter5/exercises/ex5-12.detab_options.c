#include <stdio.h>
#include <stdlib.h>

#define MAXLINE     1000  /* maximum input line size */
#define TABSTOPS    4     /* number of blanks per tab */

int getline(char line[], int maxline);
void replace_tabs(char line[], char replaced_tabs[], int len, int tabstops, int first_tabstop);

/* replace tabs with blanks */
main(int argc, char *argv[])
{
    int len, tabstops = TABSTOPS, first_tabstop = 0;
    char line[MAXLINE], replaced_tabs[MAXLINE];

    while (--argc > 0)
    {
        switch ((*++argv)[0])
        {
            case '-':
                first_tabstop = -1 * atoi(*argv);
                break;
            case '+':
                tabstops = atoi(*argv);
                break;
            default:
                printf("invalid options\n");
                exit(1);
                break;
        }
    }


    while ((len = getline(line, MAXLINE)) > 0)
    {
        replace_tabs(line, replaced_tabs, len, tabstops, first_tabstop);
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
void replace_tabs(char line[], char replaced_tabs[], int len, int tabstops, int first_tabstop)
{
    int i, j, t;
    j = 0;

    for (i = 0; i < len - 1; ++i)
    {
        if (line[i] == '\t')
        {
            if (first_tabstop > 0)
            {
                for (t = 0; t < first_tabstop; ++t)
                {
                    replaced_tabs[j] = ' ';
                    ++j;
                }
                first_tabstop = 0;
            } else {
                for (t = 0; t < tabstops; ++t)
                {
                    replaced_tabs[j] = ' ';
                    ++j;
                }
            }
        } else {
            replaced_tabs[j] = line[i];
            ++j;
        }
    }
    replaced_tabs[j] = '\0';
}
