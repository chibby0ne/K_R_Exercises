#include <stdio.h>
#include "calc.h"

int sp = 0;          /* Next free stack position. */
double val[MAXVAL];  /* value stack. */

/* push: push f onto stack. */
void push(double f)
{
   if(sp < MAXVAL)
      val[sp++] = f;
   else
      printf("\nError: stack full can't push %g\n", f);
}

/*pop: pop and return top value from stack.*/
double pop(void)
{
   if(sp > 0)
   {
      return val[--sp];
   }
   else
   {
      printf("\nError: stack empty\n");
      return 0.0;
   }
}

void showTop(void)
{
   if(sp > 0)
      printf("Top of stack contains: %8g\n", val[sp-1]);
   else
      printf("The stack is empty!\n");
}

/*
Alternatively:
void showTop(void)
{
double item = pop();
printf("Top of stack contains: %8g\n", item);
push(item);
}
*/

void duplicate(void)
{
   double temp = pop();

   push(temp);
   push(temp);
}

void swapItems(void)
{
   double item1 = pop();
   double item2 = pop();

   push(item1);
   push(item2);
}

/* 4-6 this is new for this program */
/* Altered to clear both the main stack and that of the variable
structure */
void clearStacks(struct varType var[])
{
   int i;

   /* Clear the main stack by setting the pointer to the bottom. */
   sp = 0;

   /* Clear the variables by setting the initial element of each name
   to the terminating character. */
   for( i = 0; i < MAXVARS; ++i)
   {
      var[i].name[0] = '\0';
      var[i].val = 0.0;
   }
}

/* a string/name may be either a maths function or a variable */

