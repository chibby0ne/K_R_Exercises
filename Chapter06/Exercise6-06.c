#include <stdio.h>
#include <ctype.h>
#include <strings.h>
#include <stdlib.h>

#define MAXELEMENTS 100
#define MAXLINE 100

///structures prototypes

struct define {
    char *name;
    char *repl;
};

///function prototypes

int IsBlank(char *s);
void StringCopyNoBlanks(char *s, char *t);
int getfield(char *s, char *beg, char *end);

///external variables

struct define *hashtab[MAXELEMENTS];

int main(int argc, char *argv[])
{
    char line[MAXLINE];
    int char_num = getline(line, MAXLINE);

    ///better do and array of pointer

    #define POINTERS 6
    #define NUM_FIELDS 3

    char *beg_end[POINTERS];
    int spaces_to_allocate[NUM_FIELDS];
    char *fields[NUM_FIELDS];
    int i, j;

    for (i=0, j=0; i < NUM_FIELDS; i++, j++)
        spaces_to_allocate[i] = getfield(line, beg_end[j], beg_end[j+1]);

        space_word = getfield(line, beg_word, end_word);
        space_defn = getfield(line, beg_defn, end_defn);

    for (i=0; i < NUM_FIELDS ; i++)
        fields[i] = (char *)malloc(spaces_to_allocate[i] + 1);

    word = (char *)malloc(space_word + 1);
    defn = (char *)malloc(space_defn + 1);

    for (i=0, j=0; beg_end[j] < beg_end[j+1]; i++, j++)
        for ()
            fields[i] = (beg_end+j)+k


    for (; beg_def <= end_def; beg_def++)
        strcpy(def, beg_def);

    for (; beg_def <= end_def; beg_def++)
        strcpy(def, beg_def);

    for (; beg_def <= end_def; beg_def++)
        strcpy(def, beg_def);

}

int IsBlank(char *s)
{
    return (*s == ' ' || *s == '\t' || *s == '\n') ? 1 : 0;
}

char *SplitWords(char *line)
{
    char *temp;
    char *beg, *end;
    while (*line != NULL)


}


void StringCopyNoBlanks(char *s, char *t)
{
    for (; !IsBlank(s) && (*t = *s) != '\0'; s++, t++)
            ;
}

struct define *install(char *name, char *repl)
{
    struct define *np;
    unsigned int hashval;

    if ((np = lookup(name))  == NULL)       //doesn't exist in list
    {
        np = ((struct define *) malloc(struct define);
        if (np == NULL || (np->name = strdup(name)) == NULL)     //if there's no space available in heap
            return NULL;
        hashval = hash(name);
        hashtab[hashval] = np;              //list element holds address of struct (definition pair)
        if ((np->repl = strdup(repl)) == NULL)
            return NULL;
        return np;
    }
}


struct define *lookup(char *name)
{
    struct define *np;
    unsigned int hashval;


    for ( ;np!=NULL; )


}


int getfield(char *s, char *beg, char *end)
{
    char *beg;
    char *end;
    int i;
    for (i=0; isspace(*s); s++, i++)
        ;
    beg = s;
    for (; !isspace(*s); *s++, i++)
        ;
    end = s - 1;
    return i;
}



//HOW TO SPLIT LINE IN WORDS??
///skips blanks
///copy char from source to target until blank
///detect the space
///end target here with \0
