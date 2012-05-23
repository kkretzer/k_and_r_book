#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int getline(char s[], int lim);
void escape(char s[], char t[]);
void descape(char s[], char t[]);

/* convert escapable characters like \n and \t 
  to their escaped string representations */
main()
{
    char s[MAXLINE], t[MAXLINE], mode[MAXLINE];
    int modelen;

    puts("Which mode to run in?\n\t1 = escape\n\t2 = de-escape");
    modelen = getline(mode, MAXLINE);
    if (modelen != 2 || ((mode[0] != '1' && mode[0] != '2') || mode[1] != '\n'))
    {
        puts("not a valid choice");
        exit(1);
    }

    if (mode[0] == '1')
    {
        while (1)
        {
            s[0] = t[0] = '\0';
            puts("Enter some text, with some escapable characters:");
            getline(t, MAXLINE);
            escape(s, t);
            printf("\n... with characters escaped:\n%s\n\n", s);
        }
    } else {
        while (1)
        {
            s[0] = t[0] = '\0';
            puts("Enter some text with escape sequences to be printed:");
            getline(t, MAXLINE);
            descape(s, t);
            printf("\n... with escapes sequences printed:\n%s\n\n", s);
        }
    }
}

void escape(char s[], char t[])
{
    int i, j;
    for (i = j = 0; t[i] != '\0'; ++i)
    {
        switch (t[i])
        {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\\':
                s[j++] = '\\';
                s[j++] = '\\';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

void descape(char s[], char t[])
{
    int i, j, escaping;
    escaping = 0;
    for (i = j = 0; t[i] != '\0'; ++i)
    {
        if (escaping)
        {
            switch (t[i])
            {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                case '\\':
                    s[j++] = '\\';
                    break;
                default:
                    s[j++] = '?';
                    break;
            }
            escaping = 0;
        }
        else
        {
            if (t[i] == '\\')
            {
                escaping = 1;
            }
            else
            {
                s[j++] = t[i];
            }
        }
    }
    s[j] = '\0';
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
