#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1000

void itoa(int n, char s[]);
void itoa_recur(int n, char s[], int i, int sign);
void reverse(char s[]);

main()
{
    int n;
    char s[MAXLINE];
    n = 17;
    itoa(n, s);
    printf("\n%d converted to string with itoa: %s\n\n", n, s);
    n = INT_MIN;
    itoa(n, s);
    printf("\n%d converted to string with itoa: %s\n\n", n, s);
}

void itoa(int n, char s[])
{
    int sign = (n < 0) ? -1 : 1;
    itoa_recur(n, s, 0, sign);
}

/* recursively convert n to characters in s */
void itoa_recur(int n, char s[], int i, int sign)
{
    s[i++] = (sign * (n % 10)) + '0';
    if (n / 10)
    {
        itoa_recur(n / 10, s, i, sign);
    }
    else 
    {
        if (sign == -1)
        {
            s[i++] = '-';
        }
        s[i] = '\0';
        reverse(s);
    }
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

