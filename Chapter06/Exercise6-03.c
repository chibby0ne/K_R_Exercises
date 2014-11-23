/*Write a cross-referencer that prints a list of all words in a document and for each word a
list of the line numbers on which it occurs. Remove noise words like "the", "and", and so on */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

struct node {
    char *word;
    int count;
    struct node *left;
    struct node *right;
};

void PrintWords(struct node *p);
struct node *addnode(struct node *p, char *w);
struct node *talloc(void);
char *strdupl(char *str);


int main(int argc, char *argv[])
{
    FILE *fp;
    char filename[MAX];
    struct node *root;
    char word[MAX];
    int linenumber;
    int i;

    char string[MAX];
//    ///handle the CL arguments e.g file name
//
//    if (--argc && *argv[1] == '-')
//        strcpy(filename, (argv[1]+1));
//    else
//    {
//        printf("Error: Not valid format of filename\n");
//        return -2;
//    }


    ///main routine

    char name[MAX];
    char lastname[MAX];
    char funnyname[MAX];
    int a,b,c;

    fp = fopen(filename, "r");        //test.txt in read mode

//    fp = fopen("D:/test1.txt", "rw");
//    fprintf(fp, "%s", "Antonio Gutierrez");
////    rewind(fp);
//    a = fscanf(fp, "%s", name);
//    b = fscanf(fp, "%s", lastname);
//    c = fscanf(fp, "%s", funnyname);
//    fclose(fp);
//    printf("Your name is %s=%d %s=%d %s=%d\n", name, a, lastname, b, funnyname, c);
//    getchar();
//    return 0;
//}

    fp = fopen("D:/test.txt", "r");
    if (fp == NULL)         //error opening file
    {
        printf("Error: Couldn't open file\n");
        return -1;
    }
    else
    {
        linenumber = 1;
        root = NULL;
        for (i = 0; fscanf(fp, "%s\n", word) != EOF; i++)
        {
            root = addnode(root, word);
        }
        PrintWords(root);
        fclose(fp);
    }
    getchar();
    return 0;
}


void PrintWords(struct node *p)
{
    if (p != NULL)
    {
        PrintWords(p->left);
        printf("%s %d\n", p->word, p->count);
        PrintWords(p->right);
    }
}


///adds node to binary tree. checks whether word is already in tree and increments it.
///if not it creates a node to the left node or right node of the current root depeding on the word
struct node *addnode(struct node *p, char *w)
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
        p->left = addnode(p->left, w);
    else
        p->right = addnode(p->right, w);
    return p;
}


///copy word scanned to place of word in struct node
char *strdupl(char *str)
{
    char *point_word;
    point_word = (char *) malloc(strlen(str)+1);
    if (point_word != NULL)
        strcpy(point_word, str);
    return point_word;
}

///allocate space for struct node
struct node *talloc(void)
{
    return (struct node *) malloc(sizeof(struct node));
}
