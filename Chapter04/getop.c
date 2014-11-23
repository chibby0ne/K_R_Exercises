#include <stdio.h>
#include <math.h>
#include "calc.h"

extern int pos = 0;
extern struct varType last;
extern struct varType{
   char name[];
    double val;
};


int getch(void);
void unGetch(int);

/* Getop: get next operator or numeric operand. */
int Getop(char s[])
{
   int i = 0;
   int c;
   int next;

   /* Skip whitespace */
   while((s[0] = c = getch()) == ' ' || c == '\t')
   {
      ;
   }
   s[1] = '\0';

   if(isalpha(c))
   {
      i = 0;
      while(isalpha(s[i++] = c ))
      {
         c = getch();
      }
      s[i - 1] = '\0';
      if(c != EOF)
         unGetch(c);
      return IDENTIFIER;
   }

   /* Not a number but may contain a unary minus. */
   if(!isdigit(c) && c != '.' && c != '-')
   {
      /* 4-6 Deal with assigning a variable. */
      if('=' == c && '\n' == (next = getch()))
      {
         unGetch('\0');
         return c;
      }
      if('\0' == c)
         return ENDSTRING;

      return c;
   }

   if(c == '-')
   {
      next = getch();
      if(!isdigit(next) && next != '.')
      {
         return c;
      }
      c = next;
   }
   else
   {
      c = getch();
   }

   while(isdigit(s[++i] = c))
   {
      c = getch();
   }
   if(c == '.')                 /* Collect fraction part. */
   {
      while(isdigit(s[++i] = c = getch()))
         ;
   }
   s[i] = '\0';
   if(c != EOF)
      unGetch(c);
   return NUMBER;
}

void dealWithName(char s[], struct varType var[])
{
   double op2;

   if(!strcmp(s, "sin"))
      push(sin(pop()));
   else if(!strcmp(s, "cos"))
      push(cos(pop()));
   else if (!strcmp(s, "exp"))
      push(exp(pop()));
   else if(!strcmp(s, "pow"))
   {
      op2 = pop();
      push(pow(pop(), op2));
   }
   /* Finally if it isn't one of the supported maths functions we have a
      variable to deal with. */
   else
   {
      dealWithVar(s, var);
   }
}

/* Our identifier is not one of the supported maths function so we have
   to regard it as an identifier. */
void dealWithVar(char s[], struct varType var[])
{
   int i = 0;

   while(var[i].name[0] != '\0' && i < MAXVARS-1)
   {
      if(!strcmp(s, var[i].name))
      {
         strcpy(last.name, s);
                   last.val = var[i].val;
         push(var[i].val);
         pos = i;
         return;
      }
      i++;
   }

   /* variable name not found so add it */
   strcpy(var[i].name, s);
   /* And save it to the last variable */
   strcpy(last.name, s);
   push(var[i].val);
   pos = i;
}
/* 4-6 End of new stuff */


