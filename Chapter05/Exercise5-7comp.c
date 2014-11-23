#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /*max #lines to be sorted */
#define MAXLEN 1000 /*max length of any input line */
#define MAXBUFF 10000

char *lineptr[MAXLINES];    /*pointers to text lines */

int readlines(char *lineprt[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int getline(char *s, int max);
char *alloc(int n);
void swap(char *v[], int i, int j);


/*sort input lines*/
int main()
{

    int nlines;     /*number of input lines read*/

    if ((nlines=readlines(lineptr, MAXLINES))>=0)
    {
        qsort(lineptr,0,nlines-1);  /* (nlines-1) is the last line in the array of pointers to the lines (lineptr) */
        writelines(lineptr,nlines); /* writing each line */
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}


int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p,line[MAXLEN];

    nlines=0;
    while ((len=getline(line, MAXLEN)) > 0)
    {
        if (nlines >= maxlines || ((p=alloc(len))==NULL)) /*if the number of lines is bigger than the max (5000) or if there's no free space of that size */
            return -1;
        else
        {
            line[len-1]='\0';       /*delete newline*/
            strcpy(p,line);         /*copy the string from line (used in getline) to the space pointed by the pointer p*/
            lineptr[nlines++]=p;    /*assign the address of line p to the corresponding line pointer, and the number of lines is incremented*/
        }
    }
    return nlines;      /*return the number of lines to main */
}

/*writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i=0; i<nlines; i++)
        printf("%s\n", lineptr[i]);
}

int getline(char *s, int max)
{
    int c,i;

    for (i=0; i<=max-1 && (c=getchar())!= EOF && c!='\n'; i++, s++)
    {
        *s=c;
    }
    if (c=='\n')
    {
        *s++='\n';
        i++;
    }
    *s='\0';
    return i;
}

char allocbuf[MAXBUFF];
char *allocp=allocbuf;

char *alloc(int n)
{

    if (allocbuf + MAXBUFF - allocp >= n)
    {
        allocp+=n;
        return allocp-n;
    }
    else
        return 0;
}

/*qsort : sort v[left]... v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;

    if (left >= right)
        return;
    swap(v, left, (left + right)/2);
    last=left;
    for (i=left+1; i <= right; i++)
    {
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/*swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

