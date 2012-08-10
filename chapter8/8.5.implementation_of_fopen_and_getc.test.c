//#include "8.5.implementation_of_fopen_and_getc.h"
#include "exercises/ex8-2.bitfields_insteadof_bitops.h"

int main()
{
    int j;
    for (j = 10000; j > 0; j--) {
        char huzzah[8] = "huzzah\n";
        int i;
        for (i=0; i < 8; i++) {
            putchar(huzzah[i]);
        }
        char doh[4] = "doh\n";
        for (i=0; i < 4; i++) {
            putc(doh[i], stderr);
        }
    }
}
