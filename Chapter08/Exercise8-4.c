/* 
Filename: Exercise8-4.c
Author: Antonio Gutierrez
Description: The Standard library function int fseek(File *fp, long offset, int origin) is identical to lseek except that fp is a file pointer instead of a file descriptor and the return value is an int status not a position. Write fseek. Make sure that your fseek coordinates properly with the buffering done for the other functions of the library.
Created: 13/10/2014
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int fseeek(FILE *fp, long offset, int origin);

int main(int argc, char *argv[])
{
    
    FILE *fp;
    fp = fopen("example.txt", "wb");
    fputs("This is an apple", fp);
    fseeek(fp, 9, SEEK_SET);
    fputs(" sam", fp);
    fclose(fp);
    return 0;
}

int fseeek(FILE *fp, long offset, int origin)
{
    int num_chars;      // num_chars written to write buffer
    int status = 0;

    // for read
    if (fp->flag & _READ) {
        // take into account the buffered read, if we are reading from current position (might be anywhere) for the offset, after that seek with updated offset, and reset buffer
        if (origin == SEEK_CUR) {
            offset -= fp->cnt;
        }
        lseek(fp->fd, offset, origin);
        fp->cnt = 0;

    // for write
    } else if (fp->flag & _WRITE) {

        // flush buffer (if it was used)
        if ((num_chars = fp->ptr - fp->base) > 0) {
            if (write(fp->fd, fp->base, nc) != nc) {
                status = -1;
            }
        }

        // if no error from flushing or it hasn't been used,  then seek
        if (status == 0) {
            status = lseek(fp->fd, offset, origin);
        }
    }

    // return status code
    return (status == 0) ? 0 : -1;
   
}

