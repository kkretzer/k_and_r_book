#include <stdio.h>

void mystrcat(char *s, char *t);

main()
{
    char s[] = "huzzah", t[] = "doh";

    printf("concatenating '%s' and '%s':\n", s, t);
    mystrcat(s, t);
    printf("%s\n", s);
}

void mystrcat(char *s, char *t)
{
    while (*s)
    {
        s++;
    }
    while (*s++ = *t++)
    {
        ;
    }
}
