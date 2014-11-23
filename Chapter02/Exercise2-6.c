#include <stdio.h>

void setbits(unsigned int x, unsigned int y, int p, int n);

int main()
{
    unsigned int x,y;
    int p,n;
    for (x=0; x<30000; x+=511)
    {
        for (y=0; y<1000; y+=37)
        {
            for (p=0; p<16; p++)
            {
                for (n=1; n<=p+1; n++)
                {
                    setbits(x,y,p,n);
                }
            }
        }
    }
    return 0;
}

void setbits(unsigned int x, unsigned int y, int p, int n)
{
    printf("setbits(%d,%d,%d,%d)=%d\n",x,p,n,y, ( (x& ( (~0<<(p+1)) | ( ~(~0<<(p+1-n)) ) ) ) | ( (y & (~(~0<<n) )) <<(p+1) ) ));
}
