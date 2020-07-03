#include "search.h"
// 部分代码来源于课本
char* shortestPath(int u, int v, char algorithm[], char name[])
{
    AdjGraph* G;
    CreateAdj(&G, name);

    if (!strcmp_p(algorithm, "DFS")) {
        return DFS(u, v, G);
    } else if (!strcmp_p(algorithm, "BFS")) {
        return BFS(u, v, G);
    } else if (!strcmp_p(algorithm, "Dijkstra")) {
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

char* DFS(int u, int v, AdjGraph* G)
{
    ArcNode *ptr;
    char tmp_str[MAXV];
    Box *b_stack, trans, *waste, change;
    int pop_out, top = -1, rear = -1, i;
    b_stack = (Box *)calloc(MAXV/2, sizeof(Box));
    waste = (Box *)calloc(MAXV/2, sizeof(Box));
    ptr = G->adjlist[u].firstarc;
    while (ptr != NULL) {
        top++;
        b_stack[top].val = ptr->adjvex;
        b_stack[top].wei = ptr->weight;
        b_stack[top].pre = -1;
        visited[ptr->adjvex] = 1;
        ptr = ptr->nextarc;
    }
    visited[u] = 1;
    while (top >= 0) {
        trans = b_stack[top];
        for (i = 0; i < top; i++) {
            if (b_stack[i].pre == trans.pre && b_stack[i].wei < trans.wei) {
                change = b_stack[i];
                b_stack[i] = trans;
                trans = change;
            }
        }
        top--;
        rear++;
        waste[rear] = trans;
        //printf("出队:%d  父节点:%d  权值:%d\n", trans.val, waste[trans.pre].val, trans.wei);
        if (trans.val == v) {
            sprintf(output, "%d", trans.val);
            weights += trans.wei;
            trans = waste[trans.pre];
            break;
        }
        ptr = G->adjlist[trans.val].firstarc;
        while (ptr != NULL) {
            if (visited[ptr->adjvex] == 0) {
                visited[ptr->adjvex] = 1;
                top++;
                b_stack[top].val = ptr->adjvex;
                b_stack[top].wei = ptr->weight;
                b_stack[top].pre = rear;
            }
            ptr = ptr->nextarc;
        }
    }
    while (trans.pre != -1) {
        weights += trans.wei;
        sprintf(tmp_str, "%d -> ", trans.val);
        strcat_p(tmp_str, output);
        strcpy_p(output, tmp_str);
        trans = waste[trans.pre];
    }
    weights += trans.wei;
    sprintf(tmp_str, "%d -> %d -> ", u, trans.val);
    strcat_p(tmp_str, output);
    strcpy_p(output, tmp_str);

    return output;
}

char* BFS(int u, int v, AdjGraph* G)
{
    int i;
    bool break_flag = false;
    ArcNode* p;
    SqQueue* qu;
    Box temp, ptr;
    char token[MAXSTR];
    InitQueue(&qu);
    visited[u] = 1;
    temp.val = u;
    temp.pre = -1;
    temp.wei = 0;
    enQueue(qu, temp);
    strcpy_p(output, "unreachable");
    while (!QueueEmpty(qu)) {
        deQueue(qu, &ptr);
        visited[ptr.val] = 1;
        //printf("出队节点:%d  父节点位置:%d  weights:%d\n", ptr.val, ptr.pre, ptr.wei);
        if (ptr.val == v) {
            weights = ptr.wei;
            sprintf(output, "%d", v);
            ptr = qu->data[ptr.pre];
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

    while (ptr.pre != -1) {
        sprintf(token, "%d", ptr.val);
        strcat_p(token, " -> ");
        strcat_p(token, output);
        strcpy_p(output, token);
        ptr = qu->data[ptr.pre];
    }
    sprintf(token, "%d", ptr.val);
    strcat_p(token, " -> ");
    strcat_p(token, output);
    strcpy_p(output, token);
    return output;
}

//Dijkstra算法
char* Dijkstra(int u, int v, AdjGraph* G)
{

    int *distance, *parent;
    distance = (int *)calloc(G->maxnode, sizeof(int));
    parent = (int *)calloc(G->maxnode, sizeof(int));
    int MINdis, i, j, k;
    ArcNode* ptr;
    SqQueue *qu;
    Box temp;
    InitQueue(&qu);
    ptr = G->adjlist[u].firstarc;
    for (i = 0; i < G->maxnode; i++) {
        distance[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }
    while (ptr != NULL) {
        distance[ptr->adjvex] = ptr->weight;
        temp.val = ptr->adjvex;
        temp.wei = ptr->weight;
        enQueue(qu, temp);
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
        temp.val = u;
        MINdis = INF;
        deQueue(qu, &temp);
        //printf("出队:%d  wei:%d\n", k, distance[k]);
        k = temp.val;
        visited[k] = 1;
        ptr = G->adjlist[k].firstarc;
        while (ptr != NULL) {
            j = ptr->adjvex;
            if (ptr->weight < INF && distance[k] + ptr->weight < distance[j] && visited[j] == 0) {
                distance[j] = distance[k] + ptr->weight;
                temp.val = j;
                temp.wei = distance[j];
                enQueue(qu, temp);
                parent[j] = k;
            }
            ptr = ptr->nextarc;
        }
    }
    Dispath(G, distance, parent, visited, u, v);
    return output;
}

void Dispath(AdjGraph* G, int dist[], int path[], int S[], int u, int v)
{
    int i, j, k;
    int *apath, d;
    char temp[MAXSTR];
    apath = (int *)calloc(G->maxnode, sizeof(int));
    i = v;
    if (S[i] == 1 && i != u) {
        weights = dist[i];
        d = 0;
        apath[d] = i;
        k = path[i];
        if (k == -1) {
            strcpy_p(output, "无路径");
        } else {
            while (k != u) {
                d++;
                apath[d] = k;
                k = path[k];
            }
            d++;
            apath[d] = u;
            sprintf(temp, "%d", apath[d]);
            strcat_p(output, temp);
            for (j = d - 1; j >= 0; j--) {
                sprintf(temp, " -> %d", apath[j]);
                strcat_p(output, temp);
            }
        }
    }
}

int strcmp_p(char* destination, char* source)
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

void strcat_p(char destination[], char source[])
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

void strcpy_p(char destination[], char source[])
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