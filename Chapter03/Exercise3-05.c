#include <stdio.h>
#define MAX 100
void prog();
void reverse(char s[], int j);
void getlinee(char s[], int limit);
int atoi(char s[]);
void itob(int n, char s[], int b);

int main()
{
    int fir=1;
    char c;
    while(1)
    {
        if (fir)
        {
            prog();
            fir=0;
        }
        else
        {
            printf("\nDo you want to continue(Y/N)");
            if ((c=getchar())=='Y' || c=='y')
            {
                getchar();
                prog();
            }
            else if (c=='N' || c== 'n')
            {
                printf("\nGood Bye");
                break;
            }
            else
                printf("Don't understand that code\n");
        }
    }
    return 0;
}

void prog()
{
    int n;
    int b;
    char n_str[MAX];
    char b_str[MAX];
    char str[MAX];
    printf("Enter the number n\n");
    getlinee(n_str,MAX);
    n=atoi(n_str);
    printf("Enter the base b\n");
    getlinee(b_str,MAX);
    b=atoi(b_str);
    switch (b){
        case 2:
            itob(n,str,2);
            break;
        case 8:
            itob(n,str,8);
            break;
        case 10:
            itob(n,str,10);
            break;
        case 16:
            itob(n,str,16);
            break;
        default:
            break;
    }
}

int atoi(char s[])
{
    int i,n,sign;
    n=i=0;
    if (s[i]=='-')
        sign=-1;
    else
        sign=1;
    for (i=0;s[i]>='0' && s[i]<='9'; i++)
        n=10*n+(s[i]-'0');
    return sign*n;
}

void itob(int n, char s[], int b)
{
    int i;
    for(i=0; n>=b; i++)
    {
        if (n%b > 10)
            s[i]=n%b+'A'-10;
        else
            s[i]=n%b+'0';
        n/=b;
    }
    if (n>10)
        s[i++]=n+'A';
    else
        s[i++]=n+'0';
    s[i]='\0';
    reverse(s,i);
    for (i=0; s[i]!='\0'; i++)
        printf("%c", s[i]);
}

void reverse(char s[], int j)
{
    char temp;
    int i;
    for (i=0, j-=1; i<j; i++, j--)
    {
        temp=s[i];
        s[i]=s[j];
        s[j]=temp;
    }
}


void getlinee(char s[], int limit)
{
    int c,i;
    for (i=0; i<limit-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i]=c;
    if (s[i]=='\n')
        s[i++]='\n';
    s[i]='\0';
}
