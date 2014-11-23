
#include <stdlib.h>
#include <stdio.h>
#include "calc.h"


/*
The new additions deal with adding variables to the calculator.

  If the identifier is recognised as one of the supported mathematical
  functions then that function from the library is called. If the
  identifier is not one of the supported functions, even if it is a
  valid function from math.h it is ignored.

  This is a class 1 solution as it uses structures which are not
  introduced until Chapter 6. This allows the use of "normal" names for
  variables rather than the suggested single letter though any
  identifier is limited to 31 characters.

  The main changes are:

    1. The introduction of two more define values (IDENTIFIER,
       ENDSTRING) along with associated cases in the switch statement.
    2. Getop has also been changed to deal with reading in alphabetical
       characters and coping with the '=' sign.
    3. A structure to hold the variable name and value.
    4. Another case in the switch statement to deal with the '=' sign.
    5. Altering the clearStack function to clear the array of structs as
       well as the stack.
    6. The '<' operator now prints the last accessed variable.

  Improvements:
  The code could be made class 0 by the use of "parallel" arrays for the
  names and values rather than a struct but this would be messy and is
  the situation that structs were made for.
  The use of a binary tree together with dynamically allocated memory
  would allow the arbitrary limit of 30 variables to be avoided. This
  would still be a class 1 solution.

  This is exercise 4-6 from Kernighan & Ritchie, page 79.
*/

/* 4-6 this is new for this program */
struct varType{
   char name[MAX_ID_LEN];
   double val;
};
/* 4-6 End of new stuff */

int pos = 0;
struct varType last;

/* 4-6 End of new stuff */

int main(void)
{
   int type;
   double op2;
   char s[MAXOP];
   struct varType var[MAXVARS];

   /* Use the new function here */
   clearStacks(var);

   while((type = Getop(s)) != EOF)
   {
      switch(type)
      {
      case NUMBER:
         push(atof(s));
         break;
      case IDENTIFIER:
         dealWithName(s, var);
         break;
      case '+':
         push(pop() + pop());
         break;
      case '*':
         push(pop() * pop());
         break;
      case '-':
         op2 = pop();
         push(pop()- op2);
         break;
      case '/':
         op2 = pop();
         if(op2)
            push(pop() / op2);
         else
            printf("\nError: division by zero!");
         break;
      case '%':
         op2 = pop();
         if(op2)
            push(fmod(pop(), op2));
         else
            printf("\nError: division by zero!");
         break;
      case '?':
         showTop();
         break;
      case '#':
         duplicate();
         break;
      case '~':
         swapItems();
         break;
      case '!':
         clearStacks(var);
         break;
      case '\n':
         printf("\n\t%.8g\n", pop());
         break;
         /* 4-6 this is new for this program */
      case ENDSTRING:
         break;
      case '=':
         pop();
         var[pos].val = pop();
         last.val = var[pos].val;
         push(last.val);
         break;
      case '<':
         printf("The last variable used was: %s (value == %g)\n",
                                            last.name, last.val);
         break;
         /* 4-6 End of new stuff */
      default:
         printf("\nError: unknown command %s.\n", s);
         break;
      }
   }
   return EXIT_SUCCESS;
}

