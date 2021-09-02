#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"
#include <stdio.h>
#include <assert.h>

/*
Program written by Adam Rizk. Here, I have
implemented a queue data structure that accepts
generic values. It is built from a single linked
list.
*/

typedef struct Node{
void *data;
struct Node *next;
}node;

typedef struct queue{  //This struct holds all the nodes and is the queue itself.
node *head;
node *tail;
int size;
void (*display)(void *v,FILE *fp);
void (*free)(void *v);
}QUEUE;

extern QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *)){  //constructor
assert(sizeof(QUEUE)>0);
        QUEUE *items = malloc(sizeof(QUEUE));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
}

extern void enqueue(QUEUE *items,void *value){
node *ptr = malloc(sizeof(node));
ptr->data=value;
if(items->size==0){
items->head=items->tail=ptr;
items->head->next=items->tail;
items->tail->next=0;
++items->size;
}

else{
ptr->next=0;
items->tail->next=ptr;
items->tail=ptr;
++items->size;
}
}

extern void *dequeue(QUEUE *items){
bool quit=true;
 if(items->size==0){return 0; printf("Cannot be dequeue.\n"); quit=false;}
 assert(quit==true);
 node *ftr=items->head;
 node house=*ftr;
 node *ptr=items->head->next;
 free(items->head);
 items->head=ptr; --items->size;
 return house.data;
 }

extern void *peekQUEUE(QUEUE *items){
bool quit=true;
 if(items->size==0){printf("Cannot peek.\n"); quit=false;}
 assert(quit==true);
 return items->head->data;
}

extern int sizeQUEUE(QUEUE *items){
return items->size;
}

extern void displayQUEUE(QUEUE *items,FILE * hfile){
printf("<");
node *ptr = items->head;
int i=0;
for(i=0;i<items->size;++i){
        items->display(ptr->data, hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
printf(">");
}

extern void freeQUEUE(QUEUE *items){
int i=0;
node *ptr = items->head;
node *prt;
if(items->free==NULL){
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

extern void displayQUEUEdebug(QUEUE *items,FILE * hfile){
printf("head->{");
if(items->size>0){
    node *ptr = items->head;         //displays the tail seperately for debugging.
int i=0;
for(i=0;i<items->size;++i){
        items->display(ptr->data, hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
}
printf("},tail->{");
if(items->size>0) items->display(items->tail->data, hfile);
printf("}");
}

