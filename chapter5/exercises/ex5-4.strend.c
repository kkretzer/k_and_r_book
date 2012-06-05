#include <stdio.h>

int strend(char *s, char *t);

main()
{
    char s[] = "huzzah", t[] = "zah";
    printf("is '%s' at the end of '%s'?\n%s\n", t, s, (strend(s, t) ? "yep" : "nope"));

    char ss[] = "huzzah", tt[] = "doh";
    printf("is '%s' at the end of '%s'?\n%s\n", tt, ss, (strend(ss, tt) ? "yep" : "nope"));
}

/* return 1 if string t occurs at the end of string s, zero otherwise */
int strend(char *s, char *t)
{
    char *sbeg = s, *tbeg = t;
    while (*s)
    {
        s++;
    }
    while (*t)
    {
        t++;
    }

    for (; s > sbeg && t > tbeg && *s == *t; s--, t--)
    {
        ;
    }
    return *s == *t;
}
