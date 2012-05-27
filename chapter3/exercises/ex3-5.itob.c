#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itob(int n, char s[], int b);
void reverse(char s[]);

main()
{
    int n, b;
    char s[MAXLINE];
    b = 7;
    n = 13;
    itob(n, s, b);
    printf("\n%d converted to string with itob (base=%d): %s\n\n", n, b, s);
}

/* convert n to characters s in base b */
void itob(int n, char s[], int b)
{
    int i, sign;
    char c;

    sign = (n < 0) ? -1 : 1;
    i = 0;
    do {
        c = (n % b * sign) + '0';
        if (c > '9')
        {
            c = (c - '9') + 'A' - 1;
        }
        s[i++] = c;
    } while ((n /= b) != 0);
    if (sign == -1)
        s[i++] = '-';
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
