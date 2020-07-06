
#ifndef __QUEUE__
#define __QUEUE__

#include <stdio.h>
#include <stdlib.h>

#define bool int
#define true 1
#define false 0
#define MAXSIZE 9000000 //2600000
typedef struct {
    int val;
    long long wei, pre;
} Box;
typedef Box ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    long long front;
    long long rear;  //size
} SqQueue; //Ë³Ðò¶Ó

void InitQueue(SqQueue** q);
bool QueueEmpty(SqQueue* q);
bool enQueue(SqQueue* q, ElemType e);
bool deQueue(SqQueue* q, ElemType* e);
bool enPQueue(SqQueue* q, ElemType e);
bool dePQueue(SqQueue* q, ElemType* e);

#endif