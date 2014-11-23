#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100
#define YES 1
#define NO 0

struct tnode{
    char *word;
    int match;
    struct tnode *left;
    struct tnode *right;
};


int getword(char *, int);
int getch(void);
void ungetch(int c);
char *strcpytree(char *w);
struct tnode *talloc(void);
struct tnode *addtree(struct tnode *p, char *w, int num, int *found);
int comp(struct tnode *p, char *w, int num, int *found);
int getword(char *word, int lim);
void printtree(struct tnode *p);

int main(int argc, char **argv)
{
    struct tnode *root;
    char word[MAXWORD];
    int found = 0;
    int num;

    ///getting CL arguments
    if (--argc && (**argv == '-'))
        num = atoi(*argv+1);
    else
        num = 6;

    ///program core
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]) && strlen(word) >= num)
            root = addtree(root, word, num, &found);
        found = NO;
    }
    printtree(root);
    return 0;
}

void printtree(struct tnode *p)
{
    if (p != NULL)
    {
        printtree(p->left);
        if (p->match)
        {
            printf("%s\n", p->word);
        }
        printtree(p->right);
    }
}


struct tnode *addtree(struct tnode *p, char *w, int num, int *found)
{

    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->match = *found;
        p->word = strcpytree(w);
        p->left = p->right = NULL;
    }
    else if ((cond = comp(p, w, num, found)) < 0)
        p->left = addtree(p->left, w, num, found);
    else
        p->right = addtree(p->right, w, num, found);
    return p;
}

//allocates space for string and copies it to that place
char *strcpytree(char *w)
{
    char *s;
    s = (char *) malloc(strlen(w)+1);
    if (s != NULL)      //it was stored
        strcpy(s,w);
    return s;
}

int comp(struct tnode *p, char *w, int num, int *found)
{
    int i;
    char *t = p->word;
    for (i=0; *w == *t ; i++, t++, w++)
        if (*w == '\0')
            return 0;
    if (i >= num)
    {
        p->match = YES;
        *found = YES;
    }
    return *w - *t;
}

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

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


//int getword(char *word, int lim)
//{
// int c, d, comment(void), getch(void);
// void ungetch(int);
// char *w = word;
// while(isspace(c = getch()))
//  ;
// if(c !=EOF)
//  *w++ = c;
// if(isalpha(c) || c == '-' || c == '#'){
//  for(; --lim > 0; w++)
//   if(!isalnum(*w = getch()) && *w != '-') {
//    ungetch(*w);
//    break;
//   }
// }
// else if(c == '\'' || c == '\\'){
//  for(; --lim > 0; w++)
//   if(((*w = getch()) == '\\')
//     *++w = getch();
//   else if(*w == c) {
//    w++;
//    break;
//   }else if(*w == EOF)
//    break;
// }else if(c == '/')
//  if((d = getch()) == '*')
//   c = comment();
//  else
//   ungetch(d);
// *w = '\0';
// return c;
//}



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


