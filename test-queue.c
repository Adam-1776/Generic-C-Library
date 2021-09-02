#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "integer.h"

/*
Program written by Adam Rizk. The code below is to test
my implementation of queue.c
*/


static void showItems(QUEUE *items)
       {
       printf("The items are ");
       displayQUEUE(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       displayQUEUEdebug(items,stdout);
       printf(".\n");
       }

int main(){

QUEUE *items = newQUEUE(displayINTEGER,freeINTEGER);
showItems(items);
enqueue(items,newINTEGER(3));
enqueue(items,newINTEGER(4));
enqueue(items,newINTEGER(5));
showItems(items);

printf("The value ");
       INTEGER *i = dequeue(items);
       displayINTEGER(i,stdout);
       printf(" was dequeued.\n");
       freeINTEGER(i);
       showItems(items);
       freeQUEUE(items);
return 0;
}
