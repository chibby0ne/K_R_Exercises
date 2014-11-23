
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10000

int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    char line1[MAX];
    char line2[MAX];
    char *prog = argv[0];
    int linenum = 0;
    char *c, *d;

    if (argc < 3)
    {
        printf("Too few arguments\n");
        return -1;
    }
    else if (argc == 3)
    {
        if ( (fp1 = fopen(*++argv, "r")) == NULL)
        {
            fprintf(stderr, "%s: couldn't open %s file\n", prog, *argv);
            exit(1);
        }
        else if ((fp2 = fopen(*++argv, "r")) == NULL)
        {
            fprintf(stderr, "%s: couldn't open %s file\n", prog, *argv);
            exit(2);
        }
        else
        {
            do {
                c = fgets(line1, MAX, fp1);
                d = fgets(line2, MAX, fp2);
                linenum++;
            } while (!strcmp(line1, line2) && (c != NULL || d != NULL));
            fclose(fp1);
            fclose(fp2);
            if (c == d)
            {
                printf("Files are identical\n");
                return 0;
            }
            else
            {
                printf("File differ in line %d and they were:\nFile1:\n%s-----------------------------------------------\nFile2:\n%s", linenum, line1, line2);
                return 0;
            }
        }
    }
    return 0;
}
