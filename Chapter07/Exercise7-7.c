/*  Modify the pattern finding program of Chapter 5 to take its input 
 *  from a set of named files or, if no files are named as arguments, 
 *  from the standard input. Should the file name be printed when a 
 *  matching line is found */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getlinee(char s[], int lim);

int main(int argc, char *argv[])
{
    
    char line[MAXLINE];
    long lineno = 0;
    int c, except =0, number = 0, found = 0;

    while(--argc > 0 && (*++argv)[0] == '-') {
        while(c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (argc != 1) {
        printf("Usage: find -n -x pattern\n");
    } else {
        while(getlinee(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number) {
                    printf("%ld ", lineno);
                }
                printf("%s\n", line);
                found++;
            }
        }
    }
    return found;
}

int getlinee(char s[], int lim)
{
   int c, i;
   for (i = 0; i != lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
       s[i] = c;
   }
   if (c == '\n') {
       s[i] = c;
       ++i;
   }
   s[i] = '\0';
   return i;
}
