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
    printf("\n\
                                                               1\n\
                                                             .0i1C ti18\n\
                                                            L;iitt;;tL\n\
                                         t8C88CCC8C808Cfiiiiii;;8iiitCftt\n\
                                    8;;;;;;;;iiiiiiiii;iiiiiiGiiiiiitftL\n\
                                ;ii;;;;;;;iiiiiiiiiL8tiiiiiiiiiiiii1Cft8\n\
                              ft1iiiiiiiiiiiiiCi;;;;;;iiiiiiiiiiiii1ttf8\n\
          .G88f              8fttiiiiiiiii1t8iiiiiiiiiiiiiiiiiiiiiitLtft\n\
         :;;;;;ii;L1C8CGLLG88CLft1ii;i;;CL:::;iCiiiiiiiiiiiiiii;ii1tLtttG\n\
        ii;;;;L::::::::::::;;;;;;;i;C:::::;;;;;1Giiiiiiiiiiiiiii11tttLttfL\n\
        ii;;:,,::::::,::::;fLCCi;;;;;;;;;;;;i;i1t1iiiiiiiiiiii11tttttfttttt\n\
       8ii::,,,,::::LftfffLfff;;;;;;;;;;;;;;;;i11Liiiiii1111ttttttttffLftttt1\n\
       1;;:::::::CttfffffffG;;;;;;;;;;;;;;;;;;i1tL1tttttttttttttttftttt8ttttti\n\
     1;;;;:::,::::8fffLfLi;;;;;;;;;;;;;;;;;;;;i111ftttttttttttttffttttttt1tttf,\n\
    C;::;;;;;ffi;;;;iL;i;;;;;i;;;;;;;;;;;;;;;i1111CtttttttttttttttttffttCtttttL\n\
   1:GXXL;;;;Gti;;;;i;;;;;;;i:G;;i;iCXGX;;;;;i1111tit1ttfttfttttttftttttfttttttC\n\
  .iX.GfXX1;;;i;i;;;;LL;;;;;;f::;;tX8ffLLX;;ii11t111111ttfffttfttttttttttttttttf\n\
  fX.XtX;Xt;;;;;;;;Cfffi;;;;8:;:XX.1XXtXXXX11111111C11111Gtffftttttttttttttttttt\n\
 LX..XX:,X;;;;;;;;8fffGi;;;;;:;X...XXX...XXX1111111G11GfLLLCfftttttttttfttttttff\n\
 iX..XX.XX;;;;;;;;;;iG8;;;;;;;X....XXX,..XLX1111111111tCLLLLff8tttttfffttttttttG\n\
:iX .fXXXi;;:;;;;;;;;;;;;;;;;;X...,CXLLXXXXX111111111111GLLLLLLfLCfftfttttttttfC\n\
ti;XxXLXL:;::;;;;;;;;;;;;;;;;;X....,fXtXXXt81111111111111CLfLLLLLf1Gttttttttff8\n\
GiGi;;;:;;;::;;;;;;;;;;;;;;;;;;XGX1XX;iiii1111111111111111CGfLLLLft1t8ftttfftC\n\
 ittfLii;;;;:;;;;;i;;;;;;;;;;;;;;;;;;ii1111C1111tt11111111111111111111tfttCL\n\
    L1111Gfiii;;;i;;;;;;iiiiiiiiiitiL8C11111111t8t111111111111111t111111Ci\n\
      tf111CfffffftfffffffffffffffffL1111111111G111i;;ii111i11tt1iiii11118\n\
         .L111Gtiiii1i1iii11i11tGL11111111ii81i;;;;;;;;;iif11tLi;;;i111111C\n\
          1;;8t11t1GCGL1ttCCt111t11111118tf1;;;i;;;;;;;;ii11G;i;LffL1111111\n\
          G;;;i;iit8L1111111111fC8ftffftf1;;;;;1fG;;;;;ii1t8;;Lttfff1111t118\n\
          Ci;;iLfLii111ttfftttttffffffttti;i:;itff;;;;ii118iiGttffLLf111111C\n\
           ;;ttttf111111tG111ttttfftttttt;811L;;;;;;;;i1i1i;;;8ffLLLC1111118\n\
           L11tttL8111111111fCtt1tttttfCt111tG;;;;;;;iiiiG1111i18LG81111111C\n\
            CfttfG11i111111t0    ttLCC8fttttLi;;;;;;ii1;LC1111111111111111t:\n\
             t;;;ii1111111iC      8ftt8ffff1;;;;;;iii11ii011111111111111118\n\
              C;11i11i11i1         GfCiLLGL;;;;;iiii;8    iftt11111111t1tL\n\
             :XX,;11.C1X8             ;ii;;;;ii1111t        C01iG11tttitt\n\
              .XXX XX X              ;.L;,.L1L1i1X             t;C;L:C\n\
                                        XCiX ;XX\n\
+-------------------------------------------------------------------------------------+\n\
|                                                                                     |\n\
|                                                                                     |\n\
|                                                                                     |\n\
|                          呵呵，想不到你居然闯到了这里呢！                           |\n\
|                      那么，就由我蒜头大魔王来做你的对手吧！                         |\n\
|                                                                                     |\n\
|                                    选择:                                            |\n\
|                                                                                     |\n\
|                     > 是                             > OK                           |\n\
|                                                                                     |\n\
+-------------------------------------------------------------------------------------+\n\
    \n");
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