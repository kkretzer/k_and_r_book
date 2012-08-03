#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int upcase;
    char c;
    char *basename = strrchr(argv[0], '/');
    basename++; /* move past the last '/' */
    if (strcmp(basename, "upcase") == 0) {
        upcase = 1;
    } else if (strcmp(basename, "locase") == 0) {
        upcase = 0;
    } else {
        printf("i should be named either 'upcase' or 'locase', '%s' is not valid\n", basename);
        exit(1);
    }

    if (upcase) {
        while ((c = getchar()) != EOF) {
            putchar(toupper(c));
        }
    } else {
        while ((c = getchar()) != EOF) {
            putchar(tolower(c));
        }
    }
}
