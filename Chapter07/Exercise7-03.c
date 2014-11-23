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



#define HEXADECIMAL_LOW 1
#define HEXADECIMAL_UPP 2
#define OCTAL 3
#define MAX 1000
#define SCIENTIFIC_LOW 4
#define SCIENTIFIC_UPP 5


void minprintf(char *fmt, ...);
char choose_hex_number(int num);
void convert_to(int number, int type, char value[]);
void convert_scientific(double dval, int which_case, char value[]);
void reverse_string(char s[]);
char num_to_char(int num);

int main(int argc, const char *argv[])
{
    int a = 200;
    char s[] = "Hello there";
    printf("Testing strings:\n");
    minprintf("Well hello %s\n", "mr. ups man");
    minprintf("Well hello %s\n", s);

    printf("Testing ints:\n");
    minprintf("Well hello %d\n", a);

    printf("Testin octals:\n");
    minprintf("Well hello %o\n", a);

    printf("Testin hexadecimals:\n");
    minprintf("Well hello %x\n", a);
    minprintf("Well hello %X\n", a);

    printf("Testin character:\n");
    minprintf("Well hello %c\n", 'a');

    printf("Testing addreses:\n");
    minprintf("Well hello %p\n", &a);
    return 0;
}

void convert_to(int number, int type, char value[])
{
    int i;
    int what;
    if (type == OCTAL) {
        for (i = 0; number > 7; i++) {
            value[i] = num_to_char(number % 8) ;
            number /= 8;
        }
        value[i] = num_to_char(number);
        value[++i] = '\0';
    } else {
        for (i = 0; number > 15; i++) {
            if (type == HEXADECIMAL_UPP) {
                value[i] = choose_hex_number(number % 16);
            } else {
                value[i] = (char) tolower(choose_hex_number(number % 16));
            }
            number /= 16;
        }
        if (type == HEXADECIMAL_UPP) {
            value[i] = choose_hex_number(number);
        } else {
            value[i] = (char) tolower(choose_hex_number(number));
        }
        value[++i] = '\0';
    }
    reverse_string(value);
}

void reverse_string(char s[])
{
    char temp[MAX];
    int i;
    int len = strlen(s);
    for (i = 0; s[i] != '\0'; i++) {
        temp[i] = s[len - i - 1];
    }
    temp[i] = '\0';
    for (i = 0; temp[i] != '\0'; i++) {
        s[i] = temp[i];
    }
}

char choose_hex_number(int num)
{
    if (num < 10) {
        return num_to_char(num);
    } else if (num == 10) {
        return 'A';
    } else if (num == 11) {
        return 'B';
    } else if (num == 12) {
        return 'C';
    } else if (num == 13) {
        return 'D';
    } else if (num == 14) {
        return 'E';
    } else {
        return 'F';
    }
}

void convert_scientific(double dval, int which_case, char value[])
{
    int exp = 0;
    while (dval >= 10) {
        dval = dval / 10;
    }

}


char num_to_char(int num)
{
    return num + 48;
}

void minprintf(char *fmt, ...)
{
    va_list ap;
    char *p, *sval;
    int ival;
    double dval;
    void *aval;
    char value[MAX];

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%' ) {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'o':
                ival = va_arg(ap, int);
                convert_to(ival, OCTAL, value);
                printf("0%s", value);
                break;
            case 'x':
                ival = va_arg(ap, int);
                convert_to(ival, HEXADECIMAL_LOW, value);
                printf("0x%s", value);
                break;
            case 'X':
                ival = va_arg(ap, int);
                convert_to(ival, HEXADECIMAL_UPP, value);
                printf("0X%s", value);
                break;
            case 'c':
                ival = va_arg(ap, int);
                printf("%c", ival);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++) {
                    putchar(*sval);
                }
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 'e':
                dval = va_arg(ap, double);
                convert_scientific(dval, SCIENTIFIC_LOW, value);
                printf("%s", value);
                break;
            case 'E':
                dval = va_arg(ap, double);
                convert_scientific(dval, SCIENTIFIC_UPP, value);
                printf("%s", value);
                break;
            case 'p':
                aval = va_arg(ap, void *);
                printf("%p", aval);
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);
    putchar('\n');
}


