#include "game.h"

char Show_board[ROW][COL] = {'\0'};
char Mine_board[ROWS][COLS] = {'\0'};

// 显示菜单
void Display_menu()
{
    printf("**********************************\n");
    printf("**********  1.palyer  ************\n");
    printf("**********  0.exit  **************\n");
    printf("**********************************\n");
}
// 初始化棋盘
void Init_Board()
{
    int i = 0;
    int j = 0;
    // 初始化显示棋盘:
    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            Show_board[i][j] = '*';
    // 初始化控制棋盘:
    // 一定要初始化控制棋盘，不然在下一次循环玩游戏时就会出现地雷次数不一情况
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            Mine_board[i][j] = '\0';
}
// 显示棋盘
void Display_Board()
{
    int i = 0;
    int j = 0;
    printf("\n");
    system("cls");
    printf("------------MineSweeping Game------------\n");
    printf("  ");
    for (i = 1; i <= COL; i++)
        printf(" %d ", i); // 显示 列 坐标
    printf("\n");
    for (i = 0; i < ROW; i++)
    {
        printf("%d ", i + 1); // 显示 行 坐标

        for (j = 0; j < COL; j++)
            printf(" %c ", Show_board[i][j]);
        printf("\n");
    }
    printf("------------MineSweeping Game------------\n");
}
// 运行游戏
void Run_Game()
{
    Init_Board();    // 初始化棋盘
    Display_Board(); // 显示棋盘
    Set_Mine();      // 安插雷
    Find_Mine();    //排查雷    

    printf("\n");
    printf("Do you want to continue playing the game ?\n");
    printf("-----------1.continue   0.break-----------\n");
    printf("Your choose is:");
}
// 安插雷
void Set_Mine()
{
    srand((unsigned int)time(NULL));
    int count = 0;
    while (count != Easy_Count)
    {
        int X = rand() % ROW + 1; // 1 -- ROW
        int Y = rand() % COL + 1; // 2 --COL

        if (Mine_board[X][Y] == '\0') // 这个坐标没有任何东西时才能成功赋值一个雷
        {                             // 否则会出现重复安插雷(导致雷数不够)的情况
            Mine_board[X][Y] = 'M';
            count++;
        }
    }
}
// 排查雷
void Find_Mine()
{
    int X = 0;
    int Y = 0;
    int flag = 1;   
    while (1)
    {
        if (Select_Operate() == 1)  //判断所选操作是否为 排雷操作
        {
            while (1)
            {
            printf("Please input your coordinate :");
            scanf("%d%d", &X, &Y);
                // 该位置不为 '*' 有三种情况--> 1.坐标超出范围 2.坐标已被掀开 3.坐标已被标记
                //这里是想没有被使用的全部涵盖了，所以我们应当将标记的情况排除在外
                if (Show_board[X - 1][Y - 1] != '*' && Show_board[X - 1][Y - 1] != '!')
                {
                    if ((X < 1 || X > ROW) || (Y < 1 || Y > COL)) // 坐标超出范围
                        printf("coordinate error!!!\n");
                    else // 坐标被占用
                        printf("The ccordinate already cover occupy!!!\n");
                    // 打印提示语句
                    printf("Please afresh input:");
                    scanf("%d%d", &X, &Y);          //重新输入一下坐标
                }
                else if (Mine_board[X][Y] == 'M') // 该位置为雷
                {
                    Show_board[X - 1][Y - 1] = Mine_board[X][Y]; // 将雷赋值
                    Display_Board();                             // 游戏结束，显示一下棋盘
                    printf("There is alandmine in this  location!!!\n");
                    return;                             //打印提示信息，直接结束该函数块
                }
                else // 不满足以上情况就说明该坐标输入正确
                {
                    Explosion_Spread(X, Y); // 展开棋盘
                    Display_Board();        // 每次下完都刷新一下棋盘
                    if (Is_Win() == 1)      // 判断输赢
                    {
                        printf("Win!!!\n");
                        return ;                    
                    }
                    break;
                }
            }
        }
    }
}
// 计算周围雷的个数
int Count_Around_Mine(int X, int Y)
{
    int x = -1;
    int y = -1;
    int Mine_count = 0;
    // 循环遍历以该坐标为中心的九宫格
    for (x = -1; x + X < X + 2; x++)
        for (y = -1; y + Y < Y + 2; y++)
            if (Mine_board[X + x][Y + y] == 'M') // 如果为 雷 个数加1
                Mine_count++;
    return Mine_count;
}
// 判断输赢
int Is_Win()
{
    int i = 0;
    int j = 0;
    int count = 0;
    for (i = 0; i < ROW; i++)
        for (j = 0; j < COL; j++)
            if (Show_board[i][j] != '*')
                count++; // 统计还没有被掀开的格子
    // 当还 没有被掀开 的格子 等于 所有格子减去雷的个数时 即为将雷全部排完，否则继续
    if (count == ROW * COL - Easy_Count)
        return 1;
    else
        return 0;
}
// 爆炸展开棋盘
void Explosion_Spread(int X, int Y)
{
    int num = Count_Around_Mine(X, Y); // 获取周围雷的个数
    if (num == 0)                      // 周围没有雷
    {
        // 当 个数为 0 时以为周围没有地雷 --> 赋值空格
        Show_board[X - 1][Y - 1] = ' ';
        int x = 0;
        int y = 0;
        // 递归 范围炸开部分:
        for (x = -1; x + X < X + 2; x++)
        {
            for (y = -1; y + Y < Y + 2; y++)
                // 判断所得的坐标是否在范围内，否则会造成栈溢出，也无法对周围数组进行雷数统计
                if ((X + x > 0 && X + x <= ROW) && (Y + y > 0 && Y + y <= COL))
                    // 防止已经排查过过的位置再次排查，从而造成死递归
                    if (Show_board[X + x - 1][Y + y - 1] == '*' && Mine_board[X + x][Y + y] != 'M')
                        return Explosion_Spread(X + x, Y + y);
        }
    }
    // 当 个数为不为0 时以为周围有地雷 --> 赋值所得个数 加上 '0'得到一个 数字字符
    else
        Show_board[X - 1][Y - 1] = num + '0';
}
//  设置标记位置
void Mark_Place()
{
    int X = 0;
    int Y = 0;

    printf("Please input your coordinate :");
    scanf("%d%d", &X, &Y);
    while (1)
    {
        if (Show_board[X - 1][Y - 1] != '*')
        {
            if ((X < 1 || X > ROW) || (Y < 1 || Y > COL)) // 坐标超出范围
                printf("coordinate error!!!\n");
            else if (Show_board[X - 1][Y - 1] == '!') // 已经被标记
                printf("The coordinate have been marked!!!\n");
            else // 被占用
                printf("The ccordinate already cover occupy!!!\n");
            // 打印提示语句
            printf("Please afresh input:");
            scanf("%d%d", &X, &Y);
        }
        else
        {
            Show_board[X - 1][Y - 1] = '!';
            break;
        }
    }
}
//  删除标记
void Delete_Place()
{
    int X = 0;
    int Y = 0;

    printf("Please input your coordinate :");
    scanf("%d%d", &X, &Y);
    while (1)
    {
        if (Show_board[X - 1][Y - 1] != '*' && Show_board[X - 1][Y - 1] != '!')
        {
            if ((X < 1 || X > ROW) || (Y < 1 || Y > COL)) // 坐标超出范围
                printf("coordinate error!!!\n");
            else // 被占用
                printf("The ccordinate already cover occupy!!!\n");

            // 打印提示语句
            printf("Please afresh input:");
            scanf("%d%d", &X, &Y);
        }
        else
        {
            Show_board[X - 1][Y - 1] = '*';
            break;
        }
    }
}
// 选择操作内容
int Select_Operate()
{
    int select = 0;
    printf(" ----------------\n");
    printf("|0.mine clearance|\n");
    printf("|1.mark flag     |\n");
    printf("|2.Delete mark   |\n");
    printf(" ----------------\n");
    printf("Pleasr select your oprate-->");
    scanf("%d", &select);
    do
    {
        switch (select)
        {
        case 0:         //排雷操作
            break;
        case 1:         //添加标记
            Mark_Place();
            Display_Board();    //显示棋盘
            return 0;

        case 2:         //删除标记
            Delete_Place(); 
            Display_Board();    //删除棋盘
            return 0;
        default:            //输入不对,重新输入
            printf("select error!!!\n");
            printf("Please afrsh input :");
            scanf("%d", &select);
            break;
        }
    } while (select);
    return 1;
}
