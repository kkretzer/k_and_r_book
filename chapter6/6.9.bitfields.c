#include <stdio.h>

main()
{
    typedef struct {
        unsigned int first : 1;
        unsigned int second : 1;
        unsigned int third : 1;
        unsigned int  : 1;          /* unnamed, skip this bit */
        unsigned int fifth : 1;
        unsigned int sixth : 1;
        unsigned int seventh : 1;
        unsigned int eighth : 1;
    } bitflags;
    unsigned int data = 85; /* 0x01010101 */
    unsigned int *pdata = &data;
    bitflags *bits = (bitflags *) pdata;

    printf("first=%d\n", bits->first);
    printf("second=%d\n", bits->second);
    printf("third=%d\n", bits->third);
    printf("fifth=%d\n", bits->fifth);
    printf("sixth=%d\n", bits->sixth);
    printf("seventh=%d\n", bits->seventh);
    printf("eighth=%d\n", bits->eighth);
}
