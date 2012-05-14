#include <stdio.h>

#define MAXLINE     1000  /* maximum input line size */

/* states of program text */
#define NORMAL      0
#define INSTRING    1
#define INCHAR      2
#define INCOM       3

int getline(char line[], int maxline);

main()
{
    int i, len, state;
    char line[MAXLINE];

    state = NORMAL;
    while ((len = getline(line, MAXLINE)) > 0)
    {
        for (i = 0; i < len; ++i)
        {
            if (state == INCOM)
            {
                if (line[i-1] == '*' && line[i] == '/')
                {
                    state = NORMAL;
                }
            }
            else if (state == INSTRING)
            {
                putchar(line[i]);
                if (line[i] == '"')
                {
                    state = NORMAL;
                }
            }
            else if (state == INCHAR)
            {
                putchar(line[i]);
                if (line[i] == '\'')
                {
                    state = NORMAL;
                }
            }
            else /* NORMAL */
            {
                if (i <= len-2 && line[i] == '/' && line[i+1] == '*')
                {
                    state = INCOM;
                }
                else
                {
                    putchar(line[i]);
                    if (line[i] == '"')
                    {
                        state = INSTRING;
                    }
                    else if (line[i] == '\'')
                    {
                        state = INCHAR;
                    }
                }
            }
        }
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
