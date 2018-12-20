/*
    井字棋
*/
#include <stdio.h>

//棋盘
char Board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};

//打印棋盘状态
void PrintBoard()
{
    // printf("\033[2J"); //清屏
    // printf("\n\n");
    printf("   0─1─2  \n");
    printf(" ┌─┬─┬─┬─┐\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d├─", i);
        for (int j = 0; j < 3; j++)
            printf("%c─", Board[i][j]);
        printf("┤\n");
    }

    printf(" └─┴─┴─┴─┘\n");
}

//返回0表示胜负未分，'O'表示O赢了，'X'表示X赢了
int model[8][3][2] = {
    {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}},
    {{2, 0}, {2, 1}, {2, 2}}, //横

    {{0, 0}, {1, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}}, //竖

    {{0, 0}, {1, 1}, {2, 2}},
    {{0, 2}, {1, 1}, {2, 0}}, //对角
};
int existWinner(char player)
{
    for (int n = 0; n < 8; n++)
    {
        if (Board[model[n][0][0]][model[n][0][1]] == player &&
            Board[model[n][1][0]][model[n][1][1]] == player &&
            Board[model[n][2][0]][model[n][2][1]] == player)
            return 1;
    }
    return 0;
}

int flag = 1, turn = 0;
//重置棋盘
void initBoard()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            Board[i][j] = ' ';
    turn = 0;
}

int isSum()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (Board[i][j] == ' ')
                return 0;
    return 1;
}

int AI(int *x, int *y, char c)
{
    if (isSum())
        return 0;
    int max = -100000;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (Board[i][j] == ' ')
            {
                Board[i][j] = c;
                if (existWinner(c))
                {
                    *x = i;
                    *y = j;
                    max = 10000;
                }

                int xx, yy;
                int score = -AI(&xx, &yy, c == 'O' ? 'X' : 'O');
                if (max < score)
                {
                    max = score;
                    *x = i;
                    *y = j;
                }
                Board[i][j] = ' ';
            }
    return max;
}

int main(void)
{
    while (1)
    {
        //打印棋盘
        PrintBoard();

        int x, y;
    INPUT: //用户输入并落子
        if (flag)
            scanf("%d%d", &x, &y);
        else
            printf("%d\n", AI(&x, &y, 'X'));
        // printf("%d, %d", x, y);
        if (Board[x][y] == ' ')
        {
            Board[x][y] = flag ? 'O' : 'X';
            flag = !flag;
        }
        else
        {
            printf("非法的落子位置,请重新输入\n");
            goto INPUT;
        }

        turn++;

        if (existWinner('O'))
            printf("O方获胜！\n");
        else if (existWinner('X'))
            printf("X方获胜！\n");
        else if (turn >= 9)
            printf("平局！\n");
        else
            continue; //如果棋局没有结束则继续
        initBoard();  //如果棋局结束了则重置棋盘
    }
}
