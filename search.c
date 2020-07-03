#include "search.h"
// 部分代码来源于课本
char* shortestPath(int u, int v, char algorithm[], char name[])
{
    AdjGraph* G;
    CreateAdj(&G, name);

    if (!strcmp(algorithm, "DFS")) {
        return DFS(u, v, G);
    } else if (!strcmp(algorithm, "BFS")) {
        return BFS(u, v, G);
    } else if (!strcmp(algorithm, "Dijkstra")) {
        printf("还好吗? u %d  v %d\n", u, v);
        return Dijkstra(u, v, G);
    } else {
        return "找不到算法\n";
    }
}

void CreateAdj(AdjGraph** G, char* name)
{
    int i, j;
    int temp_u, temp_v, temp_w, temp_max;
    char n_list[MAXV] = { 0 };
    ArcNode* p;
    *G = (AdjGraph*)malloc(sizeof(AdjGraph));
    for (i = 0; i < MAXV; i++) {
        (*G)->adjlist[i].firstarc = NULL;
    }

    freopen(name, "r", stdin);
    (*G)->e = 0;
    temp_max = 0;
    while (scanf("%d %d %d", &temp_u, &temp_v, &temp_w) != EOF) {
        (*G)->e++;
        if (temp_u > temp_max || temp_v > temp_max) {
            temp_max = temp_u > temp_v ? temp_u : temp_v;
        }
        n_list[temp_u] = 1;
        n_list[temp_v] = 1;
        p = (ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex = temp_v;
        p->weight = temp_w;
        p->nextarc = (*G)->adjlist[temp_u].firstarc;
        (*G)->adjlist[temp_u].firstarc = p;
    }

    (*G)->maxnode = temp_max;
    (*G)->n = 0;
    for (i = 0; i < MAXV; i++) {
        if (n_list[i] == 1) {
            (*G)->n++;
        }
    }
}

void DestroyAdj(AdjGraph* G)
{
    int i;
    ArcNode *pre, *p;
    for (i = 0; i < G->n; i++) {
        pre = G->adjlist[i].firstarc;
        if (pre != NULL) {
            p = pre->nextarc;
            while (p != NULL) {
                free(pre);
                pre = p;
                p = p->nextarc;
            }
            free(pre);
        }
    }
    free(G);
}

int visited[MAXV] = { 0 };
char output[MAXV] = "?";
int weights = 0;

int DFS_dg(int u, int v, AdjGraph* G)
{
    ArcNode* p;
    char temp[200];
    int flag = 0;
    visited[u] = 1;
    p = G->adjlist[u].firstarc;
    sprintf(temp, "%d", u);
    if (u == v) {
        strcat(output, temp);
        return 1;
    }
    while (p != NULL) {
        if (visited[p->adjvex] == 0) {
            weights += p->weight;
            flag = DFS_dg(p->adjvex, v, G);
            if (flag == 1) {
                strcat(temp, " -> ");
                strcat(temp, output);
                strcpy(output, temp);
                return 1;
            }
            weights -= p->weight;
        }
        p = p->nextarc;
    }
    visited[u] = 0;
    return 0;
}

char* DFS(int u, int v, AdjGraph* G)
{
    DFS_dg(u, v, G);
    return output;
}

void DispAdj(AdjGraph* G)
{
    int i;
    ArcNode* p;
    for (i = 0; i < G->n; i++) {
        if (i < 12180 && i > 12160 || i < 9330 && i > 9100) {
            p = G->adjlist[i].firstarc;
            printf("%3d : ", i);
            while (p != NULL) {
                printf("%3d[%d]->", p->adjvex, p->weight);
                p = p->nextarc;
            }
            printf("NULL\n");
        }
    }
}

char* BFS(int u, int v, AdjGraph* G)
{
    int i;
    bool break_flag = false;
    ArcNode* p;
    SqQueue* qu;
    Box temp, ptr;
    char token[2000];
    InitQueue(&qu);
    visited[u] = 1;
    temp.val = u;
    temp.pre = -1;
    temp.wei = 0;
    enQueue(qu, temp);
    while (!QueueEmpty(qu)) {
        deQueue(qu, &ptr);
        visited[ptr.val] = 1;
        //printf("出队节点:%d  父节点位置:%d  weights:%d\n", ptr.val, ptr.pre, ptr.wei);
        if (ptr.val == v) {
            weights = ptr.wei;
            //printf("%d %d\n", ptr.wei, p->weight);
            sprintf(output, "%d", v);
            break;
        }
        p = G->adjlist[ptr.val].firstarc;
        while (p != NULL) {
            if (visited[p->adjvex] == 0 || p->adjvex == v) {
                temp.val = p->adjvex;
                temp.pre = qu->front;
                temp.wei = ptr.wei + p->weight;
                //printf("进队节点:%d  父节点:%d  weights:%d\n", temp.val, ptr.val, temp.wei);
                enQueue(qu, temp);
            }
            p = p->nextarc;
        }
    }
    ptr = qu->data[ptr.pre];
    while (ptr.pre != -1) {
        sprintf(token, "%d", ptr.val);
        strcat(token, " -> ");
        strcat(token, output);
        strcpy(output, token);
        ptr = qu->data[ptr.pre];
    }
    sprintf(token, "%d", ptr.val);
    strcat(token, " -> ");
    strcat(token, output);
    strcpy(output, token);
    return output;
}

//Dijkstra算法


char* Dijkstra(int u, int v, AdjGraph* G)
{

    int *distance, *parent;
    distance = (int *)calloc(G->maxnode, sizeof(int));
    parent = (int *)calloc(G->maxnode, sizeof(int));
    //int visited[MAXV];
    int MINdis, i, j, k;
    ArcNode* ptr;
    ptr = G->adjlist[u].firstarc;
    for (i = 0; i < G->maxnode; i++) {
        /*if (ptr != NULL) {
            distance[ptr->adjvex] = ptr->weight;
            ptr = ptr->nextarc;
            if (ptr->weight < INF) {
                parent[ptr->adjvex] = u;
            } else {
                parent[ptr->adjvex] = -1;
            }
        }*/
        //distance[i] = g.edges[u][i];
        distance[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }
    while (ptr != NULL) {
        distance[ptr->adjvex] = ptr->weight;
        if (ptr->weight < INF) {
            parent[ptr->adjvex] = u;
        } else {
            parent[ptr->adjvex] = -1;
        }
        ptr = ptr->nextarc;
    }

    visited[u] = 1;
    parent[u] = 0;
    for (i = 0; i < G->n; i++) {
        MINdis = INF;
        for (j = 0; j < G->maxnode; j++) {
            if (visited[j] == 0 && distance[j] < MINdis) {
                k = j;
                MINdis = distance[j];
            }
        }
        visited[k] = 1;
        for (j = 0; j < G->maxnode; j++) {
            if (visited[j] == 0) {
                ptr = G->adjlist[k].firstarc;
                while (ptr != NULL && ptr->adjvex != j) {
                    ptr = ptr->nextarc;
                }
                if (ptr == NULL) {
                    continue;
                }
                if (/*g.edges[k][j]*/ ptr->weight < INF && distance[k] + ptr->weight /*g.edges[k][j]*/ < distance[j]) {
                    distance[j] = distance[k] + /*g.edges[k][j]*/ ptr->weight;
                    parent[j] = k;
                }
            }
        }
    }
    Dispath(G, distance, parent, visited, u, v);
    return output;
}

void Dispath(AdjGraph* G, int dist[], int path[], int S[], int u, int v)
{
    int i, j, k;
    int apath[MAXV], d;
    i = v;    printf("还好吗? i %d\n", i);
    if (S[i] == 1 && i != u) {
        printf("从顶点%d到顶点%d的路径长度为:%d\t路径为:", u, i, dist[i]);
        d = 0;
        apath[d] = i;
        k = path[i];
        if (k == -1) {
            printf("无路径\n");
        } else {
            while (k != u) {
                d++;
                apath[d] = k;
                k = path[k];
            }
            d++;
            apath[d] = u;
            printf("%d", apath[d]);
            for (j = d - 1; j >= 0; j--) {
                printf(",%d", apath[j]);
            }
            printf("\n");
        }
    }
}

int strcmp(char* destination, char* source)
{
    int i = 0;
    while (1) {
        if (destination[i] == '\0' && source[i] == '\0') {
            return 0;
        }
        if (destination[i] > source[i]) {
            return 1;
        } else if (destination[i] < source[i]) {
            return -1;
        }
        i++;
    }
}

void strcat(char destination[], char source[])
{
    int i = 0, j = 0;
    while (destination[i] != '\0') {
        i++;
    }
    while (source[j] != '\0') {
        destination[i + j] = source[j];
        j++;
    }
    destination[i + j] = '\0';
}

void strcpy(char destination[], char source[])
{
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

void InitQueue(SqQueue** q)
{
    *q = (SqQueue*)malloc(sizeof(SqQueue));
    (*q)->front = (*q)->rear = -1;
}

void DestroyQueue(SqQueue* q)
{
    free(q);
}

bool QueueEmpty(SqQueue* q)
{
    return (q->front == q->rear);
}

bool enQueue(SqQueue* q, ElemType e)
{
    if (q->rear == MAXSIZE - 1) {
        return false;
    }
    q->rear++;
    q->data[q->rear] = e;
    return true;
}

bool deQueue(SqQueue* q, ElemType* e)
{
    int i, min = INF, j;
    ElemType temp;
    if (q->front == q->rear) {
        return false;
    }
    for (i = q->rear; i > q->front; i--) {
        if (q->data[i].wei < min) {
            j = i;
            min = q->data[i].wei;
        }
    }
    if (q->data[q->front + 1].wei > min) {
        temp = q->data[j];
        q->data[j] = q->data[q->front + 1];
        q->data[q->front + 1] = temp;
    }
    q->front++;
    *e = q->data[q->front];
    return true;
}