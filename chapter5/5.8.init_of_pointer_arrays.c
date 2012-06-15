#include <stdio.h>

char *month_name(int n);

main()
{
    printf("month  0 = %s\n", month_name(0));
    printf("month  1 = %s\n", month_name(1));
    printf("month  2 = %s\n", month_name(2));
    printf("month  3 = %s\n", month_name(3));
    printf("month  4 = %s\n", month_name(4));
    printf("month  5 = %s\n", month_name(5));
    printf("month  6 = %s\n", month_name(6));
    printf("month  7 = %s\n", month_name(7));
    printf("month  8 = %s\n", month_name(8));
    printf("month  9 = %s\n", month_name(9));
    printf("month 10 = %s\n", month_name(10));
    printf("month 11 = %s\n", month_name(11));
    printf("month 12 = %s\n", month_name(12));
    printf("month 13 = %s\n", month_name(13));
}


/* month_name: return name of n-th month */
char *month_name(int n)
{
    static char *name [] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
    
    return (n < 1 || n > 12) ? name[0] : name[n];
}
