#include <stdio.h>
#define MAX 100

unsigned righttrot(unsigned x, int n);

int main()
{
    unsigned num,k;
    int n,c;
    for (num=511; num<30000; num+=511)
    {
        for (n=1; n<=16; n++)
        {
            k=righttrot(num,n);
            printf("(%u,%d)=%u\n", num, n, k);
        }
        while((c=getchar())!='\n')
            ;
    }
    return 0;
}

unsigned righttrot(unsigned x, int n)
{
    return ((~0U&x)>>n)|((~(~0<<n)&x)<<(16-n));
}
