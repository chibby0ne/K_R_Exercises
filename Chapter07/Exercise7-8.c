/* Write a program to print a set of files, starting each new one on a 
 * new page with a title and a running page count for each file */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSI "\033\["
#define CLEAR_SCREEN CSI"2J"
#define MAXLINE 10000

void print_file(char *filename, int maxlines);
void print_title_count(char *filename, int count);
int print_page(char *filename, FILE *fp, int maxlines);

int main(int argc, char *argv[])
{
    char* rows;
    int rows_num;
    int i;

    /* export enviroment variable that are only set by the shell */
    system("export LINES");

    /* now get the value */
    rows = getenv("LINES");
    rows_num = atoi(rows);

    i = 1;
    while(--argc > 0) {
        print_file(argv[i++], rows_num);
        printf("\n\n");
    }
    return 0;
}


void print_file(char *filename, int maxlines)
{
    FILE *fp;
    int status = 0;
    int page_count = 0;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("error: couldn't open %s\n", filename);
        exit(1);
    }

    page_count = 1;
    print_title_count(filename, page_count);

    while((status = print_page(filename, fp, maxlines)) != EOF) {
        page_count++;
        print_title_count(filename, page_count);
    }



}

void print_title_count(char *filename, int count)
{
    char *last_slash;
    char *title;

    last_slash = strrchr(filename, '/');
    if (last_slash == NULL) {               // there was no slash
        title = filename;
    } else {
        title = last_slash + 1;
    }
    printf("%s page %d\n", title, count);

}

int print_page(char *filename, FILE *fp, int maxlines)
{
    char line[MAXLINE];
    int count = 0;
    char *status;
    while(((status = fgets(line, MAXLINE, fp)) != NULL) && count < maxlines - 1) {
        printf("%s", line);
        count++;
    }
    if (status != NULL) {
        return 0;
    } else {
        return EOF;
    }

}





































