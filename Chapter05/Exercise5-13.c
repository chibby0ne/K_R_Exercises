#define _GNU_SOURCE
#define macro _POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <line.h>

#define MAXLINES 30
#define MAXLINE 80

void printlines(char *linesarray[], int n, int numberlines);
int readlines(char *linesarray[]);
int getline(char line[], int max);

int main(int argc, char *argv[])
{
    char *linesarray[MAXLINES];
    int nlines;
    int n;

    if (argc == 1)
        n=4;
    else if (argc == 2)
        if (*argv[1]=='-')
            n=atoi((argv[1]+1));
    else
    {
        printf("Not a valid argument. Argument is of type int positive and starts with '-'\n");
        return 0;
    }

    if ( (nlines=readlines(linesarray)) > 0)
        printlines(linesarray, n, nlines);
    else
        printf("YOU MADE A SERIOUS MISTAKE\n");
    return 0;
}

int readlines(char *linesarray[])
{
    char line[MAXLINE];
    int len;
    char *p;
    int numberlines;

    numberlines=0;
    while (( len=getline(line,MAXLINE)) > 0)
    {
        if (numberlines >= MAXLINES || (p=malloc(len))==0)
            return 0;
        else
        {
            line[len-1]='\0';           //erase newline
            strcpy(p,line);             //copy array to new pointer in order to be stored in the spaced reserved to it by malloc
            linesarray[numberlines++]=p;
        }
    }
    return numberlines;
}

void printlines(char *linesarray[], int n, int numberlines)
{
    int i;

    if (n>numberlines)
        for (i=0; i<numberlines; i++)
            printf("%s\n", linesarray[i]);
    else
        while (n)
            printf("%s\n", linesarray[numberlines-(n--)]);
}

int getline(char line[], int max)
{
    int i,c;
    for (i=0; i<max-1 && (c=getchar())!=EOF && c!='\n'; i++)
        line[i]=c;
    if (c == '\n')
        line[i++]=c;
    line[i]='\0';
    return i;
}
