/* i'm not quite sure what "plausible" number of bytes malloc should be checking,
    same for free.  So nothing in here is different for exercise 8-7, and 
    a google search doesn't turn up any solutions for this as an example either */

typedef unsigned long Align;    /* for alignment to unsigned long boundary,
                                    which seems to be the most-restrictive type for this macbook */

union header {      /* block header: */
    struct {
        union header *ptr;  /* next block if on free list */
        unsigned size;      /* size of this block */
    } s;
    Align x;        /* force alignment of blocks */
};

typedef union header Header;

static Header base;     /* empty list to get started */
#ifndef NULL
#define NULL 0
#endif
static Header *freep = NULL;    /* start of free list */

static Header *morecore(unsigned);

/* mymalloc:  general-purpose storage allocator */
void *mymalloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;
    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {  /* big enough */
            if (p->s.size == nunits) {  /* exactly */
                prevp->s.ptr = p->s.ptr;
            } else {                    /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) {   /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL) {
                return NULL;    /* none left */
            }
        }
    }
}

/* mycalloc:  allocate 'n' objects of size 'size' */
void *mycalloc(unsigned int n, unsigned int size)
{
    char *p;
    int i;

    if ((p = (char *) mymalloc(n*size)) == NULL) {
        return NULL;
    }
    for (i=0; i<n*size; i++) {
        *(p+i) = 0;
    }
    return (void *) p;
}

#define NALLOC  1024        /* minimum #units to request */

/* morecore:  ask system for more memory */
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;
    void myfree(void *);

    if (nu < NALLOC) {
        nu = NALLOC;
    }
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) {    /* no space at all */
        return NULL;
    }
    up = (Header *) cp;
    up->s.size = nu;
    myfree((void *)(up+1));
    return freep;
}

/* myfree:  put block ap in free list */
void myfree(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;  /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
            break;  /* freed block at start or end of arena */
        }
    }

    if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }
    if (p + p->s.size == bp) {      /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }
    freep = p;
}
