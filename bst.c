#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "bst.h"
#include "queue.h"
#include <stdio.h>
#include <assert.h>

typedef struct bstnode{
void *value;
struct bstnode *left;
struct bstnode *right;
struct bstnode *parent;
}BSTNODE;

typedef struct bst{
BSTNODE *root;
int size;
void (*display)(void *v,FILE *fp);
void (*free)(void *v);
int (*compare)(void *a,void *b);
void (*swap)(BSTNODE *a,BSTNODE *b);
}BST;

typedef struct Nodeq{
BSTNODE *data;
struct Nodeq *next;
}nodeq;

typedef struct queueq{
nodeq *head;
nodeq *tail;
int size;
void (*free)(BSTNODE *v, BST *t);
}QUEUEQ;

void freen(BSTNODE *n, BST *t){
if(n==0){free(n);return;}
if(t->free!=NULL && t->free!=0){t->free(n->value); n->left=0; n->right=0; n->parent=0;}
free(n);}

extern QUEUEQ *newQUEUEQ(void (*f)(BSTNODE *, BST *)){
assert(sizeof(QUEUEQ)>0);
        QUEUEQ *items = malloc(sizeof(QUEUEQ));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->free = f;
        return items;
}

extern void enqueueq(QUEUEQ *items,BSTNODE *value){
nodeq *ptf = malloc(sizeof(nodeq));
ptf->data=value;
if(items->size==0){
items->head=items->tail=ptf;
items->head->next=items->tail;
items->tail->next=0;
++items->size;
}

else{
ptf->next=0;
items->tail->next=ptf;
items->tail=ptf;
++items->size;
}
}

extern void *dequeueq(QUEUEQ *items){
bool quit=true;
 if(items->size==0){return 0; printf("Cannot be dequeue.\n"); quit=false;}
 assert(quit==true);
 nodeq *ftr=items->head;
 nodeq house=*ftr;
 nodeq *ptr=items->head->next;
 free(items->head);
 items->head=ptr; --items->size;
 return house.data;
 }

extern void *peekQUEUEQ(QUEUEQ *items){
bool quit=true;
 if(items->size==0){printf("Cannot peek.\n"); quit=false;}
 assert(quit==true);
 return items->head->data;
}

extern int sizeQUEUEQ(QUEUEQ *items){
return items->size;
}

extern void freeQUEUEQ(QUEUEQ *items){
int i=0;
nodeq *ptr = items->head;
nodeq *prt = items->head;
for(i=0;i<items->size;++i){
if(i<items->size-1){prt=ptr->next;}
free(ptr);
ptr=prt;
}items->head=0;items->tail=0;items->size=0; free(items);}

void swapper2(BSTNODE *a,BSTNODE *b){
BSTNODE c=*b;
b->value=a->value;
b->left=a->left;
b->right=a->right;
b->parent=a->parent;
a->value=c.value;
a->left=c.left;
a->right=c.right;
a->parent=c.parent;
}

void swapper(BSTNODE *a,BSTNODE *b){
BSTNODE c=*b;
b->value=a->value;
a->value=c.value;
}

extern BST *newBST(
void (*d)(void *,FILE *),
int (*c)(void *,void *),
void (*s)(BSTNODE *,BSTNODE *),
void (*f)(void *)){
assert(sizeof(BST)>0);
BST *items = malloc(sizeof(BST));
assert(items!=0);
items->root = 0;
items->size = 0;
items->display = d;
items->free = f;
items->compare = c;
if(s!=0 && s!=NULL){items->swap = s;}
else{items->swap=swapper;}
return items;
}

extern int sizeBST(BST *t){return t->size;}

void autosear(BST *t,BSTNODE *ptr,FILE *fp){
printf("{");
printf("root: "); t->display(ptr->value,fp);
if(ptr->parent!=0){printf(" parent: "); t->display(ptr->parent->value,fp);}
printf(" left: "); if(ptr->left!=0) {t->display(ptr->left->value,fp);}
printf(" right: "); if(ptr->right!=0) {t->display(ptr->right->value,fp);}
printf("}");
if(ptr->left!=0 && ptr->left!=NULL){printf("\n"); autosear(t,ptr->left,fp);}
if(ptr->right!=0 && ptr->right!=NULL){printf("\n"); autosear(t,ptr->right,fp);}
}

