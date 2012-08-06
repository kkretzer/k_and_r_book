#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFILENAME 500
#define MAXLINE 1000

/* simple file diffing */
main(int argc, char **argv)
{
    char *prog = argv[0];
    char line1[MAXLINE], line2[MAXLINE], *ifp1ret, *ifp2ret;
    char file1[MAXFILENAME], file2[MAXFILENAME];
    FILE *ifp1, *ifp2;
    int linecount = 0;

    if (argc == 1 || argc > 3) {
        fprintf(stderr, "%s: requires exactly 2 file names as args, or one file arg along with stdin\n", prog);
        exit(1);
    }

    if (argc == 2) {
        strcpy(file1, "<STDIN>");
        ifp1 = stdin;
        strcpy(file2, argv[1]);
        if ((ifp2 = fopen(file2, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, file2);
            exit(2);
        }
    } else {
        strcpy(file1, argv[1]);
        if ((ifp1 = fopen(file1, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, file1);
            exit(2);
        }
        strcpy(file2, argv[2]);
        if ((ifp2 = fopen(file2, "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", prog, file2);
            exit(2);
        }
    }

    ifp1ret = fgets(line1, MAXLINE, ifp1);
    ifp2ret = fgets(line2, MAXLINE, ifp2);
    for (linecount = 0; ifp1ret != NULL && ifp2ret != NULL; ifp1ret = fgets(line1, MAXLINE, ifp1), ifp2ret = fgets(line2, MAXLINE, ifp2)) {
        if (strcmp(line1, line2) != 0) {
            printf("files differ at line %d:\n------------ %s ------------\n%s------------\n\n++++++++++++ %s ++++++++++++\n%s++++++++++++\n\n", linecount, file1, line1, file2, line2);
            exit(3);
        }
        linecount++;
    }

    if (argc == 3) {
        fclose(ifp1);
    }
    fclose(ifp2);

    if (ifp1ret == NULL && ifp2ret != NULL) {
        printf("%s ends after %d, while %s continues\n", file1, linecount, file2);
        exit(4);
    } else if (ifp1ret != NULL && ifp2ret == NULL) {
        printf("%s ends after %d, while %s continues\n", file2, linecount, file1);
        exit(4);
    }

    exit(0);
}
