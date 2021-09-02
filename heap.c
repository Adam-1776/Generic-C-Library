#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "bst.h"
#include "heap.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <assert.h>

#include "integer.h"

typedef struct bstvode{
void *value;}BSTVODE;

typedef struct SNode{
BSTNODE *data;
struct SNode *next;
struct SNode *prev;
}snode;

typedef struct sstack{
snode *head;
snode *tail;
int size;
}SSTACK;

SSTACK *newSSTACK(){
assert(sizeof(SSTACK)>0);
SSTACK *items = malloc(sizeof(SSTACK));   //Constructor
assert(items != 0);
items->head = 0;
items->tail = 0;
items->size = 0;
return items;}

extern void spush(SSTACK *items,BSTNODE *value){
snode *ptr = malloc(sizeof(snode));
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

extern int sizeSSTACK(SSTACK *items){
return items->size;
}

extern void *spop(SSTACK *items){
 bool quit=true;
 if(items->size==0){printf("Cannot pop.\n"); quit=false;}
 assert(quit==true);
 snode *ftr=items->head;
 snode house=*ftr;
 snode *ptr=items->head->next;
 if(items->size!=1) ptr->prev=0;
 free(items->head);
 items->head=ptr; --items->size;
 return house.data;
}

extern void *speekSSTACK(SSTACK *items){
 bool quit=true;
 if(items->size==0){quit=false;}
 assert(quit==true);
 return items->head->data;
}

extern void freeSSTACK(SSTACK *items){
int i=0;
snode *ptr = items->head;
snode *prt = items->head;
for(i=0;i<items->size;++i){
if(i<items->size-1){prt=ptr->next;}
free(ptr);
ptr=prt;
}items->head=0;items->tail=0;items->size=0; free(items);}

typedef struct Nodem{
BSTNODE *data;
struct Nodem *next;
}nodem;

typedef struct queuem{
nodem *head;
nodem *tail;
int size;
}QUEUEM;

extern QUEUEM *newQUEUEM(){
assert(sizeof(QUEUEM)>0);
QUEUEM *items = malloc(sizeof(QUEUEM));
assert(items != 0);
items->head = 0;
items->tail = 0;
items->size = 0;
return items;}

extern void enqueuem(QUEUEM *items,BSTNODE *value){
nodem *ptf = malloc(sizeof(nodem));
ptf->data=value;
if(items->size==0){
items->head=items->tail=ptf;
items->head->next=items->tail;
items->tail->next=0;
++items->size;}
else{
ptf->next=0;
items->tail->next=ptf;
items->tail=ptf;
++items->size;}}

extern void *dequeuem(QUEUEM *items){
bool quit=true;
 if(items->size==0){return 0; printf("Cannot be dequeue.\n"); quit=false;}
 assert(quit==true);
 nodem *ftr=items->head;
 nodem house=*ftr;
 nodem *ptr=items->head->next;
 free(items->head);
 items->head=ptr; --items->size;
 return house.data;
 }

extern void *peekQUEUEM(QUEUEM *items){
bool quit=true;
if(items->size==0){printf("Cannot peek.\n"); quit=false;}
assert(quit==true);
return items->head->data;}

extern int sizeQUEUEM(QUEUEM *items){return items->size;}

void swapperpo(BSTNODE *a,BSTNODE *b){
//BSTNODE *c=newBSTNODE(getBSTNODEvalue(b));
BSTVODE c; c.value=getBSTNODEvalue(b);
setBSTNODEvalue(b,getBSTNODEvalue(a));
setBSTNODEvalue(a,c.value);
//freeBSTNODE(c,0);
}

extern void freeQUEUEM(QUEUEM *items){
int i=0;
nodem *ptr = items->head;
nodem *prt = items->head;
for(i=0;i<items->size;++i){
if(i<items->size-1){prt=ptr->next;}
free(ptr);
ptr=prt;
}items->head=0;items->tail=0;items->size=0; free(items);}

typedef struct heap{
BST *t;
int size;
bool hip;
bool tip;
QUEUEM *q;
SSTACK *si;
void (*display)(void *v,FILE *fp);
void (*free)(void *v);
int (*compare)(void *a,void *b);
void (*swap)(BSTNODE *a,BSTNODE *b);
}HEAP;

extern HEAP *newHEAP(
void (*d)(void *,FILE *),
int (*c)(void *,void *),
void (*f)(void *)){
assert(sizeof(HEAP)>0);
HEAP *items = malloc(sizeof(HEAP));
assert(items!=0);
items->size = 0;
items->hip=true;
items->tip=true;
items->display = d;
items->free = f;
items->compare = c;
items->t=newBST(d,0,0,f);
items->q=newQUEUEM();
items->si=newSSTACK();
return items;}

void displaySSTACK(SSTACK *items,FILE * hfile, HEAP *h){
printf("|");
snode *ptr = items->head;
int i=0;
for(i=0;i<items->size;++i){
        h->display(getBSTNODEvalue(ptr->data), hfile);
        if(i==items->size-1){break;}
        ptr = ptr->next;
        printf(",");
        }
printf("|");
}

extern void insertHEAP(HEAP *h,void *value){
if(h->size==0){insertBST(h->t,value); ++h->size; enqueuem(h->q,getBSTroot(h->t));}
else{BSTNODE *n=peekQUEUEM(h->q);
if(getBSTNODEleft(n)==NULL){setBSTNODEleft(n,newBSTNODE(value)); setBSTNODEparent(getBSTNODEleft(n),n); enqueuem(h->q,getBSTNODEleft(n));}
else if(getBSTNODEright(n)==NULL){setBSTNODEright(n,newBSTNODE(value)); setBSTNODEparent(getBSTNODEright(n),n); enqueuem(h->q,getBSTNODEright(n));
dequeuem(h->q);}++h->size; setBSTsize(h->t,sizeBST(h->t)+1);}}

extern void *peekHEAP(HEAP *h){
if(h->size!=0){return getBSTNODEvalue(getBSTroot(h->t));}
else{return NULL;}}

extern int sizeHEAP(HEAP *h){return h->size;}

extern void displayHEAPdebug(HEAP *h,FILE *fp){
printf("heap size: %d\n",sizeHEAP(h));
printf("bst size: %d\n", sizeBST(h->t));
displayBSTdebug(h->t,fp);}

extern void displayHEAP(HEAP *h,FILE *fp){displayBST(h->t,fp);}

void Heapifymax(BSTNODE *n, HEAP *h){
if(getBSTNODEleft(n)==NULL && getBSTNODEright(n)==NULL){return;}
if(getBSTNODEleft(n)!=NULL && getBSTNODEright(n)==NULL) {BSTNODE *l=getBSTNODEleft(n);
BSTNODE *codes=n;if(h->compare(getBSTNODEvalue(l),getBSTNODEvalue(n))>0) codes=l;
if(codes!=n){
swapperpo(n,codes);
Heapifymax(codes,h);}}
else if(getBSTNODEright(n)!=NULL && getBSTNODEleft(n)==NULL) {BSTNODE *r=getBSTNODEright(n);
BSTNODE *codes=n;if(h->compare(getBSTNODEvalue(r),getBSTNODEvalue(n))>0) codes=r;
if(codes != n){
swapperpo(n,codes);
Heapifymax(codes,h);}}
else{
BSTNODE *l=getBSTNODEleft(n);
BSTNODE *r=getBSTNODEright(n);
BSTNODE *codes=n;
if(h->compare(getBSTNODEvalue(l),getBSTNODEvalue(n))>0)
{codes=l;} else {codes=n;}
if(h->compare(getBSTNODEvalue(r),getBSTNODEvalue(codes))>0)
{codes=r;}
if(codes != n){
swapperpo(n,codes);
Heapifymax(codes,h);}}}

void Heapifyy(BSTNODE *n, HEAP *h){
while(1){
if(getBSTNODEleft(n)==NULL && getBSTNODEright(n)==NULL){return;}
BSTNODE *l=getBSTNODEleft(n);
BSTNODE *r=getBSTNODEright(n);
BSTNODE *codes=n;
if(h->compare(getBSTNODEvalue(l),getBSTNODEvalue(n))<0)
{codes=l;}
if(h->compare(getBSTNODEvalue(r),getBSTNODEvalue(codes))<0)
{codes=r;}
if(codes==n){break;}
if(codes != n){
swapperpo(n,codes);
n=codes;}}}

void Heapifymin(BSTNODE *n, HEAP *h){
if(getBSTNODEleft(n)==NULL && getBSTNODEright(n)==NULL){
return;}
else if(getBSTNODEleft(n)!=NULL && getBSTNODEright(n)==NULL) {BSTNODE *l=getBSTNODEleft(n);
BSTNODE *codes=n;if(h->compare(getBSTNODEvalue(l),getBSTNODEvalue(n))<0) codes=l;
if(codes!=n){
swapperpo(n,codes);
Heapifymin(codes,h);}}
else if(getBSTNODEright(n)!=NULL && getBSTNODEleft(n)==NULL) {BSTNODE *r=getBSTNODEright(n);
BSTNODE *codes=n;if(h->compare(getBSTNODEvalue(r),getBSTNODEvalue(n))<0) codes=r;
if(codes != n){
swapperpo(n,codes);
Heapifymin(codes,h);}}
else{
BSTNODE *l=getBSTNODEleft(n);
BSTNODE *r=getBSTNODEright(n);
BSTNODE *codes=n;
if(h->compare(getBSTNODEvalue(l),getBSTNODEvalue(codes))<0){codes=l;}
if(h->compare(getBSTNODEvalue(r),getBSTNODEvalue(codes))<0){codes=r;}
if(codes != n){
swapperpo(n,codes);
Heapifymin(codes,h);}}}

extern void buildHEAP(HEAP *h){
if(h->hip==true){freeQUEUEM(h->q); h->hip=false;}
if(h->size<2){return;}
bool ender=true;
SSTACK *bob=newSSTACK();
QUEUEM *lisr=newQUEUEM();
QUEUEM *list=newQUEUEM();
BSTNODE *ptr=getBSTroot(h->t); int yus=0;
BSTNODE *ptm=getBSTroot(h->t); int tob=(h->size/2);
enqueuem(lisr, ptr);
while(sizeQUEUEM(lisr)!=0 || sizeQUEUEM(list)!=0){
while (sizeQUEUEM(lisr)!=0 && ender==true){
ptr=peekQUEUEM(lisr);
if (getBSTNODEleft(ptr)!=NULL) enqueuem(list,getBSTNODEleft(ptr));
if (getBSTNODEright(ptr)!=NULL) enqueuem(list,getBSTNODEright(ptr));
ptr=dequeuem(lisr);
spush(bob,ptr); ++yus;}if(yus==tob){
freeQUEUEM(list);freeQUEUEM(lisr); ender=false; break;}
while (sizeQUEUEM(list)!=0 && ender==true){
ptm=peekQUEUEM(list);
if (getBSTNODEleft(ptm)!=NULL) enqueuem(lisr,getBSTNODEleft(ptm));
if (getBSTNODEright(ptm)!=NULL) enqueuem(lisr,getBSTNODEright(ptm));
ptm=dequeuem(list);
spush(bob,ptm); ++yus;}if(yus==tob){
freeQUEUEM(list);freeQUEUEM(lisr); ender=false; break;}}
if(ender==true){freeQUEUEM(list);freeQUEUEM(lisr);}
while(1){
if(bob->size==0){break;}
Heapifymin(speekSSTACK(bob),h);
spop(bob);}
freeSSTACK(bob);}

extern void freeHEAP(HEAP *h){freeBST(h->t); if(h->hip==true){
freeQUEUEM(h->q); h->hip=false;} freeSSTACK(h->si);free(h);}

extern BSTNODE *halp(HEAP *h){
int i=0;
QUEUEM *lisr=newQUEUEM();
BSTNODE *ptr=getBSTroot(h->t);
BSTNODE *kui=getBSTroot(h->t);
while(1){
kui=ptr; ++i; if(i==h->size){break;}
if(getBSTNODEleft(ptr)!=NULL){enqueuem(lisr,getBSTNODEleft(ptr));}
if(getBSTNODEright(ptr)!=NULL){enqueuem(lisr,getBSTNODEright(ptr));}
ptr=dequeuem(lisr);} freeQUEUEM(lisr); return kui;}

void selectfire(HEAP *h){
int i=0;
QUEUEM *lisr=newQUEUEM();
BSTNODE *ptr=getBSTroot(h->t);
while(1){
spush(h->si,ptr); ++i; if(i==h->size){break;}
if(getBSTNODEleft(ptr)!=NULL){enqueuem(lisr,getBSTNODEleft(ptr));}
if(getBSTNODEright(ptr)!=NULL){enqueuem(lisr,getBSTNODEright(ptr));}
ptr=dequeuem(lisr);} freeQUEUEM(lisr);}

extern void *extractHEAP(HEAP *h){
if(h->size==0){return NULL;}
BSTNODE *n=getBSTroot(h->t);
BSTVODE t; t.value=getBSTNODEvalue(n);
BSTNODE *kik=getBSTroot(h->t);
if(h->tip==true){selectfire(h); kik=spop(h->si); h->tip=false;}
else{kik=spop(h->si);}
swapperpo(kik,n); pruneLeafBST(h->t,kik);
free(kik);
--h->size; if(h->size==0){return t.value;}
Heapifymin(getBSTroot(h->t),h);
return t.value;}






















