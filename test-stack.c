#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "integer.h"

/*
Program written by Adam Rizk. Here, I
test my implementation of my stack.c program.
*/

static void showItems(STACK *items)
       {
       printf("The items are ");
       displaySTACK(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       displaySTACKdebug(items,stdout);
       printf(".\n");
       }

int main(){

STACK *items = newSTACK(displayINTEGER,freeINTEGER);
showItems(items);
push(items,newINTEGER(3));
push(items,newINTEGER(4));
push(items,newINTEGER(5));
showItems(items);

printf("The value ");
INTEGER *i = peekSTACK(items);         //remove from front
displayINTEGER(i,stdout);
printf(" was peeked.\n");
showItems(items);
freeSTACK(items);
return 0;
}
