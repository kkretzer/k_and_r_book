#define NULL        0
#define EOF         (-1)
#define BUFSIZ      1024
#define OPEN_MAX    20  /* max # files open at once */

typedef struct _iobuf {
    int  cnt;           /* characters left */
    char *ptr;          /* next character position */
    char *base;         /* location of buffer */
    int  flag;          /* mode of file access */
    int  fd;            /* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

enum _flags {
    _READ   = 01,   /* file open for reading */
    _WRITE  = 02,   /* file  open for writing */
    _UNBUF  = 04,   /* file is unbuffered */
    _EOF    = 010,  /* EOF has occurred on this file */
    _ERR    = 020   /* error occurred on this file */
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferror(p)   (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)   (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar()   getc(stdin)
#define putchar(x)  putc((x), stdout)


#include <fcntl.h>
#include <stdlib.h>
#define PERMS 0666      /* RW for owner, group, others */

/* fopen:  open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
        if ((fp->flag & (_READ | _WRITE)) == 0) {
            break;      /* found free slot */
        }
    }
    if (fp >= _iob + OPEN_MAX) {    /* no free slots */
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1) {     /* couldn't access name */
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}

int fclose(FILE *fp)
{
    if (fflush(fp) == EOF) {
        return EOF;
    }
    free(fp->base);
    if (close(fp->fd) != 0) {
        return EOF;
    }
    fp->ptr = fp->base = NULL;
    fp->flag = fp->cnt = 0;
    fp->fd = -1;
    return 0;
}

int fflush(FILE *fp)
{
    int towrite, byteswritten;

    if (fp == NULL) {
        for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
            if (fflush(fp) == EOF) {
                return EOF;
            }
        }
        return 0;
    }
    if ((fp->flag & (_WRITE | _UNBUF)) == _WRITE) {
        towrite = fp->ptr - fp->base;
        if ((byteswritten = write(fp->fd, fp->base, towrite)) == -1 || byteswritten < towrite) {
            return EOF;
        }
        fp->ptr = fp->base;
        fp->cnt = 0;
    }
    return 0;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
        return EOF;
    }
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) {     /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;     /* can't get buffer */
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag |= _EOF;
        } else {
            fp->flag |= _ERR;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
    int byteswritten = 0, towrite, bufsize;

    if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {
        return EOF;
    }

    if (fp->base == NULL && (fp->flag & _UNBUF) == 0) {
        bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;     /* can't get buffer */
        }
        fp->ptr = fp->base;
        fp->cnt = BUFSIZ - 1;
    }

    if (!(fp->flag & _UNBUF)) {
        towrite = fp->ptr - fp->base;
        if ((byteswritten = write(fp->fd, fp->base, towrite)) == -1) {
            return _ERR;
        } else if (byteswritten < towrite) {
            return EOF;
        }
        fp->ptr = fp->base;
        fp->cnt = BUFSIZ - 1;
    }
    if ((byteswritten = write(fp->fd, &c, 1)) == -1) {
        return _ERR;
    } else if (byteswritten == 0) {
        return EOF;
    }
    return c;
}

FILE _iob[OPEN_MAX] = {     /* stdin, stdout, stderr: */
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 },
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};
