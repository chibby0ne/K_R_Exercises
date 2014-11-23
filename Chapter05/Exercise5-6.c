#include <stdio.h>
#include <ctype.h>
#define MAX 100

int getline(char *s, int lim);
int atoii(char *s);
void itoaa(int n, char *s);
void reversee(char *s);
int strindexx(char *s, char *t);
int strlenn(char *s);
int strindexxx(char s[], char t[]);

int main()
{
    int len,num,value,index,indexx;
    value=22;
    char a[]= "Hola";
    char b[MAX];
    char c[MAX];
    char d[]="hello world";
    char e[]="wor";
    char f[]="-12";
    len=strlenn(a);
    printf("%d\n", len);
    printf("Enter string\n");
    num=getline(b,MAX);
    printf("%d\n", num);
    itoaa(value, c);
    printf("%s\n", c);
    getchar();
    index=strindexxx(d,e);
    printf("%d\n",index);
    indexx=strindexx(d,e);
    printf("%d\n",indexx);
    getchar();
    printf("%d\n",atoii(f));
    return 0;
}



int getline(char *s, int lim)
{
    char *p;
    p=s;
    while (p-s<lim-1 && (*p=getchar())!=EOF && *p!='\n')
        p++;
    if (*p=='\n')
        *p++='\n';
    *p='\0';
    return p-s;
}


int atoii(char *s)
{
    int i,n,sign;
    for (i=0; isspace(*(s+i)); i++)
        ;
    sign=(*(s+i)=='-') ? -1 : 1;
    if (*(s+i)=='+' || *(s+i)=='-')
        i++;
    for (n=0; isdigit(*(s+i)); i++)
        n=10*n+(*(s+i)-'0');
    return sign*n;
}

/*itoa: convert n to characters in s*/
void itoaa(int n, char *s)
{
    int sign;
    if ((sign=n)<0)
        n=-n;
    do {
        *s++= n%10 +'0';
    } while ((n/=10)>0);
    if (sign < 0)
        *s++='-';
    *s='\0';
    reversee(s);
}

void reversee(char *s)
{
    char *p;
    char temp;
    p=s-(strlenn(s)-1);
    for ( ; p<s; p++, s--)
    {
        temp=*s;
        *s=*p;
        *p=temp;
    }
}

int strlenn(char *s)
{
    char *p;
    p=s;
    while (*s++!='\0')
        ;
    return s-p;
}

int strindexx(char *s, char *t)
{
    int i,j,k;
    for (i=0; *(s+i)!='\0'; i++)
    {
        for (j=i, k=0; *(t+k)!='\0' && *(s+j)==*(t+k); j++, k++)
            ;
        if (k>0 && *(t+k)=='\0')
            return i;
    }
    return -1;


}

int strindexxx(char s[], char t[])
{
    int i,j,k;
    for (i=0; s[i]!='\0'; i++)
    {
        for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
            ;
        if (k>0 && t[k]=='\0')
            return i;
    }
    return -1;
}
