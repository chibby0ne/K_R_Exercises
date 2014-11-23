/* 
Filename: Exercise8-3.c
Author: Antonio Gutierrez
Description: Design and write _flushbuf, fflush, fclose
Created: 11/10/2014
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    
    return 0;
}

//returns char if successful, else EOF
int _flushbuf(int c, FILE *fp)
{
    unsigned int nc;        // # of characters to flush
    int bufsize;

    /* check for errors */
    if ( (fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE) {       // an error ocurred or isn't in write mode
        return EOF;
    }
    if (fp < _iob || fp >= _iob + OPEN_MAX) {           // not valid file pointer
        return EOF;
    }

    // get buffer size
    bufsize = (fp-flag & UNBUF) ? 1 : BUFSIZ;

    // if there isn't any buffer allocated (first time accesing file for writing)
    if (fp->base == NULL) {                             // is there a buffer yet?
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {    // if there was error allocating?
            fp->flag |= _ERR;
            return EOF;
        }
    } 

    // num of chars that have been buffered (stored in buffer)
    nc = fp->ptr - fp->base; 

    // try to write buffer (those chars buffers) to file
    if (write(fp->fd, fp->base, nc) != nc) {        
        fp->flag |= _ERR;
        return EOF;
    }

    
    fp->ptr  = fp->base;        // reset pointer to beginning of buffer
    *fp->ptr++ = (char) c;      // store current char
    fp->cnt = bufsize - 1;      // substract one char from size of buffer (because we stored one in previous line)
    return x;                   // return same char

}

// returns 0 if successful, else EOF
int fclose(FILE *fp)
{
    int val;

    // flush the pointer
    if ((val = fflush(fp)) != EOF) {
        fp->cnt = 0;            // zero characsters left
        fp->ptr = NULL;         // pointers to NULL
        free(fp->base);         // free buffer
        fp->base = NULL;
        fp->flag &= ~(_READ | _WRITE);               // make flags 0
    }

}

// returns 0 if successful, else EOF
int fflush(FILE *fp)
{
    int val;

    // check for valid fp
    if (fp < _iob || fp >= _iob + OPEN_MAX) {           // not valid file pointer
        return EOF;
    }
    // if it was to write then flush (write buffer to file, and reset ptr of buffer to beginning)
    if (fp->flags & _WRITE) {
        val = _flushbuf(0, fp);
    }
    fp->ptr = fp->base;
    fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    return val;
}

