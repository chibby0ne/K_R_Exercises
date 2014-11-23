#include <stdio.h>
#define MAXLINE 100

int getline(char line[], int limit);
int strrindex(char source[], char searchfor[]);

char pattern[]="abc";

int main()
{
    char line[MAXLINE];
    int found=0;
    int ind;

    while (getline(line,MAXLINE)>0)
    {
        if ((ind=strrindex(line, pattern))>=0)
        {
            printf("%s\n index:%d",line, ind);
            found++;
        }
    }
    return found;
}

int getline(char s[], int lim)
{
    int c,i;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i]=c;
    if (c=='\n')
        s[i++]='\n';
    s[i]='\0';
    return i;
}

int strrindex(char s[], char f[])
{
    int i,j,k,saved;
    saved=0;
    for (i=0; s[i]!='\0';i++)
    {
        for (j=i, k=0; f[k]!='\0' && s[j]==f[k]; j++, k++)
            ;
        if (k>0 && f[k]=='\0')
            saved=i;
    }
    if (saved)
    {
        return saved;
    }
    else
    {
        return -1;
    }
}
