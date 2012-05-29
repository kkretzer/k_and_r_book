#include <stdio.h>

#define swap(t,x,y) {t z = x; x = y; y = z;}

main()
{
    int x = 0, y = 1;
    printf("x=%d, y=%d\n", x, y);
    swap(int,x,y);
    printf("x=%d, y=%d\n", x, y);

    double xx = 0.7, yy = 1.2;
    printf("xx=%g, yy=%g\n", xx, yy);
    swap(double,xx,yy);
    printf("xx=%g, yy=%g\n", xx, yy);
}
