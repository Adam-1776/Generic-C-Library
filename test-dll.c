#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "integer.h"
/*
Program written by Adam Rizk. The code below is to test
my implementation of dll.c
*/

static void showItems(DLL *items)
       {
       printf("The items are ");
       displayDLL(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       displayDLLdebug(items,stdout);
       printf(".\n");
       }

int main(){

DLL *items = newDLL(displayINTEGER,freeINTEGER);
showItems(items);
insertDLL(items,0,newINTEGER(3));
showItems(items);
INTEGER *j = removeDLL(items,0);
freeINTEGER(j);
showItems(items);
insertDLL(items,0,newINTEGER(3));
showItems(items);
insertDLL(items,0,newINTEGER(4));
showItems(items);
insertDLL(items,1,newINTEGER(5));
showItems(items);
insertDLL(items,1,newINTEGER(6));
showItems(items);
insertDLL(items,2,newINTEGER(9));
showItems(items);
insertDLL(items,sizeDLL(items),newINTEGER(22));
showItems(items);
insertDLL(items,5,newINTEGER(-4));
showItems(items);
int x = getINTEGER((INTEGER *) getDLL(items,0));    //get the first item
       printf("The first item is %d.\n",x);
       x = getINTEGER((INTEGER *) getDLL(items,1));    //get the first item
       printf("The second item is %d.\n",x);
       x = getINTEGER((INTEGER *) getDLL(items,sizeDLL(items)-1));    //get the first item
       printf("The last item is %d.\n",x);
       x = getINTEGER((INTEGER *) getDLL(items,sizeDLL(items)-2));    //get the first item
       printf("The second last item is %d.\n",x);
       x = getINTEGER((INTEGER *) getDLL(items,sizeDLL(items)-3));    //get the first item
       printf("The third last item is %d.\n",x);
       x = getINTEGER((INTEGER *) getDLL(items,2));    //get the first item
       printf("The third item is %d.\n",x);
j =setDLL(items,0,newINTEGER(54));
freeINTEGER(j);
j =setDLL(items,1,newINTEGER(15));
freeINTEGER(j);
j =setDLL(items,sizeDLL(items)-1,newINTEGER(100));
freeINTEGER(j);
showItems(items);
j =setDLL(items,sizeDLL(items),newINTEGER(101)); showItems(items);
freeINTEGER(j);
j = setDLL(items,sizeDLL(items)-2,newINTEGER(13));showItems(items);
freeINTEGER(j);
j=removeDLL(items,4);
freeINTEGER(j);
showItems(items);
j=removeDLL(items,sizeDLL(items)-1);
freeINTEGER(j);
showItems(items);
j=removeDLL(items,1);
freeINTEGER(j);
showItems(items);
j=removeDLL(items,1);
freeINTEGER(j);
showItems(items);
j=removeDLL(items,1);
freeINTEGER(j);
showItems(items);
j=removeDLL(items,0);
freeINTEGER(j);
showItems(items);
freeDLL(items);
return 0;
}
