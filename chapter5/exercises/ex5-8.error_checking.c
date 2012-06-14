#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

main()
{
    int *m, *d, mm=0, dd=0;
    m = &mm;
    d = &dd;

    printf("day of year for %d/%0d/%0d : %d\n", 2012, 1, 1, day_of_year(2012, 1, 1));
    printf("day of year for %d/%0d/%0d : %d\n", 2012, 2, 29, day_of_year(2012, 2, 29));
    printf("day of year for %d/%0d/%0d : %d\n", 2012, 6, 12, day_of_year(2012, 6, 12));
    printf("day of year for %d/%0d/%0d : %d\n", 2012, 12, 31, day_of_year(2012, 12, 31));
    printf("day of year for %d/%0d/%0d : %d\n", 2012, 2, 31, day_of_year(2012, 2, 31));

    month_day(2011, 1, m, d);
    printf("month day for day %d of %d : %d/%d\n", 1, 2011, *m, *d);
    month_day(2011, 31, m, d);                  
    printf("month day for day %d of %d : %d/%d\n", 31, 2011, *m, *d);
    month_day(2011, 59, m, d);                  
    printf("month day for day %d of %d : %d/%d\n", 59, 2011, *m, *d);
    month_day(2011, 365, m, d);                 
    printf("month day for day %d of %d : %d/%d\n", 365, 2011, *m, *d);
    month_day(2011, 465, m, d);                 
    printf("month day for day %d of %d : %d/%d\n", 365, 2011, *m, *d);
}


static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (day > daytab[leap][month])
    {
        return -1;
    }

    for (i = 1; i < month; i++)
    {
        day += daytab[leap][i];
    }
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday > (leap ? 366 : 365))
    {
        *pmonth = *pday = -1;
        return;
    }

    for (i = 1; yearday > daytab[leap][i]; i++)
    {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}
