#include "stats.h"
#include "queue.h"

float closenessCentrality(char name[], int u)
{
    AdjGraph* G;
    int i, j;
    int temp_u, temp_v, temp_max;
    long long temp_w;
    char* n_list;
    ArcNode* p;
    n_list = (char*)calloc(MAXV, sizeof(char));
    G = (AdjGraph*)malloc(sizeof(AdjGraph));
    if (G == NULL) {
        printf("图G申请失败\n");
    }
    for (i = 0; i < MAXV; i++) {
        G->adjlist[i].firstarc = NULL;
    }

    freopen(name, "r", stdin);
    G->e = 0;
    temp_max = 0;
    while (scanf("%d %d %lld", &temp_u, &temp_v, &temp_w) != EOF) {
        G->e++;
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
        p->nextarc = G->adjlist[temp_u].firstarc;
        G->adjlist[temp_u].firstarc = p;
    }

    G->maxnode = temp_max;
    G->n = 0;
    for (i = 0; i < MAXV; i++) {
        if (n_list[i] == 1) {
            G->n++;
        }
    }
    free(n_list); // 完成邻接表

    int k;
    ArcNode* ptr;
    SqQueue* qu = NULL;
    Box temp;
    char* visited;
    int* parent;
    long long* distance;
    distance = (long long*)calloc(G->maxnode + 1, sizeof(long long));
    parent = (int*)calloc(G->maxnode + 1, sizeof(int));
    visited = (char*)calloc(G->maxnode + 1, sizeof(char));
    if (visited == NULL || distance == NULL || parent == NULL) {
        printf("内存申请失败\n");
    }
    InitQueue(&qu);
    ptr = G->adjlist[u].firstarc;
    for (i = 0; i <= G->maxnode; i++) {
        distance[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    while (ptr != NULL) {
        if (ptr->adjvex != u) {
            distance[ptr->adjvex] = ptr->weight;
            temp.val = ptr->adjvex;
            temp.wei = ptr->weight;
            enPQueue(qu, temp);
            if (ptr->weight < INF) {
                parent[ptr->adjvex] = u;
            } else {
                parent[ptr->adjvex] = -1;
            }
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
                distance[j] = distance[k] + ptr->weight;
                temp.val = j;
                temp.wei = distance[j];
                enPQueue(qu, temp);
                parent[j] = k;
            }
            ptr = ptr->nextarc;
        }
    }           //完成Dijkstra

    double res = 0;
    j = 0;
    for (i = 0; i < G->maxnode + 2; i++) {
        if (distance[i] < INF && distance[i] > 0 && i != u) {
            res += (double)distance[i];
            j++;
        }
    }
    res /= (double)(j);
    res = 1.0 / res;    //累加除以点数再求倒

    return (float)res;
}

float freemanNetworkCentrality(char* name)
{
    AdjGraph* G;
    int i, j, cc_flag, cdmax;
    int temp_u, temp_v, temp_max;
    long long temp_w, cdsum;
    char* n_list;
    double res;
    ArcNode *p, *cc;
    n_list = (char*)calloc(MAXV, sizeof(char));
    G = (AdjGraph*)malloc(sizeof(AdjGraph));
    for (i = 0; i < MAXV; i++) {
        G->adjlist[i].firstarc = NULL;
    }
    freopen(name, "r", stdin);
    G->e = 0;
    temp_max = 0;
    while (scanf("%d %d %lld", &temp_u, &temp_v, &temp_w) != EOF) {
        cc_flag = 0;
        if (temp_u > temp_max || temp_v > temp_max) {
            temp_max = temp_u > temp_v ? temp_u : temp_v;   //找出最大节点的编号
        }
        n_list[temp_u] = 1;
        n_list[temp_v] = 1;
        cc = G->adjlist[temp_u].firstarc;
        while (cc != NULL) {
            if (cc->adjvex == temp_v) {
                cc_flag = 1;
            }
            cc = cc->nextarc;
        }
        if (cc_flag == 1) {
            continue;       //检测到重边则continue
        }

        p = (ArcNode*)malloc(sizeof(ArcNode));
        if (p == NULL) {
            printf("malloc申请内存失败\n");
        }
        p->adjvex = temp_v;
        p->weight = temp_w;
        p->nextarc = G->adjlist[temp_u].firstarc;
        G->adjlist[temp_u].firstarc = p;
        if (temp_u != temp_v) { //若起点和终点都为自己则不建立第二条边
            p = (ArcNode*)malloc(sizeof(ArcNode));
            if (p == NULL) {
                printf("malloc申请内存失败\n");
            }
            p->adjvex = temp_u;
            p->weight = temp_w;
            p->nextarc = G->adjlist[temp_v].firstarc;
            G->adjlist[temp_v].firstarc = p;
        }
        G->e++;
    }
    G->maxnode = temp_max;
    G->n = 0;
    for (i = 0; i <= G->maxnode; i++) {
        if (n_list[i] == 1) {
            G->n++;     //找出节点数
        }
    }
    cdsum = 0;
    cdmax = 0;
    for (i = 0; i <= G->maxnode; i++) {
        j = 0;
        p = G->adjlist[i].firstarc;
        while (p != NULL) {
            j++;
            p = p->nextarc;
        }
        if (j > cdmax) {
            cdmax = j;
        }
        cdsum += j;
    }       //找出最大度数和所有点度数之和

    res = (G->n) * cdmax;
    res -= cdsum;
    res /= (G->n - 1);
    res /= (G->n - 2);
    return (float)res;
}

int numberOfEdges(char name[])
{
    //初始化
    FILE* fp;
    char way[100];
    long long i = 0;
    int* v1;
    int* v2;
    int* e;
    v1 = (int*)calloc(M, sizeof(int));
    v2 = (int*)calloc(M, sizeof(int));
    e = (int*)calloc(M, sizeof(int));
    strcpy_m(way, name);
    fp = fopen(way, "r");

    //判断文件是否已经打开
    if (fp == NULL) {
        printf("Open filefailure!\n");
        exit(1);
    }
    //读入数据
    while (!feof(fp)) {
        int ret = fscanf(fp, "%d %d %d", &v1[0], &v2[0], &e[0]);
        if (ret <= 0) {
            break;
        }
        i++; //每读入一行则表明 有一条边
    }
    //输出边的数目
    return (int)i;
}

int numberOfVertices(char name[])
{
    //初始化
    FILE* fp;
    char way[100];
    int i = 0;
    int j = 0;
    int* v1;
    int* v2;
    int* e;
    int* v;
    v1 = (int*)calloc(M, sizeof(int));
    v2 = (int*)calloc(M, sizeof(int));
    e = (int*)calloc(M, sizeof(int));
    v = (int*)calloc(N, sizeof(int));

    strcpy_m(way, name);
    fp = fopen(way, "r");
    //判断文件是否已经打开
    if (fp == NULL) {
        printf("Open filefailure!");
        exit(1);
    }

    //读入数据
    while (!feof(fp)) {
        int ret = fscanf(fp, "%d %d %d", &v1[0], &v2[0], &e[0]);
        //将 存在的点 变成v【】数组的下标  ，并且对应值赋为1；
        v[v1[0]] = 1;
        v[v2[0]] = 1;
        if (ret <= 0) {
            break;
        }
        i++;
    }

    for (i = 0; i < N; i++) {
        if (v[i] == 1) {
            j++; //当v【】数组中的值为1时 表明存在一个点； 累加得总数；
        }
    }

    return j; //返回点数
}

char* strcpy_m(char* dst, const char* src)
{
    if ((dst == NULL) || (src == NULL)) {
        return NULL;
    }
    char* ret = dst; //[1]
    while ((*dst++ = *src++) != '\0')
        ; //[2]
    return ret; //[3]
}