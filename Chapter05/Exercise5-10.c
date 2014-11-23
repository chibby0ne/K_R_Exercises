#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUMBER 0
#define MAXOPER 50

void push (double n);
double pop(void);

double atof(char *s);
int getop(char *s);

int getch(void);
void ungetch(int n);

void ungets(char *s);



int main(int argc, char *argv[])
{
    double op2;
    char s[MAXOPER];


    while (--argc > 0)
    {
        ungets(" ");
        ungets(*++argv);
        switch (getop(s))
        {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop()+pop());
                break;
            case '-':
                op2=pop();
                push(pop()-op2);
                break;
            case 'm':
                push(pop()*pop());
                break;
            case 'd':
                op2=pop();
                if (op2!=0.0)
                    push(pop()/op2);
                else
                    printf("math error: divide by 0\n");
                break;
            default:
                printf("error: unindentified character %s\n", s);
                argc=1;
                break;
        }
    }
    printf("result is %f\n", pop());
    return 0;
}


void ungets(char *s)
{
  int len;
  len = strlen(s);
  while (len > 0)
    ungetch(s[--len]);
}



int getop(char *s)
{
    int c;
    while ((*s=c=getch())==' '||c=='\t')
        ;
    *(s+1)=0;
    if (!isdigit(c) && c!= '.')
        return c;
    if (isdigit(c))
        while (isdigit(*++s=c=getch()))
            ;
    if (c=='.')
        while (isdigit(*++s=c=getch()))
            ;
    *s='\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
char *bufp=buf;

int getch(void)
{
    return ((int)(bufp-buf)>0) ? *--bufp : getchar();
}

void ungetch(int n)
{
    if ((int)(bufp-buf)>=BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        *bufp++=n;
}

#define MAXOPERANDS 80

double sp[MAXOPERANDS];
double *val=sp;

void push (double n)
{
    if ((int)(val-sp)< MAXOPERANDS)
        *val++=n;
    else
        printf("error: stack full, can't push%g\n",n);
}

double pop(void)
{
    if (val-sp > 0)
        return *--val;
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

double atof(char *s)
{
    int sign;
    double val, pow;
    while (*s == ' ' ||*s == '\t')  //skip blanks
        s++;
    if (*s++ == '-')
        sign=-1;
    else
        sign=1;
    for (val=0.0; isdigit(*s); s++)
        val=10.0*val+ (*s-'0');
    if (*s=='.')
        s++;
    for (pow=1.0; isdigit(*s); s++)
    {
        val=10.0*val+ (*s-'0');
        pow*=10.0;
    }
    return sign*val/pow;
}





//#include <stdio.h>
//#define MAX 100
//
//
//void convert(char **s);
//void solve(void);
//
//char operators[MAX];
//int operands[MAX];
//int i;
//int j;
//
//char *arrayp[]={"expr", "2", "3", "4", "+", "*", NULL};
//int arrayc=6;
//
//char *p=arrayp;
//
//
//int main(int argc, char *argv[])
//{
//
//    while (--arrayc > 0)
//    {
//        convert(arrayp);
//    }
//    --i;
//    --j;
//    solve();
//    printf("%d",*operands);
//    return 0;
//}
//
//
//void convert(char **s)
//{
//    int sign,num;
//    num=0;
//    sign=(*(*s) == '-') ? -1 : 1;
//
//    if (*(*s) >='0' && *(*s) <='9')
//    {
//        while (*(*s) >= '0' && *(*s) <= '9')
//            num = 10 * num + (*(*s++) - '0');
//        operands[i++]=num;
//    }
//
//    else if (*(*s)=='+' || *(*s)=='-' || *(*s)=='*' || *(*s)=='/')
//        operators[j++]=*(*s)++;
//}
//
//
//void solve(void)
//{
//    while (i>=0 && j>=0)
//    {
//        switch (operators[j])
//        {
//            case '+':
//                operands[i-1]=operands[i-1]+operands[i];
//                break;
//            case '-':
//                operands[i-1]=operands[i-1]-operands[i];
//                break;
//            case '*':
//                operands[i-1]=operands[i-1]*operands[i];
//                break;
//            case '/':
//                operands[i-1]=operands[i-1]/operands[i];
//                break;
//        }
//        i--;
//        j--;
//    }
//}
