/*
File: Exercise7-5.c
Author: Antonio Gutierrez 
Description: Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and the number conversion 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>


#define MAXOP 100           // max size of operands and operators
#define NUMBER '0'

void push(double d);
double pop(void);
int getch(void);
void ungetch(int);
int getop(char s[]);



int main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
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
                if (op2 != 0.0) {
                    push(pop() - op2);
                } else {
                    printf("error: division by zero\n");
                }
            case '\n':
                printf("\t%.8g\n", pop());
            default:
               printf("error: unknown command %s\n", s); 
               break;
        }
    }
    return 0;
}

/*
int getop(char s[])
{
    
    int c, i, rc;
    static char lastc[] = " ";

    sscanf(lastc, "%c", &c);
    lastc[0] = ' ';
    while((s[0] = c) == ' ' || c == '\t') {
        if (scanf("%c", &c) == EOF) {
            c = EOF;
        }
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {      // not a number 
        return c;
    }
    i = 0;
    if (isdigit(c)) {               // collect integer part 
        do {
            rc = scanf("%c", &c);
            if (!isdigit(s[++i] = c)) {
               break; 
            }
        } while(rc != EOF);
    }
    if (c == '.') {                 // collect fraction part 
        do {
            rc = scanf("%c", &c);
            if (!isdigit(s[++i] = c)) {
               break; 
            }
        } while(rc != EOF);
    }
    s[i] = '\0';
    if (rc != EOF) {
        lastc[0] = c;
    }
    return NUMBER;

}
*/

int getop(char s[])
{

    int i, c;

    while( (s[0] = c = getch()) == ' ' || c == '\t') {
        ;
    }
    s[1] = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    i = 0;
    if (isdigit(c)) {
        while( isdigit( s[++i] = c = getch() ) ) {
           ; 
        }
    }
    if (c == '.') {
        while( isdigit( s[++i] = c = getch() ) ) {
            ;
        }
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c)
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }

}

#define MAXVAL 100          //maximum depth of val stac

int sp = 0;                 // next free position in stack
double val[MAXVAL];         // value stac

void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void)
{
    if (sp > 0) {
       return val[--sp]; 
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}
