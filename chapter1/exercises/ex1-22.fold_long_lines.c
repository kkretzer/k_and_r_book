#include <stdio.h>

#define MAXLINE     1000  /* maximum input line size */
#define LINELIMIT   20    /* lines longer than this will be folded */

int getline(char line[], int maxline);
void fold(char line[], char folded[], int length);

/* blech */
/* fold long lines of text into multiple lines */
main()
{
    int len;
    char line[MAXLINE], folded[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0)
    {
        fold(line, folded, len);
        printf("%s", folded);
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
        printf("%s", "huzzah");
    }

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void fold(char line[], char folded[], int len)
{
    int last_nonblank, last_blank, i, j, k, line_count, processed, blank_found, boundary_idx;
    char folded_line[MAXLINE], boundary;
    blank_found = processed = j = line_count = 0;
    last_nonblank = last_blank = -1;

    while ((len - processed) > LINELIMIT)
    {
        boundary_idx = processed + LINELIMIT;
        boundary = line[boundary_idx];
        if (boundary == ' ' || boundary == '\t')
        {
            for (i = processed; i < boundary_idx; ++i)
            {
                folded_line[j] = line[i];
                ++j;
            }
            folded_line[j] = '\n';
            ++j;
            processed = boundary_idx;
        } else {
            // find last ' ' or '\t', and find last non ' ' or '\t' before it
            for (i = boundary_idx; i > processed; --i)
            {
                if (blank_found == 0 && (line[i] == ' ' || line[i] == '\t'))
                {
                    blank_found = 1;
                } else if (blank_found == 1 && line[i] != ' ' && line[i] != '\t')
                {
                    break;
                }
            }
            for (k = processed; k < i + 1; ++k)
            {
                folded_line[j] = line[k];
                ++j;
            }
            folded_line[j] = '\n';
            ++j;
            processed = i;
        }
    }
    for (i = processed; i < len; ++i)
    {
        folded[j] = line[i];
        ++j;
    }
}
