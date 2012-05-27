/*
    Explain why K&R's itoa function on page 64 does not handle 
    the largest negative number in a 2's complement number representation -(2^(wordsize-1))

    -> In 2's complement, the absolute value of the maximum positive number is 1 less than
    the absolute value of the maximum negative number.  The original implementation of itoa
    flips the sign of the number being converted to characters if it's negative, so in the case
    of the max negative number, when it's flipped to positive it's value will be higher than
    the max positive number possible by that data type, and there will be an overflow.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void itoa(int n, char s[]);
void reverse(char s[]);

main()
{
    int n;
    char s[MAXLINE];
    /* maximum negative on my laptop */
    n = -2147483648;
    //n = 2147483647;
    itoa(n, s);
    printf("\n%d converted to string with itoa: %s\n\n", n, s);
}

/* convert n to characters in s, handle maximum negative value for ints */
void itoa(int n, char s[])
{
    int i, sign, negative;

    sign = (n < 0) ? -1 : 1;
    i = 0;
    do {
        s[i++] = (n % 10 * sign) + '0';
    } while ((n /= 10) != 0);
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
