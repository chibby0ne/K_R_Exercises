#include <stdio.h>
#include <math.h>
#include <ctype.h>

int getfloat(double *p);
int getch(void);
void ungetch(int let);

int main()
{
    double a;
    a=0.0;
    int b;
    b=getfloat(&a);
    printf("%.16f\n %d", a, b);
    getch();
    return 0;
}




int getfloat(double *p)
{
    int c,i,sign;
    for (c=getch(); isblank(c); c=getch())
        ;
    sign = (c == '-') ? -1 : 1;
    if (isalpha(c))
        return 0;

    if (isdigit(c) || c== '.')
    {
        for ( ;isdigit(c); c=getch())
            *p = *p * 10 + (c - '0');
        if (c == '.')
        {
            for (c=getch(), i=1; isdigit(c); c=getch(), i++)
                *p = *p + (c -'0')/(pow(10.0,i));
        }
        *p *= sign;
    }
    return c;
}
