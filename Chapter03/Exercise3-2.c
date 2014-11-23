#include <stdio.h>
#define MAX 100
#define MAX2 200

void escape (char s[], char t[]);
void escape_inv (char s[], char t[]);
void getline(char s[], int lim);

int main()
{

    char line[MAX];
    char line_vis[MAX2];
    while (1)
    {
        printf("Enter line\n");
        getline(line,MAX);
        escape(line_vis,line);
        escape_inv(line,line_vis);
    }
    return 0;
}

void getline(char s[], int lim)
{
    int i,c;
    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i]=c;
    if (c=='\n')
        s[i++]='\n';
    s[i]='\0';
}

void escape(char s[], char t[])
{
    int i,j;
    for (i=0,j=0; t[j]!='\0'; i++,j++)
    {
        switch (t[j])
        {
            case '\n':
                s[i++]='\\';
                s[i]='n';
                break;
            case '\t':
                s[i++]='\\';
                s[i]='t';
                break;
            default:
                s[i]=t[j];
                break;
        }
    }
    if (t[j]=='\0')
        s[i]='\0';
    for (i=0; s[i]!='\0'; i++)
    {
        printf("%c",s[i]);
    }
    if (s[i]=='\0')
        printf("\n");
}

void escape_inv(char s[], char t[])
{
    int i,j;
    int prev=0;
    for (i=0,j=0; t[j]!='\0'; i++,j++)
    {
        switch (t[j])
        {
            case '\\':
                if (prev!=0)
                    s[prev]='\\';
                else
                    prev=j;
                break;
            default:
                if ((j==prev+1) && j!=1)
                {
                    switch (t[j])
                    {
                        case 'n':
                            s[prev]='\n';
                            break;
                        case 't':
                            s[prev]='\t';
                            break;
                        default:
                            break;
                    }
                    i=prev;
                    prev=0;
                }
                else
                {
                    s[i]=t[j];
                }
                break;
        }
    }
    if (t[j]=='\0')
        s[i]='\0';
    for (i=0; s[i]!='\0'; i++)
    {
        printf("%c",s[i]);
    }
}
