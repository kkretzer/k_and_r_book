#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 1000

int getline(char *, int);
void findpattern(char *, long, char *, char *);
void usage(void);

int except = 0, number = 0, printfilename = 0;

/* find: print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
    char line[MAXLINE], *pattern, **input_files = NULL, *filename;
    long lineno = 0;
    int c, i;
    FILE *input;

    while (--argc > 0 && (*++argv)[0] == '-')
    {
        while (c = *++argv[0])
        {
            switch (c)
            {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                case 'f':
                    printfilename = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    usage();
                    exit(1);
                    break;
            }
        }
    }
    if (argc == 0) {
        usage();
        exit(1);
    }
    pattern = *argv;
    if (--argc > 0) {
        input_files = ++argv;
    }
    if (input_files == NULL) {
        while (getline(line, MAXLINE) > 0)
        {
            findpattern(line, ++lineno, pattern, NULL);
        }
    } else {
        while (argc-- > 0) {
            filename = *input_files++;
            input = fopen(filename, "r");
            lineno = 0;
            while (fgets(line, MAXLINE, input) != NULL) {
                findpattern(line, ++lineno, pattern, filename);
            }
            if (ferror(input)) {
                printf("Error reading from %s\n", filename);
                exit(1);
            }
            fclose(input);
        }
    }
    exit(0);
}

void findpattern(char *line, long lineno, char *pattern, char *filename)
{
    if ((strstr(line, pattern) != NULL) != except)
    {
        if (filename != NULL && printfilename) {
            printf("%s:", filename);
        }
        if (number)
        {
            printf("%ld:", lineno);
        }
        printf("%s", line);
    }
}

void usage(void)
{
    printf("Usage: find -x -n -f pattern [input files]\n");
}

/* getline: read a line into s, return length */
int getline(char *s, int lim)
{
    int c;
    char *sbeg = s;

    while (--lim > 0 && (c=getchar()) !=EOF && c != '\n')
    {
        *s++ = c;
    }

    if (c == '\n')
    {
        *s++ = c;
    }
    *s = '\0';
    return s - sbeg;
}
