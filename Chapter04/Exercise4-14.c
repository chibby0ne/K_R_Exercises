#include <stdio.h>

#define swap(t,x,y) t temp; \
temp = x; \
x = y; \
y = temp;

int main()
{
    char a, b;
    a=10;
    b=0;
    swap (char, a, b);
    printf("%d %d\n", a, b);
    return 0;
}


