/*  Modify the pattern finding program of Chapter 5 to take its input 
 *  from a set of named files or, if no files are named as arguments, 
 *  from the standard input. Should the file name be printed when a 
 *  matching line is found */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getlinee(char s[], int lim);
int find_pattern(FILE *fp, char pat[], int except, int number, char *name);

int main(int argc, char *argv[])
{
    
    FILE *fp;
    char pattern[MAXLINE];
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
    // save pattern
    if (argc >= 1) {
        strcpy(pattern, *argv);
    } else {
        printf("Usage: find -n -x pattern\n");
    }
    // find pattern from either stdin or files
    if (argc == 1) {                                        // from if no more argmuments then from stdin
        find_pattern(stdin, pattern, except, number, *argv);
    } else {                                                // if more arguments then from those files
        while(--argc > 0) {                                 // while theres still a file
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "error: could not open file %s\n", *argv);
                return -1;
            } else {
                found += find_pattern(fp, pattern, except, number, *argv);
            }
        }
    }
    return found;
}

int find_pattern(FILE *fp, char pat[], int except, int number, char *name)
{
    char line[MAXLINE];
    long int linenum = 0;
    int found = 0;
    int first = 0;
    static int first_file = 0;

    while((fgets(line, MAXLINE, fp) != NULL)) {
        linenum++;
        if (first == 0 && fp != stdin) {            // print file name as long as there it isn't stdin
            if (first_file == 0) {
                first_file = 1;
            } else {
                printf("====================================\n\n");
            }
            printf("In File: %s\n", name );
            first = 1;
            
        }
        if ((strstr(line, pat) != NULL) != except) {
            if (number) {
                printf("%ld ", linenum);
            }
        }
        printf("%s\n", line);
        found++;
    }
    fclose(fp);
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