bool brackets=true;

void rdias(BST *t,BSTNODE *ptr,FILE *fp){
if(ptr==NULL||ptr==0){return;}
else{if(brackets==false){printf(" ");} printf("["); brackets=false; t->display(ptr->value,fp);}
rdias(t,ptr->left,fp); rdias(t,ptr->right,fp);printf("]");}

extern void displayBST(BST *t,FILE *fp){
if(t->size==0){printf("[]");return;}
BSTNODE *ptr = t->root;
brackets=true;
rdias(t,ptr,fp);
//autosear(t,ptr,fp);
}

extern BSTNODE *newBSTNODE(void *v){
BSTNODE *ptr = malloc(sizeof(BSTNODE));
ptr->value=v;
ptr->left=0;
ptr->right=0;
ptr->parent=0;
return ptr;
}

extern BSTNODE *insertBST(BST *t,void *value){
BSTNODE *ptr = malloc(sizeof(BSTNODE));
ptr->value=value;
ptr->left=0;
ptr->right=0;
ptr->parent=0;
if(t->size==0){t->root=ptr; ++t->size; return ptr;}
BSTNODE *qtr=t->root; int i=1;
while(1){
if(t->compare(qtr->value,value)>0){
if(qtr->left==0){qtr->left=ptr;ptr->parent=qtr;++t->size; return ptr;}
else{qtr=qtr->left;++i;continue;}}
else if(t->compare(qtr->value,value)<0){
if(qtr->right==0){qtr->right=ptr;ptr->parent=qtr;++t->size; return ptr;}
else{qtr=qtr->right;++i;continue;}}
else{return ptr;}
}}

extern void displayBSTdebug(BST *t,FILE *fp){
if(t->size==0){return;}
QUEUEQ *lisr=newQUEUEQ(freen);
QUEUEQ *list=newQUEUEQ(freen);
BSTNODE *ptr=t->root; int yus=0;
BSTNODE *ptm=t->root;
enqueueq(lisr, ptr);
while(sizeQUEUEQ(lisr)!=0 || sizeQUEUEQ(list)!=0){
while (sizeQUEUEQ(lisr)!=0){
ptr=peekQUEUEQ(lisr);
if (ptr->left!=0) enqueueq(list,ptr->left);
if (ptr->right!=0) enqueueq(list,ptr->right);
ptr=dequeueq(lisr);
t->display(ptr->value,fp); ++yus; if(sizeQUEUEQ(lisr)!=0)printf(" ");}if(yus!=t->size)printf("\n"); else{printf("\n");
freeQUEUEQ(list);freeQUEUEQ(lisr); return;}
while (sizeQUEUEQ(list)!=0){
ptm=peekQUEUEQ(list);
if (ptm->left!=0) enqueueq(lisr,ptm->left);
if (ptm->right!=0) enqueueq(lisr,ptm->right);
ptm=dequeueq(list);
t->display(ptm->value,fp); ++yus; if(sizeQUEUEQ(list)!=0)printf(" "); }if(yus!=t->size)printf("\n"); else{printf("\n");
freeQUEUEQ(list);freeQUEUEQ(lisr); return;}} }

int shibe=-1; int bash=-1;

int maxDepth(BSTNODE *node) {
if (node==NULL || node==0){return 0;}
else{int lDepth = maxDepth(node->left);
int rDepth=maxDepth(node->right);
if (lDepth > rDepth) return(lDepth+1);
else return(rDepth+1);}}

int minDepth(BSTNODE *root){
if(root==NULL||root==0){return 0;}
int ldepth=minDepth(root->left);
int rdepth=minDepth(root->right);
//if(ldepth == 0){return 1+rdepth;}
//else if(rdepth == 0){return 1+ldepth;}
if (ldepth < rdepth) return(ldepth+1);
else return(rdepth+1);
}

extern void statisticsBST(BST *t,FILE *fp){
//printf("\n");autosear(t,t->root,stdout);printf("\n");
if(t->size!=0 && t->root->left!=0 && t->root->right!=0){
bash=minDepth(t->root)-1;} else{if(t->size==0)bash=-1;else bash=0;}
shibe=maxDepth(t->root)-1;
fprintf(fp,"Nodes: %d\n",t->size);
fprintf(fp,"Minimum depth: %d\n",bash);
fprintf(fp,"Maximum depth: %d\n",shibe);}

