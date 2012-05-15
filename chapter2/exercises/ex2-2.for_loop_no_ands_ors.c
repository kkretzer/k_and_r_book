#include <stdio.h>

main()
{
    int lim = 10, i;
    char c, s[10];

    for (i=0; (i<lim-1) + ((c=getchar()) != '\n') + (c != EOF) == 3; ++i)
        s[i] = c;

    printf("%s\n", s);
}
