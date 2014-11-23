/* 
Filename: Exercise8-1.c
Author: Antonio Gutierrez
Description: Rewrite the program cat from Chapter 7 using read, write, open and close instead of their standard library equivalents. Perform experiments to determine the relative speeds of the two versions 
Created: 10/10/2014
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define READ_ERROR -2
#define WRITE_ERROR -3 


int filecopy(int fd1);

int main(int argc, char *argv[])
{
    int fd1;
    int status;

    if (argc == 1) {
        filecopy(STDIN);
    } else {
        while(--argc > 0) {
            if ((fd1 = open(*++argv, O_RDONLY, 0)) == EOF) {
                printf("cat: can't open %s\n", *argv);
            } else {
                status = filecopy(fd1);
                close(fd1);
                if (status == READ_ERROR) {
                    printf("cat: error reading file %s\n", *argv);
                    return READ_ERROR;
                } else if (status == WRITE_ERROR) {
                    printf("cat: error writing to stdout\n");
                    return WRITE_ERROR;
                }
            }
        }
    }
    return 0;
}

int filecopy(int fd1)
{
    int status;
    char buf[BUFSIZ];

    while (((status = read(fd1, buf, BUFSIZ)) != EOF) && status != 0) {
        if (write(STDOUT, buf, status) != status) {
            return WRITE_ERROR;
        }
    }
    if (status == EOF ) {
        return READ_ERROR;
    } else {
        return 0;
    }
}
