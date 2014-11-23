/* Write a program that will print arbitrary input in a sensible way. 
 * As a minimun it should print non-greaphics characters in octal or 
 * hexadecimal according to local custom, and break long text lines */

#include <stdio.h>
#include <ctype.h>


#define OCT 0
#define HEX 1
#define MAX_LINE_LENGTH 70

int print_usage(void);
int get_arguments(int argc, const char *argv[], int *output);
void print_characters(int *output);

int main(int argc, const char *argv[])
{
    int output;
    if (get_arguments(argc, argv, &output) == -1) {
        return -1;
    }
    print_characters(&output);
    return 0;
}

int get_arguments(int argc, const char *argv[], int *output)
{
    int ret = 0;
    if (argc == 2) {
        if (*argv[1] == '-') {
            if (*++argv[1] == 'o') {
                *output = OCT;
            } else if (*argv[1] == 'x') {
                *output = HEX;
            } else {
                ret = print_usage();
            }
        }
    } else {
        ret = print_usage();
    }
    return ret;
}

int print_usage(void)
{
    printf("Correct usage: ./print_sensible [OPTION]\nwhere OPTION is: -o for octal or -x for hexadecimal\n");
    return -1;
}

void print_characters(int *output)
{
    int count_length = 0;
    int c;

    while ((c = getchar()) != EOF) {
        // if non-graphic
        if (isprint(c) != 0) {
            if (*output == OCT) {
                printf("0%-3o ", c);
            } else {
                printf("0x%x ", c);
            }
        } else {
            putchar(c);
        }
        count_length += 4;      // octal has a 0 + at least 3 more chars, hexa has 0x + as many chars as needed which is 2 for ASCII (7 bits => 2 bits hex)
        if (count_length >= MAX_LINE_LENGTH) {
            putchar('\n');
            count_length = 0;
        }
    }
}
