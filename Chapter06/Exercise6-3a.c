#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100
#define YES 1
#define NO 0

struct linkedlist {
    int linenum;
    struct linkedlist *ptr;
};

struct tnode{
    char *word;
    struct linkedlist *lines;
    struct tnode *left;
    struct tnode *right;
};

int noiseword(char *s);
int getword(char *, int);
int getch(void);
void ungetch(int c);
char *strcpytree(char *w);
struct tnode *talloc(void);
struct linkedlist *lalloc(void);
struct tnode *addtree(struct tnode *p, char *w, int linenumber);
void addline(struct tnode *p, int linenumber);
int getword(char *word, int lim);
void printtree(struct tnode *p);

int main(int argc, char **argv)
{
    struct tnode *root;
    char word[MAXWORD];
    int linenumber;

    ///getting CL arguments


    ///program core
    linenumber = 1;
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]) && noiseword(word) == -1)
            root = addtree(root, word, linenumber);
        else if (word[0] == '\n')
            linenumber++;
    }
    printtree(root);
    return 0;
}

int noiseword(char *s)
{
    char *nw[] = {
        "a",
        "an",
        "and",
        "are",
        "is",
        "in",
        "of",
        "on",
        "or",
        "that",
        "the",
        "this",
        "to"
};
    int cond, mid;
    int high = sizeof(nw) / sizeof(char *) -1;
    int low = 0;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if ( (cond = strcmp(s, nw[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}


void printtree(struct tnode *p)
{
    struct linkedlist *temp;
    if (p != NULL)
    {
        printtree(p->left);
        printf("%s: ", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->ptr)
            printf("%d ", temp->linenum);
        printf("\n");
        printtree(p->right);
    }
}


struct tnode *addtree(struct tnode *p, char *w, int linenumber)
{

    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = strcpytree(w);
        p->lines = lalloc();
        p->lines->linenum = linenumber;
        p->lines->ptr = NULL;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        addline(p, linenumber);
    else if (cond < 0)
        p->left = addtree(p->left, w, linenumber);
    else
        p->right = addtree(p->right, w, linenumber);
    return p;
}

void addline(struct tnode *p, int linenumber)
{
    struct linkedlist *temp;

    temp = p->lines;
    while (temp->ptr != NULL && temp->linenum != linenumber)        //while not pointing to the last linkedlist of this word and current linenumber don't match the one stored
        temp = temp->ptr;                                           //point to the next linked list
    if (temp->linenum != linenumber)                                //if we point to the last linked list (lasted linenumber) then allocate space for linkedlist and update linenumber and latest linkedlist pointer.
    {
        temp->ptr = lalloc();
        temp->ptr->linenum = linenumber;
        temp->ptr->ptr = NULL;
    }
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

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct linkedlist *lalloc(void)
{
    return (struct linkedlist *) malloc(sizeof(struct linkedlist));
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

