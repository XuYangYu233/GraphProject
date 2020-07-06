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
//邻接矩阵
typedef struct ANode {
    int adjvex; //顶点编号
    struct ANode* nextarc;
    long long int weight;
} ArcNode; //边
typedef struct Vnode {
    ArcNode* firstarc;
} VNode; //顶点
typedef struct {
    VNode adjlist[MAXV];
    int n, e, maxnode;
} AdjGraph; //邻接表

#endif

void strcpy_p(char destination[], char source[]); //strcpy
void strcat_p(char destination[], char source[]); //strcat
int strcmp_p(char destination[], char source[]);  //strcmp
char* shortestPath(int u, int v, char algorithm[], char name[]);
void CreateAdj(AdjGraph** G, char name[]);  //建立邻接表
char* DFS(int u, int v, AdjGraph* G);
char* BFS(int u, int v, AdjGraph* G);
char* Dijkstra(int u, int v, AdjGraph* G);
void Dispath(AdjGraph* G, long long dist[], int path[], char S[], int u, int v);

#endif