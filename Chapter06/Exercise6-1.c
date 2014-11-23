#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

int getword(char *, int);
int binsearch(char *, struct key *, int);


int main()
{
    int n;
    char word [MAXWORD];

    while ((getword(word, MAXWORD)) != EOF)     // while word[0] != EOF
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)  //if word[] is valid keywork then increment count of that keyword
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)         //after all inserted words, print the ones that were entered and their respective count
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
    return 0;
}

//binary search alg
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (high + low)/2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

//get word
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;     //w is pointing to whatever word is pointing (or first position of word array)

    //skip all spaces
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
//    if (!isalpha(c))
//    {
//        *w = '\0';
//        return c;
//    }
    else
        return EOF;
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
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
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
