#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

/*
Program written by Adam Rizk. The code below is to test
my implementation of sll.c
*/

   static void showItems(SLL *items)
       {
       printf("The items are ");
       displaySLL(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       displaySLLdebug(items,stdout);
       printf(".\n");
       }

   int main()
       {
       SLL *items = newSLL(displayINTEGER,freeINTEGER);
       showItems(items);

       insertSLL(items,0,newINTEGER(3));
       showItems(items);
       INTEGER *j =removeSLL(items,0);
       showItems(items);
       freeINTEGER(j);         //insert at front
       insertSLL(items,sizeSLL(items),newINTEGER(2));      //insert at back
       insertSLL(items,1,newINTEGER(1));                   //insert at middle
       showItems(items);
       insertSLL(items,0,newINTEGER(6));                   //insert at middle
       showItems(items);

       printf("The value ");
       INTEGER *i = removeSLL(items,1);                 //remove from front
       displayINTEGER(i,stdout);
       printf(" was removed.\n");
       freeINTEGER(i);
       showItems(items);


       int x = getINTEGER((INTEGER *) getSLL(items,0));    //get the first item
       printf("The first item is %d.\n",x);
       showItems(items);
       printf("Freeing the list.\n");
       freeSLL(items);
       return 0;
       }
