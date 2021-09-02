#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dll.h"
#include <stdio.h>
#include <assert.h>

/*
Program written by Adam Rizk. Here, I
have implemented a double linked list that
accepts generic values.
*/

typedef struct Node{
void *data;
struct Node *next;
struct Node *prev;
}node;

typedef struct dll{  //This struct holds all of my nodes and is the actual list.
node *head;
node *tail;
int size;
void (*display)(void *v,FILE *fp);
void (*free)(void *v);
}DLL;

DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)){  //constructor
assert(sizeof(DLL)>0);
DLL *items = malloc(sizeof(DLL));
assert(items != 0);
items->head = 0;
items->tail = 0;
items->size = 0;
items->display = d;
items->free = f;
return items;
}

void displayDLL(DLL *items,FILE * hfile){
printf("{{");
node *ptr = items->head;
int i=0;
for(i=0;i<items->size;++i){
        items->display(ptr->data, hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
printf("}}");
}

extern void insertDLL(DLL *items,int index,void *value){
bool quit=true;
if(index>items->size || index<0){printf("Cannot be added.\n"); quit=false;}
assert(quit==true);
node *ptr = malloc(sizeof(node));
ptr->data=value;
int i=0;
if(items->size==0){
items->head=items->tail=ptr;
items->head->next=items->tail;
items->tail->prev=items->head;
items->head->prev=0;
items->tail->next=0;
++items->size;
}

else if(index==0){
ptr->next=items->head;
items->head->prev=ptr;
ptr->prev=0;
items->head=ptr;
++items->size;
}

else if(index==items->size){
items->tail->next=ptr;
ptr->prev=items->tail;
ptr->next=0;
items->tail=ptr;
++items->size;
}

else if(index<(items->size/2)){
node *pre=items->head;
for(i=1;i<index;++i){pre=pre->next;}
ptr->next=pre->next;
ptr->prev=pre;
pre->next->prev=ptr;
pre->next=ptr;
++items->size;
 }

else{
node *pre=items->tail;
for(i=0;i<items->size-index;++i){pre=pre->prev;}
ptr->next=pre->next;
ptr->prev=pre;
pre->next->prev=ptr;
pre->next=ptr;
++items->size;
 }
}

extern void displayDLLdebug(DLL *items,FILE * hfile){
printf("head->");
if(items->size>0) displayDLL(items,stdout);
else{printf("{{}}");}
printf(",tail->{{");
if(items->size>0) items->display(items->tail->data, hfile);
printf("}}");

}

extern int sizeDLL(DLL *items){
return items->size;
}

extern void *removeDLL(DLL *items,int index){

 bool quit=true;
 if(items->size==0 || index>items->size-1 || index<0){printf("Cannot be removed.\n"); quit=false;}
 assert(quit==true);

 if(index==0){
 node house=*items->head;
 node *ptr=items->head->next;
 if(items->size!=1) ptr->prev=0;
 free(items->head);
 items->head=ptr;
  --items->size;
 return house.data;
 }

 else if(index==items->size-1){
 node house=*items->tail;
 node *ptr=items->tail->prev;
 ptr->next=0;
 free(items->tail);
 items->tail=ptr;
  --items->size;
 return house.data;
 }

 else if(index<(items->size/2)){
 node *ptr=items->head; int i=0;
 for(i=1;i<index;++i){ptr=ptr->next;}
 node *htr=ptr->next;
 ptr->next=ptr->next->next;
 ptr->next->prev=ptr;
 node house=*htr;
 free(htr);
 --items->size;
 return house.data;
 }

 else{
 node *ptr=items->tail; int i=0;
 for(i=0;i<items->size-index;++i){ptr=ptr->prev;}
 node *htr=ptr->next;
 ptr->next=ptr->next->next;
 ptr->next->prev=ptr;
 node house=*htr;
 free(htr);
 --items->size;
 return house.data;
 }

}

extern void *getDLL(DLL *items,int index){
 bool quit=true;
 if(index>items->size-1 || index<0){printf("Cannot find.\n"); quit=false;}
 assert(quit==true);
 if(index==items->size-1){
      return items->tail->data;
 }

 else if(index<(items->size/2)){
    node *ptr=items->head; int i=0;
    for(i=0;i<index;++i){ptr=ptr->next;}
      return ptr->data;
 }
 else{
    node *ptr=items->tail; int i=0;
    for(i=1;i<items->size-index;++i){ptr=ptr->prev;}
      return ptr->data;
 }
}

extern void *setDLL(DLL *items,int index,void *value){
 bool quit=true;
 if(index>items->size || index<0){printf("Cannot change.\n"); quit=false;}
 assert(quit==true);
 if(index==items->size-1){ node house=*items->tail;
    items->tail->data=value; return house.data;
 }
 else if(index==items->size){
    insertDLL(items,items->size,value);
    node *ptr=NULL;
    return ptr;
 }

 else if(index<(items->size/2)){
    node *ptr=items->head; int i=0;
    for(i=0;i<index;++i){ptr=ptr->next;}
    node house=*ptr;
    ptr->data=value; return house.data;
 }

 else{
    node *ptr=items->tail; int i=0;
    for(i=1;i<items->size-index;++i){ptr=ptr->prev;}
    node house=*ptr;
    ptr->data=value; return house.data;
 }
}

extern void freeDLL(DLL *items){
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

extern void freeDLL2(DLL *items){
items->head=0;items->tail=0;items->size=0;
}

extern void unionDLL(DLL *recipient,DLL *donor){
if(donor->size==0) return;  //do nothing if the donor doesn't have any nodes.
if(recipient->size==0){     //set the recipient equal to donor if recipient
    recipient->head=donor->head;  //doesn't have any nodes.
    recipient->tail=donor->tail;
    recipient->size=donor->size;
    freeDLL2(donor);
}
else{
node *ptr = recipient->tail;
node *qtr = donor->head;
node *ttr = donor->tail;
ptr->next=qtr;
qtr->prev=ptr;
recipient->tail=ttr;
recipient->size=recipient->size+donor->size;
freeDLL2(donor);
}
}


