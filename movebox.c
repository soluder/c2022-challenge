#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

int main(int argc, const char* argv[])
{
	char map[8][8] = {
		{0,0,1,1,1,1,0,0},
		{0,0,1,4,4,1,0,0},
		{0,1,1,0,4,1,1,0},
		{0,1,0,0,3,4,1,0},
		{1,1,0,3,0,0,1,1},
		{1,0,0,1,3,3,0,1},
		{1,0,0,2,0,0,0,1},
		{1,1,1,1,1,1,1,1}
	};
	char m_x = 6, m_y = 3;
	int step = 0;

	for (;;)
	{
		int cnt = 0;
		int x = 0, y = 0;
		system("cls");
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				switch (map[i][j])
				{
				case 0: printf("  "); break;
				case 1: printf("# "); break;
				case 2: printf("@ "); break;
				case 3: printf("$ "); break;
				case 4: printf("0 "); break;
				case 6: printf("@ "); break;
				case 7: printf("$ "); cnt++; break;
				}
			}
			printf("\n");
		}
		if (4 == cnt)
		{
			printf("游戏结束，共走了%d步\n", step);
			break;
		}
		switch (getch())
		{
		case 'w'://上
			x--;
			break;
		case 's'://下
			x++;
			break;
		case 'a':
			y--;
			break;
		case 'd'://左
			y++;
			break;
		}
		if (0 == map[m_x + x][m_y + y] || 4 == map[m_x + x][m_y + y])
		{
			map[m_x + x][m_y + y] += 2;
			map[m_x][m_y] -= 2;
			m_x += x;
			m_y += y;
			step++;
		}
		else if (3 == map[m_x + x][m_y + y] || 7 == map[m_x + x][m_y + y])
		{
			if (0 == map[m_x + 2 * x][m_y + 2 * y] || 4 == map[m_x + 2 * x][m_y + 2 * y])
			{
				map[m_x + 2 * x][m_y + 2 * y] += 3;
				map[m_x + x][m_y + y] -= 1;
				map[m_x][m_y] -= 2;
				m_x += x;
				m_y += y;
				step++;
			}
		}
	}
}
