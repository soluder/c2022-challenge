//
// Created by 旺仔 on 2022/10/29.
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void encrypt(char [40],int [40]);
void decrypt(char [40],int [40]);
int main()
{
    int a[40];
    char str[40];
    srand(time(NULL));
    for(int i=0;i<40;i++)
    {
        a[i]=rand();
    }
    scanf("%s",str);
    encrypt(str,a);
    decrypt(str,a);

}
void encrypt(char str[40],int a[40])
{
    printf("加密后的字符串为：");
    for(int i=0;i<40;i++)
    {
        str[i]=str[i]+a[i];
        printf("%c",str[i]);
    }

}
void decrypt(char str[40],int a[40])
{
    printf("解密后的字符串为：");
    for(int i=0;i<40;i++)
    {
        str[i]=str[i]-a[i];
        printf("%c",str[i]);
    }

}

