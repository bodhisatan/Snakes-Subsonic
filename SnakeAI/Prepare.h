/************************************************************************/
/*					头文件                                              */
/************************************************************************/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <queue>
#include <iterator>
#include <stack>
using namespace std;
/************************************************************************/
/*					常量声明                                            */
/************************************************************************/
const int ROWUNIT = 1;													//控制台单位行大小
const int COLUMNUNIT = 2;												//控制台单位列大小
const int HEIGHT = 20;													//游戏区域高
const int WIDTH = 40;													//游戏区域宽
const int INF = 10000;													//无穷大常量
const int SNAKEBODY = 20000;											//表征蛇身的常量
const int WALL = 30000;													//表征墙的常量


/************************************************************************/
/*					结构声明                                            */
/************************************************************************/
typedef struct node
{
    int x;
    int y;
} SnakeNode;																//一个位置，可以表示食物，蛇身结点等

SnakeNode Food;															//食物

SnakeNode NextStep;														//下一步的位置

SnakeNode theTail;														//蛇尾位置

int NextDirection;														//下一步的方向

list<SnakeNode> Snake;													//记录蛇的链表

list<SnakeNode> VirtualSnake;											//记录虚拟蛇的链表

int SnakeDirection;														//蛇的当前方向

int Direction[4][2] = { { 0, ROWUNIT },{ 0, -ROWUNIT },
    { COLUMNUNIT, 0 },{ -COLUMNUNIT, 0 }
};			//记录方向表

int bfsDistance[WIDTH + 2 * COLUMNUNIT][HEIGHT + 2 * ROWUNIT];			//记录bfs时的最短路,即每次蛇头与与食物真实距离

int bfsJudgeVirtualTail[WIDTH + 2 * COLUMNUNIT][HEIGHT + 2 * ROWUNIT];	//记录虚拟蛇尾与各位置距离

int bfsJudgeRealTail[WIDTH + 2 * COLUMNUNIT][HEIGHT + 2 * ROWUNIT];		//记录各位置到蛇尾距离

int dfsDistance[WIDTH + 2 * COLUMNUNIT][HEIGHT + 2 * ROWUNIT];			//记录递归求得的距离

int Mark[WIDTH + 2 * COLUMNUNIT][HEIGHT + 2 * ROWUNIT];					//标记不可到达的位置

int currentDepth, deepest;												//当前深度，最大深度


/*注释模板*/
/************************************************************************/
/*函数名称：																*/
/*函数功能：																*/
/*参数列表：																*/
/*返回值:																*/
/*版本：																	*/
/*author:																*/
/************************************************************************/


/************************************************************************/
/*函数名称：		setPosition												*/
/*函数功能：		设定光标位置												*/
/*参数列表：		光标坐标 x y												*/
/*返回值:		无														*/
/*版本：			1.0														*/
/*author:		Bodhisatan													*/
/************************************************************************/
void setPosition(int x, int y);

/************************************************************************/
/*函数名称：		hideCursor												*/
/*函数功能：		设置光标不可见											*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			1.0														*/
/*author:		Bodhisatan													*/
/************************************************************************/
void hideCursor();

/************************************************************************/
/*函数名称：		checkSnake												*/
/*函数功能：		检查蛇身是否重合，调试使用									*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			2.0														*/
/*author:		Bodhisatan													*/
/************************************************************************/
void checkSnake();

/************************************************************************/
/*函数名称：		isHeadequalTail											*/
/*函数功能：		检查蛇头是否撞到蛇尾										*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			2.0														*/
/*author:		Bodhisatan													*/
/************************************************************************/
void isHeadequalTail();

/************************************************************************/
/*函数名称：		createFood												*/
/*函数功能：		产生食物													*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			1.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void createFood();

/************************************************************************/
/*函数名称：		printSnake												*/
/*函数功能：		打印蛇身													*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			3.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void printSnake();

/************************************************************************/
/*函数名称：		isOpposite												*/
/*函数功能：		判断移动方向是否与当前方向相反								*/
/*参数列表：		移动方向a,当前方向b										*/
/*返回值:		相反返回true，否则返回false								*/
/*版本：			1.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
bool isOpposite(int a, int b);

/************************************************************************/
/*函数名称：		createInterface											*/
/*函数功能：		打印游戏界面												*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void createInterface();

/************************************************************************/
/*函数名称：		getFoodDistance											*/
/*函数功能：		获取食物与各位置距离，使用BFS								*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void getFoodDistance();

/************************************************************************/
/*函数名称：		isReachable												*/
/*函数功能：		判断蛇头是否能达到食物									*/
/*参数列表:		没有参数													*/
/*返回值：		蛇能吃到食物返回true，否则返回false						*/
/*版本:			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
bool isReachable();

/************************************************************************/
/*函数名称：		isVirtualTailReachable_Regular							*/
/*函数功能：		沿蛇身选择最短路径去吃食物									*/
/*参数列表：		无														*/
/*返回值:		如果吃完能找到蛇头则返回true，否则返回false					*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
bool isVirtualTailReachable_Regular();

/************************************************************************/
/*函数名称：		isVirtualTailReachable_Random							*/
/*函数功能：		方向随机但是是最短路径去吃食物								*/
/*参数列表：		无														*/
/*返回值:		如果吃完能找到蛇头则返回true，否则返回false					*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
bool isVirtualTailReachable_Random();

/************************************************************************/
/*函数名称：		eatFoodMove												*/
/*函数功能：		沿最近方向移动一步										*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void eatFoodMove();

/************************************************************************/
/*函数名称：		eatFood													*/
/*函数功能：		选择一种策略吃食物										*/
/*参数列表：		无														*/
/*返回值:		有可选择策略则返回true,否则返回false						*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
bool eatFood();

/************************************************************************/
/*函数名称：		isSafe													*/
/*函数功能：		判断蛇吃完食物是否安全（能找到尾巴）						*/
/*参数列表：		蛇头														*/
/*返回值:		安全则返回true，否则返回false								*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
bool isSafe(SnakeNode NewHead);

/************************************************************************/
/*函数名称：		followTailMove											*/
/*函数功能：		不能去吃食物就去追着尾巴跑									*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void followTailMove();

/************************************************************************/
/*函数名称：		FoodDistance											*/
/*函数功能：		不考虑蛇身，求到食物的曼哈顿距离							*/
/*参数列表：		某一位置													*/
/*返回值:		距离														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
int FoodDistance(SnakeNode adj);

/************************************************************************/
/*函数名称：		followTail												*/
/*函数功能：		追着尾巴走												*/
/*参数列表：		无														*/
/*返回值:		能执行这种策略返回true，否则返回false						*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
bool followTail();

/************************************************************************/
/*函数名称：		DFS														*/
/*函数功能：		递归求解某一位置深度										*/
/*参数列表：		当前递归位置												*/
/*返回值:		无														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void DFS(int x, int y);

/************************************************************************/
/*函数名称：		getDepth												*/
/*函数功能：		DFS获取各个方向的最深路径									*/
/*参数列表：		表示位置的结构体											*/
/*返回值:		int，深度												*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
int getDepth(SnakeNode temp);

/************************************************************************/
/*函数名称：		snakeWander												*/
/*函数功能：		如果所有策略都不可行，DFS最长的路径走						*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void snakeWander();

/************************************************************************/
/*函数名称：		snakeMove												*/
/*函数功能：		选择一种策略移动											*/
/*参数列表：		无														*/
/*返回值:		无														*/
/*版本：			4.0														*/
/*author:		Bodhisatan														*/
/************************************************************************/
void snakeMove();
