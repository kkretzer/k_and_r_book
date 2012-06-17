#include <stdio.h>
#include <string.h>
#define MAXOP   100

main(int argc, char *argv[])
{
    int i, j, operands[MAXOP], *currop;
    currop = operands;

    for (i = 1; i < argc; i++) {
        switch (argv[i][0]) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                *currop = 0;
                for (j = 0; j < strlen(argv[i]); j++)
                {
                    *currop = *currop * 10 + (argv[i][j] - '0');
                }
                ++currop;
                break;
            case '+':
                *(currop-2) = *(currop-2) + *(currop-1);
                currop = currop - 1;
                break;
            case '-':
                *(currop-2) = *(currop-2) - *(currop-1);
                currop = currop - 1;
                break;
            case '*':
                *(currop-2) = *(currop-2) * *(currop-1);
                currop = currop - 1;
                break;
            case '/':
                *(currop-2) = *(currop-2) / *(currop-1);
                currop = currop - 1;
                break;
            default:
                printf("invalid operator %s\n", argv[i]);
                break;
        }
    }
    printf("\n%d\n", *--currop);
}

