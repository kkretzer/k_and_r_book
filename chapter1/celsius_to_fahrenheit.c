#include <stdio.h>

/* print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300 */
main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    // print a heading
    printf("  Cels Fahr\n");
    printf("-----------\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = 32.0 + (9.0/5.0) * celsius;
        printf("%6.1f %3.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

