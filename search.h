#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stdio.h>
#include <stdlib.h>

#define MAXV 1280000//2600000
#define MAXSTR 2000
#define INF 0x7fffffff
typedef int InfoType;
//ÁÚ½Ó¾ØÕó
typedef struct ANode {
    int adjvex;//¶¥µã±àºÅ
    struct ANode* nextarc;
    int weight;
} ArcNode; //±ß
typedef struct Vnode {
    InfoType info;
    ArcNode* firstarc;
} VNode; //¶¥µã
typedef struct {
    VNode adjlist[MAXV];
    int n, e, maxnode;
} AdjGraph;

#define bool int
#define true 1
#define false 0
#define MAXSIZE 1280000//2600000
typedef struct {
    int val, pre, wei;
} Box;
typedef Box ElemType;
typedef struct {
    ElemType data[MAXSIZE];
    int front, rear;
} SqQueue; //Ë³Ðò¶Ó

void InitQueue(SqQueue** q);
bool QueueEmpty(SqQueue* q);
bool enQueue(SqQueue* q, ElemType e);
bool deQueue(SqQueue* q, ElemType* e);
void strcpy_p(char destination[], char source[]);
void strcat_p(char destination[], char source[]);
int strcmp_p(char destination[], char source[]);
char* shortestPath(int u, int v, char algorithm[], char name[]);
void CreateAdj(AdjGraph** G, char name[]);
char* DFS(int u, int v, AdjGraph* G);
int DFS_dg(int u, int v, AdjGraph* G);
char* BFS(int u, int v, AdjGraph* G);
char* Dijkstra(int u, int v, AdjGraph *G);
void Dispath(AdjGraph* G, int dist[], int path[], int S[], int u, int v);

int visited[MAXV] = { 0 };
char output[MAXV] = "";
int weights = 0;

#endif