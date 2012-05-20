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

int rightrot(unsigned x, int n);

/* i was lazy and this only allows for 8 bit rotation */
main()
{
    unsigned x;
    int n;

    x = 0127;
    n = 3;

    printf("\tn=%d\n", n);
    printf("PRE\tx in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(x));
    x = rightrot(x, n);
    printf("POST\tx in bits = "BYTETOBINARYPATTERN"\n", BYTETOBINARY(x));
}


/* rotate x to the right by n bits */
int rightrot(unsigned x, int n)
{
    return (x << (8-n)) | (x >> n);
}

