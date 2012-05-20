/* 1st part of ex 2-9
    x &= (x-1) deletes the rightmost 1-bit in x
    because (x-1) will absolutely flip the rightmost 1-bit to zero
        (ex: 1001 - 1 = 1000
             1010 - 1 = 1001
             1100 - 1 = 1011
        )
    and 'and-ing' with the '&=' operator is equivalent to
        x = x & (x-1)
    so the rightmost 1-bit will always be and-ed with a zero

==> the rightmost 1-bit will be deleted

 */

#include <stdio.h>

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0) 

int bitcount(unsigned x);

main()
{
    unsigned x;
    x = 0757;

    printf("x in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(x));
    printf("%d 1-bits in x\n", bitcount(x));
}

/* using the first part of this exercise to make a faster bitcount */
int bitcount(unsigned x)
{
    if (x == 0)
        return 0;

    int b;
    b = 1;
    
    while (x &= (x-1))
        ++b;
    return b;
}

