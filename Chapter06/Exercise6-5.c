/* Write a fucnion undef that will remove a name and definition from the table maintained by lookup and install */

//not erasing defn for other than first word!!! :@
//check how to use gdb in codeblocks


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct nlist {              //table entry
    struct nlist *next;     //next entry in chain
    char *name;             //defined name
    char *defn;             //replacement text
};

#define HASHSIZE 101
#define MAXWORD 1000

static struct nlist *hashtab[HASHSIZE];


struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
unsigned int hash(char *s);
struct nlist *undef(char *s);
char *strdupl(char *);


int main(int argc, char **argv)
{
    struct nlist *list_pointer;
    struct nlist *list_pointer_lookup;
    struct nlist *list_pointer_undf_bad;
    struct nlist *list_pointer_undf;
    char name[MAXWORD];
    char defn[MAXWORD];

    struct nlist *list_pointer1;
    struct nlist *list_pointer_lookup1;
    struct nlist *list_pointer_undf_bad1;
    struct nlist *list_pointer_undf1;
    char name1[MAXWORD];
    char defn1[MAXWORD];


    struct nlist *list_pointer2;
    struct nlist *list_pointer_lookup2;
    struct nlist *list_pointer_undf_bad2;
    struct nlist *list_pointer_undf2;
    char name2[MAXWORD];
    char defn2[MAXWORD];


    scanf("%s\n", name);
    scanf("%s\n", defn);

    scanf("%s\n", name1);
    scanf("%s\n", defn1);


    scanf("%s\n", name2);
    scanf("%s\n", defn2);
    printf("You placed: %s with replacemente text: %s\n", name, defn);
    printf("You placed: %s with replacemente text: %s\n", name1, defn1);
    printf("You placed: %s with replacemente text: %s\n", name2, defn2);
    list_pointer = install(name, defn);
    printf("first word installed in list pointer: %p\n", list_pointer);
    list_pointer1 = install(name1, defn1);
    printf("second word installed in list pointer: %p\n", list_pointer1);
    list_pointer2 = install(name2, defn2);
    printf("third word installed in list pointer: %p\n", list_pointer2);
    list_pointer_lookup = lookup(name);
    list_pointer_lookup1 = lookup(name1);
    list_pointer_lookup2 = lookup(name2);
    if (list_pointer == list_pointer_lookup)
        printf("first word found\n");
    else
    {
        printf("word not found. ending program\n");
        return -1;
    }
    if (list_pointer1 == list_pointer_lookup1)
        printf("second word found\n");
    else
    {
        printf("word not found. ending program\n");
        return -1;
    }
    if (list_pointer2 == list_pointer_lookup2)
        printf("third word found\n");
    else
    {
        printf("word not found. ending program\n");
        return -1;
    }
    printf("address of name of first word: %p\n", &list_pointer->name);
    printf("deferefenced address of name of first word: %s\n", list_pointer->name);
    printf("address of name of second word: %p\n", &list_pointer1->name);
    printf("dereferenced address of name of second word: %s\n", list_pointer1->name);
    printf("address of name of third word: %p\n", &list_pointer2->name);
    printf("deferefenced address of name of third word: %s\n", list_pointer2->name);
    printf("address of defn of first word: %p\n", &list_pointer->defn);
    printf("dereferenced address of defn of first word: %s\n", list_pointer->defn);
    printf("address of defn of second word: %p\n", &list_pointer1->defn);
    printf("dereferenced address of defn of second word: %s\n", list_pointer1->defn);
    printf("address of defn of third word: %p\n", &list_pointer2->defn);
    printf("dereferenced address of defn of third word: %s\n", list_pointer2->defn);

    printf("first test is with not the correct word\n");
    list_pointer_undf_bad = undef("funny");
    list_pointer_undf_bad1 = undef("funny");
    list_pointer_undf_bad2 = undef("funny");
    printf("pointer when trying to undef word that doesn't exist: %p\n", list_pointer_undf_bad);
    printf("pointer when trying to undef word that doesn't exist: %p\n", list_pointer_undf_bad1);
    printf("pointer when trying to undef word that doesn't exist: %p\n", list_pointer_undf_bad2);
    list_pointer_undf = undef(name);
    list_pointer_undf1 = undef(name1);
    list_pointer_undf2 = undef(name2);
    printf("pointer to free space: %p\n", list_pointer_undf);
    printf("pointer to free space: %p\n", list_pointer_undf1);
    printf("pointer to free space: %p\n", list_pointer_undf2);

    printf("address of name of first word: %p\n", &list_pointer->name);
    printf("deferefenced address of name of first word: %s\n", list_pointer->name);
    printf("address of name of second word: %p\n", &list_pointer1->name);
    printf("dereferenced address of name of second word: %s\n", list_pointer1->name);
    printf("address of name of third word: %p\n", &list_pointer2->name);
    printf("deferefenced address of name of third word: %s\n", list_pointer2->name);
    printf("address of defn of first word: %p\n", &list_pointer->defn);
    printf("dereferenced address of defn of first word: %s\n", list_pointer->defn);
    printf("address of defn of second word: %p\n", &list_pointer1->defn);
    printf("dereferenced address of defn of second word: %s\n", list_pointer1->defn);
    printf("address of defn of third word: %p\n", &list_pointer2->defn);
    printf("dereferenced address of defn of third word: %s\n", list_pointer2->defn);

    getchar();
    return 0;

}

///hash: from hash value from string s
unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

///lookup: look for s in hastab
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;          ///found
    return NULL;                ///not found
}


///install: put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL)        ///not found
    {
        np = (struct nlist *) malloc(sizeof(struct nlist));     ///allocate space for table entry
        if (np == NULL || ((np->name = strdup(name)) == NULL))  ///if not enough space then return null
            return NULL;
        hashval = hash(name);           //create hash of name

        printf("name: %s\n", name);
        printf("hasval: %d\n", hashval);
        np->next = hashtab[hashval];
        printf("np->next: %p\n", np->next);
        hashtab[hashval] = np;
        printf("hashtab[hashval]: %p\n", hashtab[hashval]);
    }
    else                                ///already there
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

char *strdupl(char *s)
{
    char *t;
    t = (char *) malloc(sizeof(s) + 1);
    if (t != NULL)
        strcpy(t, s);
    return t;
}

struct nlist *undef(char *name)
{
    struct nlist *np;
    ///find name
    if ((np = lookup(name)) == NULL)    ///if it's not there then return NULL
    {
        return NULL;
    }
    else                                ///if it is, eliminate the space, set block pointer to NULL
    {
        hashtab[hash(name)] = NULL;
        free((void *) np->defn);
        free((void *) np->name);
        free((void *) np);
        return np;
    }
}
