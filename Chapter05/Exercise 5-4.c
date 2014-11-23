#include <stdio.h>
#define MAX 100

int strend(char *s, char *t);
void getline(char *s, int max);

int main()
{
    char a[MAX];
    char b[MAX];
    printf("Enter first string\n");
    getline(a,MAX);
    printf("Enter second string\n");
    getline(b,MAX);
    printf("%d", strend(a,b));
//    if (strend(a,b)== 0)
//        printf("Esa es la palabra correcta!!\n");
//    else
//        printf("Perdisteee\n");
    getchar();
    return 0;
}

void getline(char *s, int lim)
{
    int i;
    char c;
    i=(int)s;
    while ((int)s-i<lim-1 && (c=getchar())!=EOF && c!='\n')
    {
        *s=c;
        s++;
    }
    *s='\0';
}


int strend(char *s, char *t)
{
    int i; // number of chars that t has
    for (; *s!='\0'; s++)
        ;
    s--;
    for (i=0 ; *t!='\0' ; t++, i++)
        ;
    t--;
    for (; *s==*t ; s--, t--)
        i--;
    if (i)
        return 1;
    else
        return 0;
}
