#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itoa(int n, char s[], int w);
void reverse(char s[]);

main()
{
    int n, w;
    char s[MAXLINE];
    n = -13;
    w = 5;
    itoa(n, s, w);
    printf("\n%d converted to string with padded itoa:\n%s\n\n", n, s);
}

/* convert n to characters in s with minimum w width */
void itoa(int n, char s[], int w)
{
    int i, sign;

    sign = (n < 0) ? -1 : 1;
    i = 0;
    do {
        s[i++] = (n % 10 * sign) + '0';
    } while ((n /= 10) != 0);
    if (sign == -1)
        s[i++] = '-';
    while ( i < w )
    {
        s[i++] = ' ';
    }
    s[i] = '\0';
    reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = strlen(s)-1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
