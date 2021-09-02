#ifndef __SLL_INCLUDED__
#define __SLL_INCLUDED__
#include <stdio.h>
typedef struct sll SLL;
extern SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *));
extern void displaySLL(SLL *items,FILE *);
extern void insertSLL(SLL *items,int index,void *value);
extern void *removeSLL(SLL *items,int index);
extern void *getSLL(SLL *items,int index);
extern void *setSLL(SLL *items,int index,void *value);
extern int sizeSLL(SLL *items);
extern void freeSLL(SLL *items);
extern void displaySLLdebug(SLL *items,FILE *);
extern void unionSLL(SLL *recipient,SLL *donor);
#endif
