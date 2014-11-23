#include <stdio.h>
#define MAXLINE 1000

void strcat1(char s[], char t[], int len1, int len2);
int getlinee(char s[], int lim);

int main()
{
    int len1,len2,first,c;
    char s1[MAXLINE];
    char s2[MAXLINE];
    first=1;
    while(1)
    {
        if(first != 1)
        {
            printf("\nDo you want to continue?(Y\\N)");
            if(((c=getchar())== 'y') || (c=='Y'))
            {
                c=getchar();
                printf("\nPlease enter first string\n");
                len1=getlinee(s1, MAXLINE);
                printf("Please enter second string\n");
                len2=getlinee(s2, MAXLINE);
                strcat1(s1,s2,len1,len2);
                printf("The resulting string is:\n%s", s1);
            }
            else if ((c=='n')||(c=='N'))
                break;
            else
                printf("I don't understand that command\n");
        }
        else
        {
            printf("Please enter first string\n");
            len1=getlinee(s1, MAXLINE);
            printf("Please enter second string\n");
            len2=getlinee(s2, MAXLINE);
            strcat1(s1,s2,len1,len2);
            printf("The resulting string is:\n%s", s1);
            first=0;
        }
    }
    return 0;
}

int getlinee(char s[], int lim)
{
    int i;
    char c;
    for (i=0; i<lim-1 && (c=getchar())!= EOF && c!='\n' ;i++)
        s[i]=c;
    if (c == '\n')
        s[i]='\0';
    return i;
}

void strcat1(char s[], char t[], int len1, int len2)
{
    int i,j,k;
    for (i=0;i<=len1;i++)
    {
        for(j=0;j<=len2;j++)
        {
            if (s[i]==t[j])
            {
                k=i;
                while (k<len1-1)
                {
                    s[k]=s[k+1];
                    k++;
                }
                s[k]='\0';
            }
        }
    }
}
