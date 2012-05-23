#include <stdio.h>
#include <stdlib.h>

#define ARRAYSIZE 1000000

main()
{
    int i, idx, v[ARRAYSIZE];

    for (i = 0; i < ARRAYSIZE; ++i)
    {
        v[i] = i;
    }

    //for (i = 0; i < 3; ++i)
    for (i = 0; i < ARRAYSIZE; ++i)
    {
        //idx = binsearch_from_book(i, v, ARRAYSIZE);
        idx = binsearch_mine(i, v, ARRAYSIZE);
        if (i != idx)
        {
            printf("binsearch returned index %d for item %d\n", idx, i);
        }
    }
}

/* binsearch: find x in v[0] <= v[1] <= ... <=v[n-1] */
int binsearch_from_book(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else /* found match */
            return mid;
    }
    return -1; /* no match */
}


int binsearch_mine(int x, int v[], int n)
{
    int low, high, mid;

    low = mid = 0;
    high = n - 1;
    while (low <= high && x != v[mid])
    {
        mid = (low+high) / 2;
        //printf("\tlow=%d mid=%d high=%d\n", low, mid, high);
        if (x < v[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    //printf("low=%d mid=%d high=%d\n", low, mid, high);
    if (x == v[mid])
    {
        return mid;
    }
    return -1; /* no match */
}
