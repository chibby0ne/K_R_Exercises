/*Write a program that prints distincts words in its input sorted in decreasing order of frequency of occurence. Precede each word by its  count */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Macros */

#define MAXWORD 100
#define MAXNODES 100


/* structures definitions */

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* Functions prototypes */

void StoreNode(struct tnode *p);
void SortList(void);
char *strdupl(char *s);
struct tnode *AddTree(struct tnode *p, char *w);
struct tnode *talloc(void);
int comment(void);
int getword(char *word, int max);
int getch(void);
void ungetch(char);


/* Global variables */
struct tnode *list[MAXNODES];
int num_tnodes = 0;

int main(int argc, char *argv[])
{
    struct tnode *root;
    int i;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalnum(word[0]))
            root = AddTree(root, word);
    StoreNode(root);
    SortList();
    for (i=0; i < num_tnodes; i++)
        printf("%d %s\n", list[i]->count, list[i]->word);
    return 0;
}

void StoreNode(struct tnode *p)
{
    if (p != NULL)
    {
        StoreNode(p->left);
        if (num_tnodes < MAXNODES)
            list[num_tnodes++] = p;
        StoreNode(p->right);
    }
}


void SortList(void)
{
    struct tnode *temp;
    int i, j, gap;

    for (gap = num_tnodes/2; gap > 0; gap /= 2)
        for (i = gap; i < num_tnodes; i++)
            for (j = i-gap; j >= 0; j-=gap)
            {
                if ((list[j]->count) >= (list[j+gap]->count))
                    break;
                temp = list[j];
                list[j] = list[j+gap];
                list[j+gap] = temp;
            }
}

struct tnode *AddTree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = strdupl(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = AddTree(p->left, w);
    else
        p->right = AddTree(p->right, w);
    return p;
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdupl(char *s)
{
    char *t;
    t = (char *) malloc(sizeof(s) + 1);
    if (t != NULL)
        strcpy(t, s);
    return t;
}

//int getword(char *word, int max)
//{
//    int c, d;
//
//    char *w = word;
//
//    while (isspace(c=getch()))
//        ;
//    if (c != EOF)
//        *w++ = c;
//    if (isalpha(c) || c == '_' || c == '#')             ///if it is either a character(word) or a preporcessor directive
//    {
//        for ( ; --max > 0; w++)
//            if (!isalnum(*w = getch()) && *w != '_')
//            {
//                ungetch(*w);
//                break;
//            }
//    }
//    else if (c == '\'' || c == '"')         //if it is a string or char literal
//    {
//        for ( ; --max > 0; w++)             //ignore whole thing after it
//        {
//            if ((*w = getch()) == '\\')
//                *++w = getch();
//            else if (*w == c)               //if char or string literal is complete then return first char
//            {
//                w++;
//                break;
//            }
//            else if (*w == EOF)             //if it is a EOF
//                break;
//        }
//    }
//    else if (c == '/')                         //if it is a comment
//    {
//        if ((d = getch()) == '*')               //if it really is a comment??
//            c = comment();
//        else
//            ungetch(d);                         //it is not quite a comment but is not a valid word
//    }
//    *w = '\0';
//    return c;
//}
int getword(char *word, int lim)
{
    char c;
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
//int comment(void)
//{
//    int c;
//    while ((c = getch()) != EOF)
//        if (c == '*')
//        {
//            if ((c = getch()) == '/')
//                break;
//            else
//                ungetch(c);
//        }
//    return c;
//}


#define BUFSIZE 10000
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    if (bufp > 0)
        return buf[--bufp];
    else
        return getchar();
}

void ungetch(char c)
{
    if (bufp >= BUFSIZE)
        printf("Error: too many characters\n");
    else
        buf[bufp++] = c;
}
