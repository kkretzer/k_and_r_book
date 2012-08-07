#include <stdio.h>
#include <stdlib.h>

#define MAXPAGE 80
#define MAXLINE 1000

/* print set of files, with title, page breaks and page count */
main(int argc, char **argv)
{
    FILE *inputfile;
    char *inputfilename, line[MAXLINE];
    int pagelinecount, pagecount;

    while (--argc > 0) {
        inputfilename = *++argv;
        inputfile = fopen(inputfilename, "r");
        if (inputfile == NULL) {
            printf("Error opening %s\n", inputfilename);
            exit(1);
        }
        printf("\n\n#####\n##### %s\n#####\n", inputfilename);
        pagelinecount = 0;
        pagecount = 1;
        while (fgets(line, MAXLINE, inputfile) != NULL) {
            if (pagelinecount++ == 0) {
                printf("\n-------- PAGE %d --------\n", pagecount++);
            }
            printf("%s", line);
            if (pagelinecount >= MAXPAGE) {
                pagelinecount = 0;
            }
        }
        if (ferror(inputfile)) {
            printf("Error reading from file %s\n", inputfilename);
            exit(1);
        }
        fclose(inputfile);
    }
    exit(0);
}
