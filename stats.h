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
//�ڽӾ���
typedef struct ANode {
    int adjvex;//������
    struct ANode* nextarc;
    long long int weight;
} ArcNode; //��
typedef struct Vnode {
    InfoType info;
    ArcNode* firstarc;
} VNode; //����
typedef struct {
    VNode adjlist[MAXV];
    int n, e, maxnode;
} AdjGraph; //�ڽӱ�

#endif

float freemanNetworkCentrality(char* name);         //freeman
float closenessCentrality(char name[], int node);   //closeness
int numberOfEdges(char name[]);                     //edges
int numberOfVertices(char name[]);                  //vertices
char *strcpy_m(char *dst, const char *src);

#endif