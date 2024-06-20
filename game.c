#include "game.h"

int main()
{
    int choose = 1;
    Display_menu(); // 显示棋盘
    printf("Your choose is :");
    scanf("%d", &choose);
    do
    {

        switch (choose)
        {
        case 0:
            printf("Exit succefssful!\n");
            break;            
        case 1:
            Run_Game();
            scanf("%d", &choose);
            break;
        default:
            printf("Your input error,Please afrsh input!!!\n");
            printf("Your choose is :");
            scanf("%d", &choose);
            break;
        }
    } while (choose);

    printf("----------------Game Over----------------\n");

    system("pause");
    return 0;
}
