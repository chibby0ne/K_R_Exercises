#include <stdio.h>
#include <limits.h>


void itoa(int n, char s[]);

int i;

int main()
{
    int n;
    char arr[100];
    while (gets(arr) > 0)
    {
        n=atoi(arr);
        itoa(n,arr);
        printf("%s\n",arr);
    }
    return 0;
}

/* converts a int into a string */
void itoa(int n, char s[])
{
    int num;
    char sign;
    if (n < 0)      //check for sign
    {
        sign = '-'; //
        if (n == INT_MIN)
            num=n=-n-1;
        else
            n=-n;       //make number positive
        itoa(n / 10, s);
    }
    else if (n / 10)
        itoa(n / 10, s);
    if (n < 0)
        s[i++]='-';
    if (i==0 && num == INT_MIN)
        s[i++]=n%10+'0'+1;
    else
        s[i++]=n%10+'0';
}
