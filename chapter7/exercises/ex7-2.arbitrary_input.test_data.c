#include <stdio.h>

int main()
{
    char c;
    printf("tab is %d\n", '\t');
    printf("nongraphic characters:\n");
    for (c = 0; c < ' '; c++) {
        printf("%c\n", c);
    }
}
