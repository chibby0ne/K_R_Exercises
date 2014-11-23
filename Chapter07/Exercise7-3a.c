/* Revise minprintf to handle more of the other facilities for printf */

/*
File: Exercise7-3.c
Author: Antonio Gutierrez
Description: from K&R C book
*/

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

void minprintf(char *fmt, ...);

int main(int argc, const char *argv[])
{
    int a = 200;
    char s[] = "Hello there";
    printf("Testing strings:\n");
    minprintf("Well hello %s\n", "mr. ups man");
    minprintf("Well hello %s\n", s);

    printf("Testing ints:\n");
    minprintf("Well hello %d bitch %d\n", a, a);

    printf("Testin octals:\n");
    minprintf("Well hello %o\n", a);

    printf("Testin hexadecimals:\n");
    minprintf("Well hello %x\n", a);
    minprintf("Well hello %X\n", a);
    printf("Well hello %X\n", a);

    printf("Testin character:\n");
    minprintf("Well hello %c\n", 'a');

    printf("Testing addreses:\n");
    minprintf("Well hello %p\n", &a);
    return 0;
}


void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    unsigned int uval;
    double dval;
    void *aval;
    int i;
    char format_str[MAX];

    i = 0;
    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%' ) {
            putchar(*p);
            continue;
        }
        format_str[i++] = '%';
        while(*(p + 1) && !isalpha(*(p + 1))) {   // store all conversion specificators (e.g: minus sign, field width, period, precision)
            format_str[i++] = *++p;
        }
        format_str[i++] = *(p + 1);                // store conversion specifier
        format_str[i] = '\0';                      // null-terminate string
        switch (*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int);
                printf(format_str, ival);
                break;
            case 'o':
            case 'x':
            case 'X':
                uval = va_arg(ap, int);
                printf(format_str, uval);
                break;
            case 'c':
                ival = va_arg(ap, int);
                printf(format_str, ival);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf(format_str, sval);
                break;
            case 'f':
            case 'e':
            case 'E':
                dval = va_arg(ap, double);
                printf(format_str, dval);
                break;
            case 'p':
                aval = va_arg(ap, void *);
                printf(format_str, aval);
                break;
            default:
                putchar(*p);
                break;
        }
        i = 0;
    }
    va_end(ap);
    putchar('\n');
}


