#include <stdio.h>

int isupper_savespace(char);
#define isupper_savetime(c) ((c >= 'A') && (c <= 'Z'))

main()
{
    printf("A isupper? %d\n", isupper_savespace('A'));
    printf("z isupper? %d\n", isupper_savespace('z'));
    printf("K isupper? %d\n", isupper_savetime('K'));
    printf("h isupper? %d\n", isupper_savetime('h'));
}

int isupper_savespace(char c)
{
    return (c >= 'A') && (c <= 'Z');
}

