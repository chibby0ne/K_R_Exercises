#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>


#define MAX 100


void minscanf(char *fmt, ...);
int main(int argc, const char *argv[])
{
    char c;
    int i;
    float f;
    char s[MAX];


    printf("Please type you age:\n");
    minscanf("%d", &i);
    printf("\nYour age is: %d\n", i);

    printf("Please type your letter\n");
    minscanf("\n\n\n%c", &c);
    printf("\nYour letter is:%c\n", c);


    printf("Please type your name\n");
    minscanf("\n\n%s", s);
    printf("\nYour name is:%s\n", s);

    printf("Please type your salary\n");
    minscanf("\n%f", &f);
    printf("\nYour salary is:%f\n", f);
    
    return 0;
}

void minscanf(char *fmt, ...)
{
    va_list ap;
    int i;
    char *p, *sval;
    int *ival;
    char *cval;
    float *fval;
    char format_str[MAX];
    unsigned int *uval;

    i = 0;
    va_start(ap, fmt);
    for (p = fmt; *p ; p++) {
        if (*p != '%') {
            format_str[i++] = *p;
            continue;
        }
        format_str[i++] = '%';
        while (*(p + 1) && !isalpha(*(p + 1))) {
            format_str[i++] = *++p;
        }
        format_str[i++] = *(p + 1);
        format_str[i] = '\0';;
        switch (*++p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int *);
                scanf(format_str, ival);
                break;
            case 'o':
            case 'x':
            case 'X':
                uval = va_arg(ap, unsigned int *);
                scanf(format_str, uval);
                break;
            case 'c':
                cval = va_arg(ap, char *);
                scanf(format_str, ival);
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf(format_str, ival);
                break;
            case 'f':
            case 'e':
            case 'E':
                fval = va_arg(ap, float *);
                scanf(format_str, fval);
                break;
            default:
                // mmm
                break;
        }
        i = 0;
    }
    va_end(ap);
}
