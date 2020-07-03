#include <stdio.h>
#include <stdlib.h>

extern weights;

void print_help()
{
    printf("    - `./search-cli -h/--help`(-h��--help������ͬ) ��ʾ�����˵�����ʽû��Ҫ�󣬲���Ϊ����Ҫ��ֻ���Լ��ܹ�����\n\
    - `./search-cli -g/--graph FILE_PATH -s/--stats STATS_PARAMS` ��ʾ�� `FILE_PATH` Ϊ�����ļ���ͼ��ͳ����Ϣ�����û�и�ʽҪ�󣬾���֧�ֵ�`STATS_PARAMS`�������£�\n\
      - `edges`\n\
      - `vertices`\n\
      - `freeman`\n\
      - `closeness`\n\
    - `./search-cli -g/--graph FILE_PATH -sp/--shortestpath SEARCH_PARAMS -u STARTING_POINT -v TARGET_POINT` ��ʾ�� `FILE_PATH` Ϊ�����ļ���ͼ�� �ӿ�ʼ�� u �� �յ� v ���� `SEARCH_PARAMS`����������·��\n\
      - �������룺 `./search-cli -g ./sx-stackoverflow.txt -sp Dijkstra -u 1 -v 5`\n\
      - ��������� `1 -> 2 -> 3 -> 4 ->5`\n");
    return;
}

void print_suantou()
{
    printf("������ͷ���Ļ���\n");
}

void print_error()
{
    printf("�������󣬽�������\"./search-cli -h/--help\"�����Բ�ѯʹ�÷���\n");
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