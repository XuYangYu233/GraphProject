#include <stdio.h>
#include <stdlib.h>

extern weights;

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
        if ((!strcmp_p(argv[3], "-s") || !strcmp_p(argv[3], "--stats")) && argc == 5) {
            if (!strcmp_p(argv[4], "edges")) {
                /*numberOfEdges(argv[2])*/
            } else if (!strcmp_p(argv[4], "vertices")) {
                /*numberOfVertices(argv[2])*/
            } else if (!strcmp_p(argv[4], "freeman")) {
                /*freemanNetworkCentrality(argv[2])*/
            } else if (!strcmp_p(argv[4], "closeness")) {
                /*closenessCentrality(argv[2])*/
            } else {
                print_error();
            }
        } else if ((!strcmp_p(argv[3], "-sp") || !strcmp_p(argv[3], "--shortestpath")) && argc == 9) {
            printf("%s\n", shortestPath(atoi(argv[6]), atoi(argv[8]), argv[4], argv[2]));
            printf("cost: %d\n", weights);
        }
    } else if (argc == 2 && !strcmp_p(argv[1], "-j")) {
        print_suantou();
    } else {
        print_error();
    }

    return 0;
}