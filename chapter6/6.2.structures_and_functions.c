#include <stdio.h>
#include <string.h>

#define XMAX 1000
#define YMAX 1000
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};

/* makepoint:  make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

/* addpoint:  add two points */
struct point addpoint(struct point p1, struct point p2)
{
    /* p130 in K&R - "structure parameters are passed by value like any others" */
    p1.x += p2.x;
    p1.y += p2.y;
    /* the calling scope of addpoint still has its original p1 */
    return p1;
}

/* ptinrect:  return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
    return p.x >= r.pt1.x && p.x < r.pt2.x
        && p.y >= r.pt1.y && p.y < r.pt2.y;
}

/* canonrect:  canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r)
{
    struct rect temp;

    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}
    
main()
{
    struct rect screen;
    struct point middle;
    struct point makepoint(int, int);
    struct point addpoint(struct point, struct point);
    int ptinrect(struct point, struct rect);
    struct rect canonrect(struct rect);
    
    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    middle = makepoint((screen.pt1.x + screen.pt2.x)/2,
                       (screen.pt1.y + screen.pt2.y)/2);
    
    struct point origin, *pp;
    
    pp = &origin;
    /* printf("origin is (%d,%d)\n", (*pp).x, (*pp).y); */
    /* use the pp->x shorthand notation rather than (*pp).x */
    printf("origin is (%d,%d)\n", pp->x, pp->y);
    
    struct rect r, *rp = &r;
    /* all the following are equivalent */
    r.pt1.x;
    rp->pt1.x;
    (r.pt1).x;
    (rp->pt1).x;

    struct {
        int len;
        char *str;
    } q, *p;
    p = &q;
    char b[] = {'h', 'u', 'z', 'z', 'a', 'h', '\0'};
    q.len = strlen(b);
    q.str = b;
    printf("%s, %d\n", p->str, p->len);

    /* K&R p132 - ". and ->, together with () for function calls and [] for subscripts,
                   are at the top of the precedence hierarchy and thus bind bery tightly" */
    /* ie, this increments len, not p */
    ++p->len;
    printf("p->len now %d\n", p->len);
    /* which is same as */
    ++(p->len);
    printf("p->len now %d\n", p->len);

    /* this would increment p before accessing len */
    // (++p)->len;

    printf("*p->str fetches whatever str points to: %c\n", *p->str);

    printf("*p->str++ increments str after accessing whatever it points to: %c\n", *p->str++);
    printf("\t...so now *p->str yields: %c\n", *p->str);

    (*p->str)++;
    printf("(*p->str)++ increments whatever str points to: %c\n", *p->str);

    /* this would increment p after accessing whatever str points to */
    //(*p->str)++;
}
