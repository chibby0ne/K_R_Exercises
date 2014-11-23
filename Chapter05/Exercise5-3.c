#include <stdio.h>
#define MAX 100

void strcaat(char *s, char *t);
void getline(char *s, int max);

int main()
{
    char a[MAX];
    char b[MAX];
    printf("Enter first string\n");
    getline(a,MAX);
    printf("Enter second string\n");
    getline(b,MAX);
    strcaat(a,b);
    printf("%s", a);
    getchar();
    return 0;
}

void getline(char *s, int lim)
{
    int i;
    char c;
    i=(int)s;
    while (i-(int)s<lim-1 && (c=getchar())!=EOF && c!='\n')
    {
        *s=c;
        s++;
    }
    *s='\0';
}


void strcaat(char *s, char *t)
{
    for ( ; *s!= '\0'; s++)
        ;
    for ( ; (*s=*t)!= '\0'; s++, t++ )
        ;
}


