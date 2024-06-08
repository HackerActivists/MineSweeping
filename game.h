#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

// 显示板子 行 和 列
#define ROW 5
#define COL 5

// 控制板子 行 和 列
#define ROWS ROW + 2
#define COLS COL + 2

// 困难程度(雷的个数)
#define Easy_Count  (ROW * COL) / 4

// 显示 的棋盘
extern char Show_board[ROW][COL];
// 控制 的棋盘
extern char Mine_board[ROWS][COLS];

// 打印菜单
void Display_menu(void);
// 初始化棋盘
void Init_Board(void);
// 显示棋盘
void Display_Board(void);
// 运行游戏
void Run_Game(void);
// 设置雷
void Set_Mine(void);
// 排查雷
void Find_Mine(void);
//选择操作内容
int Select_Operate(void);
//设置标记的位置
void Mark_Place(void);
//删除标记的位置
void Delete_Place(void);
// 计算周围雷的个数
int Count_Around_Mine(int X, int Y);
// 判断输赢
int Is_Win(void);
// 爆炸展开棋盘
void Explosion_Spread(int X, int Y);
