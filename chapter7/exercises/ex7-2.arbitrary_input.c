#include <stdio.h>

#define MAXLINE 100

int main()
{
    char c;
    int linelen = 0;
    while ((c = getchar()) != EOF) {
        if (c >= ' ' || c == '\t' || c == '\n') {
            linelen = c == '\n' ? 0 : linelen+1;
            if (linelen > MAXLINE) {
                putchar('\n');
                linelen = 0;
            }
            putchar(c);
        } else {
            printf("\\0x%X", c);
        }
    }
    putchar('\n');
}
