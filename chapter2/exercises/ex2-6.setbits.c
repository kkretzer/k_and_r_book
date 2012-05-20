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
    unsigned x, y;
    int p, n;

    x = 0777, y = 02;
    p = 3, n = 4;

    printf("\tp=%d n=%d\n", p, n);
    printf("\ty in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(y));
    printf("PRE\tx in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(x));
    x = setbits(x, p, n, y);
    printf("POST\tx in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(x));
}


/* return x with the n bits that begin at position p (position 0 is on the right)
    set to the rightmost n bits of y */
int setbits(unsigned x, int p, int n, unsigned y)
{
    return (x & ~(~(~0 << n) << p)) | ((y & ~(~0 << n)) << p);
}

