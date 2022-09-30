#include<stdio.h>
int main()
{
    int count=0,flag=1;
    int a[100];
    for(int i=1;i<101;i++)//得到素数数组，便于计算
    {
        flag =1;
       for(int t=2;t<i;t++)
       {
           if(i%t==0)
           {
               flag = 0;
           }
       }
       if(flag==1)
       {
           a[count++]=i;
       }
    }
    for(int i=2;i<101;i+=2)//验证猜想
    {
      for(int x=0;x<count;x++)
      {
          for(int y=0;y<count;y++)  
          {
              if(i==a[x]+a[y])
              {
                  printf("%d = %d + %d\n",i,a[x],a[y]);
                  break;
              }
          }
      }
    }
    }
