#include <stdio.h>
#include "calc.h"

int buf[BUFSIZE];
int bufp = 0;

/* Getch: get a ( possibly pushed back) character. */
int getch(void)
{
   return (bufp > 0) ? buf[--bufp]: getchar();
}

/* unGetch: push character back on input. */
void unGetch(int c)
{
   if(bufp >= BUFSIZE)
      printf("\nUnGetch: too many characters\n");
   else
      buf[bufp++] = c;
}

