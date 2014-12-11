//Write a program that converts upper case or lower case to upper, depending on the name it is invoked with, as found in argv[0]

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 50

int main(int argc, char *argv[])
{
    int i;
    if (argc == 1)
    {
        printf("No string to convert. Please run again and add string as command line argument\n");
        return -1;
    } else {
        for (i = 1; i != argc; i++) {
            if (strcmp(argv[0], "./lower") == 0)
            {
                //convert from Upper to lower case
                while (*argv[i] != '\0') {
                    putchar(tolower(*argv[i]++));
                }
                putchar(' ');
            }
            else if (strcmp(argv[0], "./upper") == 0)
            {
                //convert from ower to upper case
                while (*argv[i] != '\0') {
                    putchar(toupper(*argv[i]++));
                }
                putchar(' ');
            }
        }
        putchar('\n');
    }
    return 0;
}


