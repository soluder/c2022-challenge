#include<stdio.h>
int hanoi(int,char,char,char);
int hanoi(int num,char x,char y,char z)
{
    static int count=0;
    if(num==1){
        printf("%c-->%c\n",x,z);
        count++;
    }else{
        hanoi(num-1,x,z,y);
        printf("%c-->%c\n",x,z);
        count++;
        hanoi(num-1,y,x,z);
    }
    return count;
}
int main()
{
    int num;
    printf("请输入汉诺塔的层数： ");
    scanf("%d",&num);
    printf("一共需要%d步",hanoi(num,'x','y','z'));
    return 0;
}
