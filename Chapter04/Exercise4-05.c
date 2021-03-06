#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void swap(void);
double show(void);
void duplicate(void);
void clear(void);

int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type=getop(s)) != EOF)
    {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case 'c':
            clear();
            printf("Stack is cleared\n");
            break;
        case 'w':
            swap();
            break;
        case 'd':
            duplicate();
            break;
        case 'p':
            printf("%.8g", show());
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int) pop() % (int) op2);
            else
                printf("error: zero divisor\n");
            break;
        case 's':
            push(sin(pop()));
            break;
        case 'e':
            push(exp(pop()));
            break;
        case '^':
            op2 = pop();
            push(pow(pop(),op2));
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100

int sp=0;
double val[MAXVAL];

void push(double f)
{
    if (sp<MAXVAL)
        val[sp++]=f;
    else
        printf("error: stack full, can't push %g\n",f);
}

double pop(void)
{
    if (sp>0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0;
    }
}

void clear(void)
{
    val[sp]=0;  // clear the one that is pointed
    while (sp>0)
        val[--sp]=0;  // clear the next one
}

double show(void)
{
    return val[sp-1];
}

void swap(void)
{
    double temp;
    temp=val[sp-2];
    val[sp-2]=val[sp-1];
    val[sp-1]=temp;
}

void duplicate(void)
{
    val[sp]=val[sp-1];
    sp++;
}

#include <ctype.h>
int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i,c;
    while ((s[0]=c=getch()) == ' ' || c=='\t')
        ;
    s[1]=0;
    if (c!= '-' && !isdigit(c) && c!='.')
    {
        if (c == 's')
        {
            if ((s[1]=c=getch()) == 'i')
            {
                if ((s[2]=c=getch()) == 'n') // sine sin command : s
                    return 's';
                else
                    return '_'; // meaning don't understand command
            }
            else if (c== 'w')   // swap sw command : w
                return 'w';
            else
                return '_'; // meaning don't understand command
        }
        else if (c == 'd')  // duplicate dp command: d
        {
            if ((s[1]=c=getch()) == 'p')
                return 'd';
            else
                return '_';
        }
        else if (c == 'c')  // clear cl command: c
        {
            if ((s[1]=c=getch()) == 'l')
                return 'c';
            else
                return '_';
        }
        else if (c == 'e')
        {
            if ((s[1]=c=getch()) == 'x')
            {
                if ((s[2]=c=getch()) == 'p')
                    return 'e';
                else
                    return '_';
            }
            else
                return '_';
        }
        else
            return c;
    }
    i=0;
    if (c == '-')
    {
        s[i++]=c;      // s[0]= '-';
        c=getch();
    }
    if (isdigit(c))
    {
        if (s[i-1]== '-')    // if s[0] = '-' , store next char in s[1]
            s[i]=c;
        while (isdigit(s[++i]=c=getch()))
            ;
    }
    if (c=='.')
    {
        while (isdigit(s[++i]=c=getch()))
            ;
    }
    s[i]='\0';
    if (c!=EOF)
        ungetch(c);
    if (s[0] == '-' && s[1] == '\0')
        return s[0];
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp=0;

int getch(void)
{
    return (bufp>0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


