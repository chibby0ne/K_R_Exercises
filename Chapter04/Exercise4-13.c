#include <stdio.h>
#define MAX 100

void reverse(char s[]);

int main()
{
    char array[MAX];
    gets(array);
    reverse(array);
    printf("%s\n", array);
    return 0;
}


void reverse(char s[])
{
    int i, j, med, temp;
    for (i=0; s[i]!='\0'; i++)
        ;
    j=--i;
    med=i/2;
    for (i=0, j; i!=j && j>med; i++, j--)
    {
        temp=s[i];
        s[i]=s[j];
        s[j]=temp;
    }
}
