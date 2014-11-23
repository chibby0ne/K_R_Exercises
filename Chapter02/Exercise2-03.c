//write a function htoi(s) that converts a strigns of hexadecimal digits into its equivalet integer value

#include <stdio.h>
#include <math.h>
#define MAXLINE 1000

void htoi(char line[], int i);
int getlinee(char line[], int max);

int main()
{
    int i,j,c;
    j=0;
    i=0;
    char line[MAXLINE];
    printf("Welcome to the HEX to INT converter\nPlease enter a hexadecimal number\n");
    while (1)
    {
        if (j!=0)  //if it's not the first time
        {
            printf("Do you want to continue(Y\\N)?");
            if (((c=getchar())=='Y') || (c=='y'))
            {
                printf("\nPlease enter a hexadecimal number\n");
                c=getchar();                           //my way of ignoring the enter in getchar,otherwise it will be read in getlinee
                i = getlinee(line,MAXLINE);
                if (i>=0)
                {
                    htoi(line, i);
                }
            }
            else if ((c =='N') || (c == 'n'))
                break;
            else
                printf("I don't understand that command\n");
        }
        else
        {
            i = getlinee(line,MAXLINE);
            if (i>=0)
            {
                htoi(line, i);
                j=1;

            }
        }
    }
    return 0;
}

int getlinee(char s[], int lim)
{
    int i,c;
    i=0;
    while (i<lim-1 && (c=getchar())!=EOF && c!='\n')
    {
        if ((c>='0' && c<='9') || (c>='a' && c<='f') || (c>='A' && c<='F'))
        {
            s[i]=c;
            ++i;
        }
        else
            printf("This is not a hexadecimal number. Please enter a valid hexadecimal number\n");
    }
    return i-1;  //have to substract one because the last char inputed also increments the count!!
}


void htoi(char hex[], int num)
{
    int i, j;
    int result;
    result = 0;
    for (i=num, j=0; i>=0; i--, j++)
    {
        if (hex[i]>= '0' && hex[i]<='9')
        {
            result = pow(16,j)*(hex[i] % 48) + result;
        }
        else if (hex[i]>= 'a' && hex[i] <='f')
        {
            result = pow(16,j)*((hex[i] % 97) + 10) + result;
        }
        else
        {
            result = pow(16,j)*((hex[i] % 65) + 10) + result;
        }
    }
    printf("%d\n", result);
}
