#include <stdio.h>

#define MAXLINE 1000

int getlinee(char s[], int lim);
void any(char s1[], char s2[], int s1_char, int s2_char);

int main()
{
    int first, s1_char, s2_char,c;
    char s1[MAXLINE];
    char s2[MAXLINE];
    first=0;
    while (1)
    {
        if (first!=0)
        {
            printf("Do you want to continue?(Y\\N)");
            if (((c=getchar())== 'y') || (c=='Y'))
            {
                getchar();
                printf("Please enter the first sentence\n");
                s1_char=getlinee(s1,MAXLINE);
                printf("Please enter the second sentence\n");
                s2_char=getlinee(s2,MAXLINE);
                any(s1,s2,s1_char,s2_char);
            }
            else if ((c=='n') || (c=='N'))
            {
                printf("Have a nice day!!");
                break;
            }
            else
                printf("I don't understand that command\n");
        }
        else
        {
            printf("Please enter the first sentence\n");
            s1_char=getlinee(s1,MAXLINE);
            printf("Please enter the second sentence\n");
            getlinee(s2,MAXLINE);
            any(s1,s2,s1_char,s2_char);
            first=1;
        }
    }
    return 0;
}

int getlinee(char s[], int lim)
{
    int i,c;
    for (i=0; (i<lim-1) && ((c=getchar())!=EOF) && (c!='\n'); i++)
        s[i]=c;
    s[i]='\0';
    return i;
}

void any(char s1[], char s2[], int s1_char, int s2_char)
{
    int i,j,best;
    best = s1_char;
    for (i=0; s1[i]!='\0'; i++)
    {
        for (j=0; s2[j]!='\0'; j++)
        {
            if (s1[i]==s2[j])
            {
                if (i<=best)
                {
                    best=i;
                }
            }
        }
    }
    if (best == s1_char)
        printf("-1");
    else
        printf("The location of the first char in s1 that is also in s2 is: %d\n",best);
}