extern BSTNODE *getBSTNODEleft(BSTNODE *n){if(n->left!=0&&n->left!=NULL)return n->left;else{return NULL;}}
extern BSTNODE *getBSTNODEright(BSTNODE *n){if(n->right!=0&&n->right!=NULL)return n->right;else{return NULL;}}
extern BSTNODE *getBSTNODEparent(BSTNODE *n){if(n->parent!=0&&n->parent!=NULL)return n->parent;else{return NULL;}}
extern void *getBSTNODEvalue(BSTNODE *n){return n->value;}
extern void setBSTNODEvalue(BSTNODE *n,void *value){n->value=value;}
extern void setBSTNODEright(BSTNODE *n,BSTNODE *replacement){n->right=replacement; //if(replacement!=NULL&&replacement!=0)replacement->parent=n;
}
extern void setBSTNODEleft(BSTNODE *n,BSTNODE *replacement){n->left=replacement; //if(replacement!=NULL&&replacement!=0)replacement->parent=n;
}
extern void setBSTNODEparent(BSTNODE *n,BSTNODE *replacement){n->parent=replacement;}
extern BSTNODE *getBSTroot(BST *t){return t->root;}
extern void setBSTroot(BST *t,BSTNODE *replacement){t->root=replacement;}
extern void setBSTsize(BST *t,int s){t->size=s;}

extern BSTNODE *findBST(BST *t,void *value){
BSTNODE *qtr=t->root;
while(1){
if(qtr==0||qtr==NULL){return NULL;}
else if(t->compare(qtr->value,value)>0){++shibe; qtr=qtr->left;continue;}
else if(t->compare(qtr->value,value)<0){++shibe; qtr=qtr->right;continue;}
else{return qtr;}}
}

BSTNODE *findsuc(BSTNODE *node){
if(node->left==0){return node;}
else{++shibe;return findsuc(node->left);}}

BSTNODE *findpre(BSTNODE *node){
if(node->right==0){return node;}
else{++shibe;return findpre(node->right);}}

BSTNODE *swapToLeafBST(BST *t,BSTNODE *node){
BSTNODE *qtr=t->root;
if(node->left==0&&node->right==0){
return node;}
else if(node->right!=0){
qtr=findsuc(node->right);
t->swap(node,qtr);}
else if(node->left!=0){
qtr=findpre(node->left);
t->swap(node,qtr);}
return swapToLeafBST(t,qtr);
}

extern void pruneLeafBST(BST *t,BSTNODE *leaf){
BSTNODE *rrr=t->root;
if(leaf==rrr){
if(t->size!=1){return;}
else{t->size=0;t->root=0; return;}}
BSTNODE *qtr=leaf->parent;
if(qtr->left==leaf){qtr->left=0;leaf->parent=0;}
else{qtr->right=0;leaf->parent=0;}
--t->size;
}

void showNode(BST *t,BSTNODE *n){t->display(n->value,stdout);}

extern void freeBSTNODE(BSTNODE *n,void (*fre)(void *)){
if(n==0){free(n);return;}
//printf("freeing this node: "); showNode()
if(fre!=NULL && fre!=0){fre(n->value); n->left=0; n->right=0; n->parent=0;}
free(n);}

extern BSTNODE *deleteBST(BST *t,void *value){
BSTNODE *qtr=findBST(t,value);
if(qtr==NULL||qtr==0){return NULL;}
BSTNODE *kit=swapToLeafBST(t,qtr);
pruneLeafBST(t,kit); return kit;}

extern void freeBST2(BST *t,BSTNODE *ptr){
bool left=false; bool right=false;
BSTNODE *qtr=t->root; BSTNODE *mtr=t->root;
if(qtr==0||qtr==NULL){return;}
if(ptr->left!=0){qtr=ptr->left;left=true;}
if(ptr->right!=0){mtr=ptr->right;right=true;}
//t->display(ptr->value,stdout); printf(" ");
freeBSTNODE(ptr,t->free);
if(left==true){freeBST2(t,qtr);}
if(right==true){freeBST2(t,mtr);}
}

extern void freeBST(BST *t){
if(t->size!=0) freeBST2(t,t->root);
t->root=0; t->size=0;
t->swap=0; t->free=0;
t->compare=0; t->display=0;
free(t); return;}


