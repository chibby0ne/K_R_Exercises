#include <stdio.h>
#define MAX 100

void strnncpy(char *s, char *t, int n);
void strnncat(char *s, char *t, int n);
int strnncmp(char *s, char *t, int n);
void getline(char *s, int lim);

int main()
{
    int n;
    n=3;
    char a[MAX];
    char b[MAX];
    getline(a, MAX);
    getline(b, MAX);
    strnncpy(a,b,n);
    printf("%s\t%s\n", a, b);

    printf("Insert second line\n");
    getline(b, MAX);
    strnncat(a,b,n);
    printf("%s\t%s\n", a, b);

    printf("Insert second line\n");
    getline(b,MAX);
    printf("%s\t%s\t%d\n", a, b, strnncmp(a,b,n));
    return 0;
}

void getline(char *s, int lim)
{
    int i;
    i=(int)s;
    for ( ; (int)s-i<lim-1 && (*s=getchar())!=EOF && *s!='\n' ; s++)
        ;
    *s='\0';
}


void strnncpy(char *s, char *t, int n)
{
    for (; n>0; s++, t++, n--)
        *s=*t;
}


void strnncat(char *s, char *t, int n)
{
    for ( ; *s!='\0'; s++)
        ;
    for ( ; n>0; s++, t++, n--)
        *s=*t;
}


int strnncmp(char *s, char *t, int n)
{
    for ( ; n-1>0 ; s++, t++, n--)
        ;
    if (*s=='\0')
        return 0;
    else
        return *s - *t;
}
