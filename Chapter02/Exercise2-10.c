#include <stdio.h>

int lower(int c);

int main()
{
    int c,d;
    while((c=getchar())!=EOF && c!='\n')
    {
        d=lower(c);
        printf("%c = %c\n",c,d);
        c=getchar();
    }
    return 0;
}

int lower(int c)
{
    return c>='A' && c<='Z'?c+'a'-'A':c;
}


//int lower (int c)
//{
//    if (c>= 'A' && c<='Z')
//        return c + 'a' - 'A';
//    else
//        return c;
//}
