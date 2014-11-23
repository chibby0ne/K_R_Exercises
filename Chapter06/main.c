#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

//struct point
int getline(char s[], int c);

int add(int x, int y);

int mul(int a, int b);

int add1(int x, int y, int *z);

void mul10(int *x, int *y);

void muladd(int *, int *);
void add10(int *, int *);
void add10real(int * , int * );

int div1(int a, int (*op)(int, int));



struct point makepoint(int x, int y);
void makepointp(int x, int y, struct point *p);

struct rect makerect(struct point pt1, struct point pt2);

    struct point {
    int x;
    int y;
};


    struct rect {
    struct point pt1;
    struct point pt2;
};

int main()
{

    int x;
    int y;
    int z;
    int c;
    int option;
    char *p;
    char name[] = "Vane";
    char name2[] = "Tony";
    char name3[] = "Hermaphrodite";
    char sex[MAX];
    x = 10;
    y = 5;
    p = malloc(sizeof(int));
    FILE *fp;
    fp = fopen("D:\\test.txt", "w");
    fprintf(fp, "This is a test\n %s\t%d", "Antonio", 18);
    fclose(fp);

    struct point *ppt1;
    struct point *ppt2;

    ppt1 = malloc(sizeof(struct point));

    struct point pt1;
    struct point pt2;

    struct rect screen;

    pt1 = makepoint(x, y);
    printf("%d, %d\n", pt1.x, pt1.y);


    printf("Now with pointer to struct point\n");
    makepointp(x, y, ppt1);
    printf("%d, %d\n", ppt1->x, ppt1->y);

    pt2 = makepoint(x+y, x*y);
    printf("%d, %d\n", pt2.x, pt2.y);

    screen = makerect(pt1, pt2);
    printf("%d, %d\t %d, %d\n", screen.pt1.x, screen.pt1.y, screen.pt2.x, screen.pt2.y);

    char *sexes[] = {"girl", "boy", "gay"};


    printf("%d + %d = %d\n", x, y, add(x, y));
    add1(x,y,&z);
    printf("%d + %d = %d\n", x, y, z);

    mul10(&x, &y);
    printf("x = %d, y = %d\n", x, y);

    muladd(&x, &y);
    printf("x = %d, y = %d\n", x, y);

    printf("Enter your sex\n");
    getline(sex,MAX);

    if (strcmp(sexes[0],sex) == 0)
        printf("%s\n", name );
    else if(strcmp(sexes[1], sex) == 0)
        printf("%s\n", name2);
    else if (strcmp(sexes[2], sex) == 0)
        printf("%s\n", name3);
    else
        printf("Error\n");


    printf("Enter your option\n");
    *p=getchar();
    if (isdigit(*p))
        option = atoi(p);
    else
    {
        printf("SuperError\n");
        return -1;
    }

    printf("option = %d\n", option);
    double a = 10;
    int b = 18;

    if (option == 1)
        c = div1(a , (int (*)(int , int)) add);
    else
        c = div1(b, (int (*)(int, int)) mul);

    printf("%d\n", c);

    return 0;

}

struct point makepoint(int x, int y)
{
    struct point pt;
    pt.x = x;
    pt.y = y;
    return pt;
}

void makepointp(int x, int y, struct point *p)
{
    p->x = x;
    p->y = y;
}

struct rect makerect(struct point pta, struct point ptb)
{
    struct rect rectangle;
//
//    rectangle.pt1.x = pta.x;
//    rectangle.pt1.y = pta.y;
//    rectangle.pt2.x = ptb.x;
//    rectangle.pt2.y = ptb.y;

    rectangle.pt1 = pta;
    rectangle.pt2 = ptb;
    return rectangle;
}


#define VAR1 2
#define VAR2 3

int div1(int a, int (*op)(int, int))
{

    int x;
    x = (*op)(VAR1, VAR2);
    return a / x;

}


int getline(char s[], int max)
{
    int c, i;
    for (i=0; i<max-1 && (c=getchar())!=EOF && c!='\n'; i++ )
        s[i]=c;
    s[i] = '\0';
    return i;
}


int add(int a, int b)
{
    return a + b;
}

int mul(int a, int b)
{
    return a * b;
}


int add1(int c, int d, int *e)
{
    *e = c + d;
    return 0;
}

void mul10(int *a, int *b)
{
    *a *= 10;        /// x = 100
    *b *= 10;        /// y = 50
}


void muladd(int *a, int *b)
{
    add10(a, b);    /// x = 110 , y = 60
    printf("x = %d\n", *a);
    printf("y = %d\n", *b);

    *a *= 2;        ///x = 220
    *b *= 2;        ///y = 120
}

void add10(int *a, int *b)
{
    printf("First function\n");
    add10real(a, b);
}

void add10real(int *x, int *y)
{
    printf("Second Function\n");
    *x += 10;
    *y += 10;
}


