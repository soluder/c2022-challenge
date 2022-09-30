#include<stdio.h>
#include <stdlib.h>
#include<time.h>   
#include<math.h>
int main() {
	int begintime,endtime;
	int flag=1;
	begintime=clock();	
	for(int i=2;i<1000;i++)
	{
		flag =1;
		for(int t=2;t<sqrt (i);t++)
		{
			if(i%t==0)
			{
				flag = 0;
			}
		}
		if(flag==1)
			{
			printf("%d ",i);
			}
	}
	
	endtime = clock();	
	printf("\n\nRunning Time£º%dms\n", endtime-begintime);
	return 0;
}
