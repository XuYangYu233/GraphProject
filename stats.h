#ifndef __STATS_H__
#define __STATS_H__

#include <stdio.h>
#include <stdlib.h>

#define M 7000000
#define N 10000000

#ifndef __GRAPH__
#define __GRAPH__

#define MAXV 7000000//2600000
#define MAXSTR 2000000
#define INF 0x7fffffffffffffff
typedef int InfoType;
//ÁÚ½Ó¾ØÕó
typedef struct ANode {
    int adjvex;//¶¥µã±àºÅ
    struct ANode* nextarc;
    long long int weight;
} ArcNode; //±ß
typedef struct Vnode {
    InfoType info;
    ArcNode* firstarc;
} VNode; //¶¥µã
typedef struct {
    VNode adjlist[MAXV];
    int n, e, maxnode;
} AdjGraph; //ÁÚ½Ó±í

#endif
/*
#ifndef __QUEUE__
#define __QUEUE__

#define bool int
#define true 1
#define false 0
#define MAXSIZE 9000000 //2600000
typedef struct {
    int val, pre;
    long long wei;
} Box;
typedef Box ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    long long front;
    long long rear;
} SqQueue; //Ë³Ðò¶Ó

void InitQueue(SqQueue** q);
bool QueueEmpty(SqQueue* q);
bool enQueue(SqQueue* q, ElemType e);
bool deQueue(SqQueue* q, ElemType* e);
bool enPQueue(SqQueue* q, ElemType e);
bool dePQueue(SqQueue* q, ElemType* e);

#endif
*/
float freemanNetworkCentrality(char* name);
float closenessCentrality(char name[], int node);
int numberOfEdges(char name[]);
int numberOfVertices(char name[]);
char *strcpy_m(char *dst, const char *src);

#endif