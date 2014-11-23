/*The exercise requires to implement the for loop in the function getlinee WITHOUT using && or || operators*/

#include <stdio.h>

#define MAXLINE 1000

int getlinee(char line[], int maxline);
void copy(char from[], char to[]);

int main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;  //initialize the max count. for the first string it will always be stored
    while ((len = getlinee(line, MAXLINE)) >0)
    {
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)
        printf("%s", longest);
    return 0;
}

int getlinee(char s[], int lim)
{
    int c,i;
//    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
//        s[i]=c;
    i=0;
    while (i<lim-1)
    {
        if ( (c=getchar()) != EOF)
        {
            if (c != '\n')
            {
                s[i] = c;
                ++i;
            }
            else
                break;

        }
        else
            break;

    }

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;
    i=0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}
