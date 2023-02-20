#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Date{
    int year;
    int month;
    int day;
};
struct Ware{
    char type[40];
    char count[40];
    struct Date date;
    struct Ware* next;
};
//录入书籍信息
void getinput(struct Ware* ware)
{
    printf("please input the type:");
    scanf("%s",ware->type);
    printf("please input the count:");
    scanf("%s",ware->count);
    printf("please input the date:");
    scanf("%d.%d.%d",&ware->date.year,&ware->date.month,&ware->date.day);//注意加& 
}
//添加新书
void addware(struct Ware** library)
{
    struct Ware* ware;
    static struct Ware* temp;
    ware = (struct Ware*)malloc(sizeof(struct Ware));
    getinput(ware);
    if(*library==NULL)
    {
        *library = ware;
        ware->next = NULL;
    }
    else{
        temp -> next = ware;
        ware -> next = NULL;
    }
}
//打印图书馆
void printware(struct Ware*ware)
{
    int count;
    while(ware!=NULL)
    {
        printf("ware%d\n:",count++);
        printf("type:%s\n",ware->type);
        printf("count:%s\n",ware->count);
        printf("date:%d.%d.%d",ware->date.year,ware->date.month,ware->date.day);
        ware=ware->next;
        
    }
}
void searchware(struct Ware* ware)
{
    char str[40];
    printf("请输入货物型号：\n");
    scanf("%s",str);
    while(ware!=NULL)
    {
        if(strcmp(ware->type,str)==0||strcmp(ware->count,str)==0)
        {
            printware(ware);
        }
        ware = ware->next;
    }
}
int main()
{
    char ch;
    struct Ware* warehouse =NULL;
    while(1){
        printf("是否需要录入货物（Y/N）：");
        do{
            ch = getchar();
        }while(ch!= 'Y'&&ch!='N');
        if(ch=='Y')
        {
            addware(&warehouse);
        }else{
            break;
        } 
    }
    printware(warehouse);
 while(1){
        printf("是否需要查找货物（Y/N）：");
        do{
            ch = getchar();
        }while(ch!= 'Y'&&ch!='N');
        if(ch=='Y')
        {
            searchware(warehouse);
        }else{
            break;
        } 
    }
    return 0;
    
}

