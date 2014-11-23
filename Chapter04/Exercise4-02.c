#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100

double atof(char number[]);
void getline(char string[], int max);


int main()
{
    char numb[MAXLINE];
//    char number[]="123.45e-6";
//    printf("%s\n%f\n", number, atof(number));
    while (1)
    {
        getline(numb,MAXLINE);
        printf("%f\n",atof(numb));
    }

    return 0;
}

double atof(char s[])
{
    double val, power;
    int i, sign, exp_sign, exp, exp_val;
    exp_val=1;


    for (i=0; isspace(s[i]); i++)
        ;
    sign = (s[i]=='-') ? -1 : 1;
    if (s[i]=='+' || s[i]== '-')
        i++;
    for (val=0.0; isdigit(s[i]); i++)
        val = val * 10 + (s[i]-'0');
    if (s[i]=='.')
        i++;
    for (power=1.0; isdigit(s[i]); i++)
    {
        val = val * 10 + (s[i]- '0');
        power *= 10;
    }
    if (s[i]== 'e' || s[i]== 'E')
    {
        i++;
        exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i]=='+' || s[i]== '-')
            i++;
        for (exp=0; isdigit(s[i]); i++)
            exp=exp * 10 +  (s[i] - '0');
        while (exp>0)
        {
            exp_val *= 10;
            exp--;
        }
    }
    if (exp_sign == 1)
        return ((sign*val*exp_val)/power);
    else
        return ((sign*val)/(exp_val*power));
}

void getline(char s[], int limit)
{
    int c,i;
    for (i=0; i<limit-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i]=c;
    if (s[i]=='\n')
        s[i++]='\n';
    s[i]='\0';
}
