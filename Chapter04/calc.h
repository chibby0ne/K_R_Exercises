#define MAXOP      100
#define NUMBER       0
/* 4-6 these are new for this exercise*/
#define IDENTIFIER   1
#define ENDSTRING    2
/* 4-6 end of new stuff */
#define TRUE         1
#define FALSE        0
#define MAX_ID_LEN  32
#define MAXVARS     30
#define MAXVAL 100
#define BUFSIZE 100

extern struct varType{
   char name[MAX_ID_LEN];
   double val;
};

int Getop(char s[]);
void push(double val);
double pop(void);
void showTop(void);
void duplicate(void);
void swapItems(void);

/* 4-6 this is new for this program */
/* Changed clearStack(void) to clearStacks(struct varType var[])*/
void clearStacks(struct varType var[]);
void dealWithName(char s[],  struct varType var[]);
void dealWithVar(char s[], struct varType var[]);

