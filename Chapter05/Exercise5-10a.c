#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getlinee(char s[], int lim);

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int found=0;

    if (argc != 2)
        printf("Usage: find pattern\n");
    else
        while (getlinee(line,MAXLINE) > 0)
        {
            if (strstr(line, argv[1]) != NULL)
            {
                printf("%s", line);
                found++;
            }
        }
    return found;
}

int getlinee(char s[], int lim)
{
    int i, c;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i]=c;
    if (s[i] == '\n')
        s[i]='\n';
    i++;
    s[i]='\0';
    return i;
}
