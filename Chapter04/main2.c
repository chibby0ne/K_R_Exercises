#include <stdio.h>


int getline (char s[], int max);
int strincmp(char s[], char t[]);
void clr(char s[]);


int main()
{
    char ans[] = "apple";
    char array[20];
    printf("Guess my favorite fruit\n");
    while (getline(array,20) > 0 )
        if (!strincmp(ans,array))
        {
            printf("The answer is correct\n");
            break;
        }
        else
        {
            printf("%s not the answer\nTry it again\n", array);
        }
    return 0;
}


int getline (char s[], int max)
{
    int i,c;
    for (i=0; i<max-1 && (c=getchar())!= EOF && c!='\n' ;i++ )
        s[i]=c;
    s[i]='\0';
    return i;
}


int strincmp(char s[], char t[])
{
    int i=0;
    while (s[i]==t[i])
    {
        if (s[i]=='\0')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

void clr(char s[])
{
    s[0]='\0';
}
