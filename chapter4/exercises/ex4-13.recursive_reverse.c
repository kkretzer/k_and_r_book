#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

void reverse(char s[]);
void reverse_recur(char s[], int left, int right);

main()
{
    int n;
    char s[MAXLINE] = "hello world";
    printf("reversing %s:\n", s);
    reverse(s);
    printf("%s\n", s);

    char s2[MAXLINE] = "foobar";
    printf("reversing %s:\n", s2);
    reverse(s2);
    printf("%s\n", s2);

}

/* reverse: reverse string s in place */
void reverse(char s[])
{
    reverse_recur(s, 0, strlen(s)-1);
}

void reverse_recur(char s[], int left, int right)
{

    int c;
    if (left < right)
    {
        c = s[left];
        s[left] = s[right];
        s[right] = c;
        reverse_recur(s, left+1, right-1);
    }
}

