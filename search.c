#include "search.h"
#include "queue.h"
// 部分代码来源于课本

char* visited;
char output[MAXSTR] = "";
long long weights = 0;

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
    int temp_u, temp_v, temp_max;
    long long temp_w;
    char* n_list;
    ArcNode* p;
    n_list = (char*)calloc(MAXV, sizeof(char));
    *G = (AdjGraph*)malloc(sizeof(AdjGraph));
    if (*G == NULL) {
        printf("图G申请失败\n");
    }
    for (i = 0; i < MAXV; i++) {
        (*G)->adjlist[i].firstarc = NULL;
    }

    freopen(name, "r", stdin);
    (*G)->e = 0;
    temp_max = 0;
    while (scanf("%d %d %lld", &temp_u, &temp_v, &temp_w) != EOF) {
        (*G)->e++;
        if (temp_u > temp_max || temp_v > temp_max) {
            temp_max = temp_u > temp_v ? temp_u : temp_v;
        }
        n_list[temp_u] = 1;
        n_list[temp_v] = 1;
        p = (ArcNode*)malloc(sizeof(ArcNode));
        if (p == NULL) {
            printf("p节点申请失败\n");
        }
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
    ArcNode* ptr;
    char* tmp_str;
    Box *b_stack, trans, *waste, change;
    int pop_out, top = -1, rear = -1, i;
    tmp_str = (char*)calloc(MAXSTR, sizeof(char));
    b_stack = (Box*)calloc(G->maxnode / 2, sizeof(Box));
    waste = (Box*)calloc(G->maxnode / 2, sizeof(Box));
    visited = (char*)calloc(G->maxnode + 1, sizeof(char));
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
        trans = b_stack[top]; //出栈
        top--;
        rear++;
        waste[rear] = trans;
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
                top++; //进栈
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
    int i, j;
    int* path;
    long long* distance;
    bool break_flag = false;
    ArcNode* p;
    SqQueue* qu;
    Box temp, ptr;
    char* token;
    token = (char*)calloc(MAXSTR, sizeof(char));
    visited = (char*)calloc(G->maxnode + 1, sizeof(char));
    path = (int*)calloc(G->maxnode + 1, sizeof(int));
    distance = (long long*)calloc(G->maxnode + 1, sizeof(long long));
    if (token == NULL || visited == NULL || path == NULL) {
        printf("内存申请失败\n");
    }
    InitQueue(&qu);

    for (i = 0; i < G->maxnode + 1; i++) {
        distance[i] = INF; // 初始化distance数组
    }

    visited[u] = 1;
    temp.val = u;
    temp.wei = 0;
    enQueue(qu, temp);
    path[u] = -1;
    distance[u] = 0;
    strcpy_p(output, "unreachable");
    while (!QueueEmpty(qu)) {
        deQueue(qu, &ptr);
        visited[ptr.val] = 0;
        p = G->adjlist[ptr.val].firstarc;
        while (p != NULL) {
            if (distance[p->adjvex] > distance[ptr.val] + p->weight) {
                distance[p->adjvex] = distance[ptr.val] + p->weight; //松弛
                if (visited[p->adjvex] == 0) {
                    temp.val = p->adjvex;
                    enQueue(qu, temp);
                    visited[p->adjvex] = 1;
                }
                path[p->adjvex] = ptr.val;      //记录路径
            }
            p = p->nextarc;
        }
    }
    sprintf(output, "%d", v);
    weights = distance[v];
    i = path[v];
    while (path[i] != -1) {
        sprintf(token, "%d", i);
        strcat_p(token, " -> ");
        strcat_p(token, output);
        strcpy_p(output, token);
        i = path[i];
    }
    sprintf(token, "%d", i);
    strcat_p(token, " -> ");
    strcat_p(token, output);
    strcpy_p(output, token);
    return output;
}

//Dijkstra算法
char* Dijkstra(int u, int v, AdjGraph* G)
{
    int* parent;
    long long* distance;
    distance = (long long*)calloc(G->maxnode + 1, sizeof(long long));
    parent = (int*)calloc(G->maxnode + 1, sizeof(int));
    visited = (char*)calloc(G->maxnode + 1, sizeof(char));
    if (visited == NULL || distance == NULL || parent == NULL) {
        printf("内存申请失败\n");
    }
    int i, j, k;
    ArcNode* ptr;
    SqQueue* qu;
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
        enPQueue(qu, temp);
        if (ptr->weight < INF) {
            parent[ptr->adjvex] = u;
        } else {
            parent[ptr->adjvex] = -1;
        }
        ptr = ptr->nextarc;
    }

    visited[u] = 1;
    parent[u] = 0;
    while (!QueueEmpty(qu)) {
        temp.val = u;
        dePQueue(qu, &temp);
        k = temp.val;
        visited[k] = 1;
        ptr = G->adjlist[k].firstarc;
        while (ptr != NULL) {
            j = ptr->adjvex;
            if (ptr->weight < INF && distance[k] + ptr->weight < distance[j] && visited[j] == 0) {
                distance[j] = distance[k] + ptr->weight;    // 松弛
                temp.val = j;
                temp.wei = distance[j];
                enPQueue(qu, temp);
                parent[j] = k;  // 记录路径
            }
            ptr = ptr->nextarc;
        }
    }
    Dispath(G, distance, parent, visited, u, v);    //处理路径
    return output;
}

void Dispath(AdjGraph* G, long long dist[], int path[], char S[], int u, int v)
{
    int i, j, k;
    int *apath, d;
    char* temp;
    temp = (char*)calloc(MAXSTR, sizeof(char));
    apath = (int*)calloc(G->maxnode + 1, sizeof(int));
    i = v;
    if (S[i] == 1 && i != u) {
        weights = dist[i];
        d = 0;
        apath[d] = i;
        k = path[i];
        if (k == -1) {
            strcpy_p(output, "unreachable");
        } else {
            while (k != u) {
                d++;
                apath[d] = k;
                k = path[k]; //将原本反向的路径正向放入apath
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
    } else {
        strcpy_p(output, "unreachable");
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