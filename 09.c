#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
int main(void)
{
   
    char map[50][50] = {
                        "######",
                        "#O #  ",
                        "# ## #",
                        "#  # #",
                        "##   #",
                        "######",
    };
    int i, x, y, p, q;//x,y起点
                      //p,q终点
    int ch;
    x = 1; y = 1; p = 1; q = 5;
    for (i = 0; i < 6; i++)
        puts(map[i]);
    while (x != p || y != q)
    {
        ch = _getch();
        if (ch == 's')
        {
            if (map[x + 1][y] != '#')
            {
                map[x][y] = ' ';
                x++;
                map[x][y] = 'O';
            }
        }
        if (ch == 'w')
        {
            if (map[x - 1][y] != '#')
            {
                map[x][y] = ' ';
                x--;
                map[x][y] = 'O';
            }
        }
        if (ch == 'a')
        {
            if (map[x][y - 1] != '#')
            {
                map[x][y] = ' ';
                y--;
                map[x][y] = 'O';
            }
        }
        if (ch == 'd')
        {
            if (map[x][y + 1] != '#')
            {
                map[x][y] = ' ';
                y++;
                map[x][y] = 'O';
            }
        }
        system("cls");
        for (i = 0; i < 6; i++)
            puts(map[i]);
    }
    system("cls");
    printf("你赢了!\n");
    return 0;
}