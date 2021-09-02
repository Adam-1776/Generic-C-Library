#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#include <stdio.h>
#include <assert.h>

/*
Program written by Adam Rizk. Here, I have
implemented a stack data structure that accepts
generic values. It is built from a double linked
list.
*/

typedef struct Node{  //Node
void *data;
struct Node *next;
struct Node *prev;
}node;

typedef struct stack{ //This struct holds all the nodes.
node *head;
node *tail;
int size;
void (*display)(void *v,FILE *fp);
void (*free)(void *v);
}STACK;

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)){
assert(sizeof(STACK)>0);
STACK *items = malloc(sizeof(STACK));   //Constructor
assert(items != 0);
items->head = 0;
items->tail = 0;
items->size = 0;
items->display = d;
items->free = f;
return items;
}

void displaySTACK(STACK *items,FILE * hfile){
printf("|");
node *ptr = items->head;
int i=0;
for(i=0;i<items->size;++i){
        items->display(ptr->data, hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
printf("|");
}

extern void push(STACK *items,void *value){
node *ptr = malloc(sizeof(node));
ptr->data=value;

if(items->size==0){
items->head=items->tail=ptr;
items->head->next=items->tail;
items->tail->prev=items->head;
items->head->prev=0;
items->tail->next=0;
++items->size;
}

else{
ptr->next=items->head;
items->head->prev=ptr;
ptr->prev=0;
items->head=ptr;
++items->size;
}
}

extern void displaySTACKdebug(STACK *items,FILE * hfile){
printf("head->{{");
if(items->size>0){
    if(items->size>0){
    node *ptr = items->head;
int i=0;
for(i=0;i<items->size;++i){
        items->display(ptr->data, hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
}
}
printf("}},tail->{{");
if(items->size>0) items->display(items->tail->data, hfile);
printf("}}");
}

extern int sizeSTACK(STACK *items){
return items->size;
}

extern void *pop(STACK *items){
 bool quit=true;
 if(items->size==0){printf("Cannot pop.\n"); quit=false;}
 assert(quit==true);
 node *ftr=items->head;
 node house=*ftr;
 node *ptr=items->head->next;
 if(items->size!=1) ptr->prev=0;
 free(items->head);
 items->head=ptr; --items->size;
 return house.data;
}

extern void *peekSTACK(STACK *items){
 bool quit=true;
 if(items->size==0){quit=false;}
 assert(quit==true);
 return items->head->data;
}

extern void freeSTACK(STACK *items){
int i=0;
node *ptr = items->head;
node *prt;
if(items->free==NULL){  //Cannot free data if free function is not provided.
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






