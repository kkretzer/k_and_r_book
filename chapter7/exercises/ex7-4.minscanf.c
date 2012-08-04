#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void minscanf(char *, ...);

main()
{
    int huzzah;
    float ahoy;
    char doh[1000];
    printf("enter text in this form:\nhuzzah %%d ahoy hoy %%f doh %%s\n\n");
    minscanf("huzzah %d ahoy hoy %f doh %s", &huzzah, &ahoy, doh);
    printf("\nhuzzah:\t%d\nahoy hoy:\t%f\ndoh:\t%s\n", huzzah, ahoy, doh);
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval, c;
    int *ival;
    double *dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (isspace(*p)) {
            continue;
        }
        if (*p != '%') {
            for (c = getchar(); isspace(c); c = getchar()) {};
            if (*p != c) {
                printf("error - input doesn't match expected format\n");
                return;
            }
            continue;
        } else {
            switch (*++p) {
            case 'd':
                scanf("%d", va_arg(ap, int *));
                break;
            case 'f':
                scanf("%f", va_arg(ap, double *));
                break;
            case 's':
                scanf("%s", va_arg(ap, char *));
                break;
            }
        }
    }           
    va_end(ap);
}
