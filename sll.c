#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sll.h"
#include <stdio.h>
#include <assert.h>

/*
Program written by Adam Rizk. Here, I have
implemented a single linked list data structure
that accepts generic values.
*/

typedef struct Node{
void *data;              //Node
struct Node *next;
}node;

typedef struct sll{      //This struct holds all the nodes and is the actual list.
node *head;
node *tail;
int size;
void (*display)(void *v,FILE *fp);
void (*free)(void *v);
}SLL;

SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *)){   //Constructor
        assert(sizeof(SLL)>0);
        SLL *items = malloc(sizeof(SLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
        }

void displaySLL(SLL *items,FILE * hfile){
printf("{");
node *ptr = items->head;
int i=0;
for(i=0;i<items->size;++i){
        items->display(ptr->data, hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
printf("}");
}

extern void insertSLL(SLL *items,int index,void *value){
bool quit=true;
if(index>items->size || index<0){printf("Cannot be added.\n"); quit=false;}
assert(quit==true);
node *ptr = malloc(sizeof(node));
ptr->data=value;
int i=0;
if(items->size==0){
items->head=items->tail=ptr;
items->head->next=items->tail;
items->tail->next=0;
++items->size;
}

else if(index==0){
ptr->next=items->head;
items->head=ptr;
++items->size;
}

else if(index==items->size){
items->tail->next=ptr;
items->tail=ptr;
++items->size;
}

else{
node *pre=items->head;
for(i=1;i<index;++i){pre=pre->next;}
ptr->next=pre->next;
pre->next=ptr;
++items->size;
 }
}

extern void *removeSLL(SLL *items,int index){
 bool quit=true;
 if(items->size==0 || index>items->size-1 || index<0){printf("Cannot be removed.\n"); quit=false;}
 assert(quit==true);

 if(index==0){
 node house=*items->head;
 node *ptr=items->head->next;
 free(items->head);
 items->head=ptr;
  --items->size;
 return house.data;
 }

 else if(index==items->size-1){
 node qtr=*items->tail;
 node *ptr=items->head; int i=0;
 for(i=1;i<index;++i){ptr=ptr->next;}
 free(items->tail);
 items->tail=ptr;
 --items->size;
 return qtr.data;
 }

 else {
 node *ptr=items->head; int i=0;
 for(i=1;i<index;++i){ptr=ptr->next;}
 node htr=*ptr->next;
 node *pqq=ptr->next;
 ptr->next=ptr->next->next;
 --items->size; free(pqq);
 return htr.data;
 }
}

extern void *getSLL(SLL *items,int index){
 bool quit=true;
 if(index>items->size-1 || index<0){printf("Cannot find.\n"); quit=false;}
 assert(quit==true);
 if(index==items->size-1){
      return items->tail->data;
 }

 else{
    node *ptr=items->head; int i=0;
    for(i=0;i<index;++i){ptr=ptr->next;}
      return ptr->data;
 }
}

extern void *setSLL(SLL *items,int index,void *value){
 bool quit=true;
 if(index>items->size || index<0){printf("Cannot change.\n"); quit=false;}
 assert(quit==true);
 if(index==items->size-1){
    node house=*items->tail;
    items->tail->data=value;
    return house.data;

 }
 else if(index==items->size){
    insertSLL(items,items->size,value);
    node *ptr=NULL;
    return ptr;
 }

 else{
    node *ptr=items->head; int i=0;
    for(i=0;i<index;++i){ptr=ptr->next;}
    node house=*ptr;
    ptr->data=value; return house.data;
 }

}

extern int sizeSLL(SLL *items){
return items->size;
}

extern void freeSLL(SLL *items){
int i=0;
node *ptr = items->head;
node *prt;
if(items->free==NULL){   //cannot free the actual values
                             //if free function is not provided.
for(i=0;i<items->size;++i){
    if(i<items->size-1){prt=ptr->next;}
    free(ptr);
    ptr=prt;
}items->head=0;items->tail=0;items->size=0; free(items);}
else{
for(i=0;i<items->size;++i){
    items->free(ptr->data);
    if(i<items->size-1){prt=ptr->next;}
    free(ptr);
    ptr=prt;
}items->head=0;items->tail=0;items->size=0; free(items);}
}

extern void displaySLLdebug(SLL *items,FILE * hfile){
printf("head->{");
node *ptr = items->head;
int i=0;
for(i=0;i<items->size;++i){
        items->display(ptr->data, hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
printf("},tail->{");
if(items->size>0) items->display(items->tail->data, hfile);
printf("}");
}

extern void freeSLL2(SLL *items){
items->head=0;items->tail=0;items->size=0;
}

extern void unionSLL(SLL *recipient,SLL *donor){
if(donor->size==0){return;}     //do nothing if donor has no nodes.
else if(recipient->size==0){
    recipient->head=donor->head;
    recipient->tail=donor->tail;
    recipient->size=donor->size;
    freeSLL2(donor);
}
else{
node *ptr = recipient->tail;
node *qtr = donor->head;
node *ttr = donor->tail;
ptr->next=qtr;
recipient->tail=ttr;
recipient->size=recipient->size+donor->size;
freeSLL2(donor); }
}



