#include <stdio.h>
#include <stdlib.h>

#include "search.h"
#include "stats.h"
#include "queue.h"

extern long long weights;

void print_help()
{
    printf("    - `./search-cli -h/--help`(-h或--help，以下同) 显示帮助菜单，格式没有要求，不作为评分要求，只求自己能够看懂\n\
    - `./search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS` 显示以 `FILE_PATH` 为输入文件的图的统计信息，输出没有格式要求，具体支持的`STATS_PARAMS`参数如下：\n\
      - `edges`\n\
      - `vertices`\n\
      - `freeman`\n\
      - `closeness`\n\
    - `./search-cli -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT` 显示以 `FILE_PATH` 为输入文件的图中 从开始点 u 到 终点 v 的用 `SEARCH_PARAMS`蒜出来的最短路径\n\
      - 样例输入： `./search-cli -g ./sx-stackoverflow.txt -sp Dijkstra -u 1 -v 5`\n\
      - 样例输出： `1 -> 2 -> 3 -> 4 ->5`\n");
    return;
}

void print_suantou()
{
    printf("这是蒜头君的画像\n");
}

void print_error()
{
    printf("输入有误，建议输入\"./search-cli -h/--help\"命令以查询使用方法\n");
    return;
}

int main(int argc, char* argv[])
{

    if (argc == 2 && (!strcmp_p(argv[1], "-h") || !strcmp_p(argv[1], "--help"))) {
        print_help();
    } else if (!strcmp_p(argv[1], "-g") || !strcmp_p(argv[1], "--graph")) {
        if ((!strcmp_p(argv[3], "-s") || !strcmp_p(argv[3], "--stats"))) {
            if (!strcmp_p(argv[4], "edges")) {
                printf("%d\n", numberOfEdges(argv[2]));
            } else if (!strcmp_p(argv[4], "vertices")) {
                printf("%d\n", numberOfVertices(argv[2]));
            } else if (!strcmp_p(argv[4], "freeman")) {
                printf("%f\n",freemanNetworkCentrality(argv[2]));
            } else if (!strcmp_p(argv[4], "closeness")) {
                printf("%f\n",closenessCentrality(argv[2], atoi(argv[5])));
            } else {
                print_error();
            }
        } else if ((!strcmp_p(argv[3], "-sp") || !strcmp_p(argv[3], "--shortestpath")) && argc == 9) {
            printf("%s\n", shortestPath(atoi(argv[6]), atoi(argv[8]), argv[4], argv[2]));
            printf("cost: %lld\n", weights);
        } else {
            print_error();
        }
    } else if (argc == 2 && !strcmp_p(argv[1], "-j")) {
        print_suantou();
    } else {
        print_error();
    }

    return 0;
}

/*
float closenessCentrality(char name[], int u)
{
    printf("u = %d\n", u);
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
    free(n_list);
    int MINdis, k;
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
    printf("初始化完成\nq->rear地址 = %p\n", &qu->rear);
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

            printf("close qu->rear地址 = %p 值 = %lld\n", &qu->rear, qu->rear);

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
        printf("k = %d\n", k);
        visited[k] = 1;

        ptr = G->adjlist[k].firstarc;
        while (ptr != NULL) {
            j = ptr->adjvex;
            if (ptr->weight < INF && distance[k] + ptr->weight < distance[j] && visited[j] == 0) {
                distance[j] = distance[k] + ptr->weight;
                temp.val = j;
                temp.wei = distance[j];
                printf("k = %d   j = %d\n", k, j);
                enPQueue(qu, temp);
                parent[j] = k;
            }
            ptr = ptr->nextarc;
        }
    }
    printf("!!!!\n");
    double res = 0;
    j = 0;
    for (i = 0; i < G->maxnode + 2; i++) {
        if (distance[i] < INF && distance[i] > 0 && i != u) {
            res += (double)distance[i];
            j++;
        }
    }
    res /= (double)(j);
    res = 1.0 / res;
    return (float)res;
}*/