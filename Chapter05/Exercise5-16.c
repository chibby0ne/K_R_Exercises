#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#define MAXLINES 30
//external variables
char *linesarray[MAXLINES];
int directory;
int fold;

//function prototypes
int readlines(char *linesarray[], int maxlines);
void printlines(int nlines);
void qsorts(char *linesarray[], int left, int right, int (*comp)(char *, char *));
void swap(char *linesarray[], int left, int right);
int numcmp(char *s1, char *s2);
void writelines(int nlines, void (*print)(int));
int getline(char s[], int lim);
void printreverse(int nlines);
void printnormal(int nlines);
int charcmp(char *s1, char *s2);
char *alloc(int n);

int main(int argc, char *argv[])
{
    int nlines;
    int numeric=0;
    int reverse=0;
    int i;
    char c;

        for (i=1; --argc>0 && *argv[i]=='-'; i++)
        {
            c=(*(argv[i]+1));
            switch (c)
            {
                case 'n':
                    numeric=1;
                    break;
                case 'r':
                    reverse=1;
                    break;
                case 'f':
                    fold=1;
                    break;
                case 'd':
                    directory=1;
                    break;
                default:
                    printf("You just made ANOTHER HUGE MISTAKE\n");
                    return 0;
            }
        }
    fold=1;
    directory=1;

    printf("fold=%d\n", fold);
    printf("directory=%d\n", directory);
//    if (argc > 1 && (strcmp(argv[1], "-n")) == 0)
//        numeric=1;
    if ((nlines=readlines(linesarray, MAXLINES)) > 0)
    {
        if (numeric)
            qsorts(linesarray, 0, nlines-1, (int (*)(char *, char *))(numcmp));
        else
            qsorts(linesarray, 0, nlines-1, (int (*)(char *, char *))(charcmp));
        writelines(nlines, (void (*)(int))(reverse ? printreverse : printnormal));
    }
    else
        printf("YOU MADE A HUGE MISTAKE....\n");
    return 0;
}


#define ALLOCSIZE 1000
char allocbuf[ALLOCSIZE];
char *allocp=allocbuf;

char *alloc(int n)
{
    if (allocbuf+ ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;
    }
    else
        return NULL;
}

#define MAXLENGHT 100
int readlines(char *linesarray[], int maxlines)
{
    int len;
    char *p;
    int nlines;
    char line[MAXLENGHT];

    nlines=0;
    while ((len=getline(line,MAXLENGHT)) > 0)
    {
        if (nlines >= maxlines || (p=alloc(len)) == NULL)
            return 0;
        else
        {
            line[len-1]='\0';     //delete newline
            strcpy(p, line);
            linesarray[nlines++]=p;
        }
    }
    return nlines;
}

void qsorts(char *linesarray[], int left, int right, int (*comp)(char *, char *))
{
    int i, last;

    if (left >= right)
        return;
    swap(linesarray, left, (left+right)/2);
    last=left;
    for (i=left+1; i <= right; i++)
        if ((*comp)(linesarray[left], linesarray[i]) > 0)
            swap(linesarray, ++last, i);
    swap(linesarray, left, last);
    qsorts(linesarray, left, last-1, comp);
    qsorts(linesarray, last+1, right, comp);
}

void writelines(int nlines, void (*print)(int))
{
    (*print)(nlines);
}

void printreverse(int nlines)
{
    int i;

    for (i=nlines-1; i>=0; i--)
        printf("%s\n", linesarray[i]);
}

void printnormal(int nlines)
{
    int i;

    for (i=0; i<nlines; i++)
        printf("%s\n", linesarray[i]);
}


void swap(char *linesarray[], int left, int right)
{
    char *temp;

    temp=linesarray[right];
    linesarray[right]=linesarray[left];
    linesarray[left]=temp;
}

int numcmp(char *s1, char *s2)
{
    double v1,v2;

    v1=atof(s1);
    v2=atof(s2);

    if (v1 > v2)
        return 1;
    else if (v1 == v2)
        return 0;
    else
        return -1;
}

int getline(char s[], int lim)
{
    int i,c;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i]=c;
    if (c == '\n')
        s[i++]=c;
    s[i]='\0';
    return i;
}

int charcmp(char *s1, char *s2)
{
    char a;
    char b;

    do{
        if (directory)
        {
            while (!isalnum(tolower(*s1)) && tolower(*s1)!=' ' && *s1!='\0')
                s1++;
            while (!isalnum(tolower(*s2)) && tolower(*s2)!=' ' && *s2!='\0')
                s2++;
        }
    a = fold ? tolower(*s1) : *s1;
    b = fold ? tolower(*s2) : *s2;

    if (a == b && a == '\0')
        return 0;

    s1++;
    s2++;

    } while(a == b);
    return (a - b);
}
