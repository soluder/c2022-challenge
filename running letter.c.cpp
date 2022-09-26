#include<stdio.h>
#include<windows.h>
int main()
{
	const int L=0,R=118;
	int flag=1,cur=0;
	while(1)
	{
		for(int i=0;i<=cur;i++)
		{
			printf(" ");
		}
		cur += flag;
		printf("t");
		if(cur==L||cur==R)
		{
			flag *= -1;
		}
		Sleep(100);
		system("cls");
	}
	return 0;
}
