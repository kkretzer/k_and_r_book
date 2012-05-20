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

main()
{
    unsigned x;
    int p, n;

    x = 0127;
    p = 2, n = 4;

    printf("\tp=%d n=%d\n", p, n);
    printf("PRE\tx in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(x));
    x = invert(x, p, n);
    printf("POST\tx in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(x));
}


/* invert the n bits of x beginning at position p,
    where 0 is the rightmost position, leaving the other bits unchanged */
int invert(unsigned x, int p, int n)
{
    unsigned mask = ~(~0 << n) << p;
    return (x & ~mask) | (~x & mask);
}

