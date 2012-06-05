#include <stdio.h>

void mystrncpy(char *s, char *t, int n);
void mystrncat(char *s, char *t, int n);
int mystrncmp(char *s, char *t, int n);

main()
{
    char s[] = "huzzah", t[] = "ahoy hoy";
    int n = 3;

    printf("working with:\n\ts='%s'\n\tt='%s'\n\tn=%d\n", s, t, n);

    mystrncmp(s, t, n);
    printf("first %d letters of '%s' and '%s' are same? %s\n", n, s, t, (mystrncmp(s, t, n) ? "yep" : "nope"));

    mystrncpy(s, t, n);
    printf("s after mystrncpy: %s\n", s);

    mystrncat(s, t, n);
    printf("s after mystrncat: %s\n", s);

    mystrncmp(s, t, n);
    printf("first %d letters of '%s' and '%s' are same? %s\n", n, s, t, (mystrncmp(s, t, n) ? "yep" : "nope"));
}

void mystrncpy(char *s, char *t, int n)
{
    while ((*s++ = *t++) && --n > 0)
    {
        ;
    }
}

void mystrncat(char *s, char *t, int n)
{
    while (*s)
    {
        s++;
    }
    while ((*s++ = *t++) && --n > 0)
    {
        ;
    }
}

int mystrncmp(char *s, char *t, int n)
{
    for (; (*s == *t) && n > 1; s++, t++, n--)
    {
        ;
    }
    return *s == *t;
}
