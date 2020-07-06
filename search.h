#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stdio.h>
#include <stdlib.h>

#ifndef __GRAPH__
#define __GRAPH__

#define MAXV 7000000 //2600000
#define MAXSTR 2000000
#define INF 0x7fffffffffffffff
typedef int InfoType;
//ÁÚ½Ó¾ØÕó
typedef struct ANode {
    int adjvex; //¶¥µã±àºÅ
    struct ANode* nextarc;
    long long int weight;
} ArcNode; //±ß
typedef struct Vnode {
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
*/

void strcpy_p(char destination[], char source[]);
void strcat_p(char destination[], char source[]);
int strcmp_p(char destination[], char source[]);
char* shortestPath(int u, int v, char algorithm[], char name[]);
void CreateAdj(AdjGraph** G, char name[]);
char* DFS(int u, int v, AdjGraph* G);
int DFS_dg(int u, int v, AdjGraph* G);
char* BFS(int u, int v, AdjGraph* G);
char* Dijkstra(int u, int v, AdjGraph* G);
void Dispath(AdjGraph* G, long long dist[], int path[], char S[], int u, int v);

#endif