/* 
Filename: Exercise8-2.c
Author: Antonio Gutierrez
Description: Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution speeds
Created: 10/10/2014
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define OPEN_MAX 20
#define PERMS 666

typedef struct flags {
    unsigned int read : 1;
    unsigned int write: 1;
    unsigned int unbuf: 1;
    unsigned int eof: 1;
    unsigned int err : 1;
    
} flags;


typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    flags flag; 
    int fd;
} FILEE;

flags stdin_flags;


FILEE iob[OPEN_MAX] = {
    {0, (char*) 0, (char *) 0, 1, 0 },
    {0, (char*) 0, (char *) 0, 1, 1 },
    {0, (char*) 0, (char *) 0, 1, 2 }
};
    

FILEE *fopenn(char *name, char *mode);
int _fillbuf(FILEE *fp);
void get(FILEE *fp);

int main(int argc, char *argv[])
{
    FILEE *fp;
    int i = 0;

    stdin_flags.read = 1;
    stdin_flags.read = 1;

    if (--argc > 0) {
        i++;
        if ((fp = fopenn(argv[i], "r")) != NULL) {
            get(fp);
        }
    }

    return 0;
}

void get(FILEE *fp)
{
    char buf[BUFSIZ];
    int n;
    while ((n = read(fp->fd, buf, BUFSIZ)) > 0) {
        write(1, buf, n);
    }
}

FILEE * fopenn(char *name, char *mode)
{
    int fd;
    FILEE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = 0; fp != iob + OPEN_MAX; ++fp) {
        if (fp->flag.read == 0 && fp->flag.write == 0) {
            break;
        }
    }
    if (fp >= iob + OPEN_MAX) {
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1) {
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag.unbuf = 0;
    fp->flag.eof = 0;
    fp->flag.err = 0;
    if (*mode == 'r') {
       fp->flag.read = 1; 
       fp->flag.write = 0; 
    } else {
       fp->flag.read = 0; 
       fp->flag.write = 1; 
    }
    return fp;
}

int _fillbuf(FILEE *fp)
{
    int bufsize;

    if ((fp->flag.read == 0) || (fp->flag.eof == 1) || (fp->flag.err == 1)) {
        return EOF;
    }
    bufsize = (fp->flag.unbuf == 1) ? 1 : BUFSIZ;
    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag.eof = 1;
        } else {
            fp->flag.err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

