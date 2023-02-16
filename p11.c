#include<stdio.h>
#include<stdlib.h>
typedef struct nodelist
{
    int data;
    int count;
    struct nodelist* next;
}*list;
list nodelist = NULL;
void Create(list head);
void Print(list head);
void Reverse(list head);
int GetNode1(list head);
int GetNode2(list head);

int main()
{
    list head;
    head = (list)malloc(sizeof(struct nodelist));
    head->next = NULL;
    Create(head);
    Print(head);
    Reverse(head);
    Print(head);
    return 0;
}
void Create(list head)
{
    list p, rear = head;
    puts("输入若干整数，输入-1表示输入结束");
    int num;
    scanf("%d", &num);
    while (num != -1)
    {
        p = (list)malloc(sizeof(nodelist));
        p->data = num;
        rear->next = p;
        rear = p;
    }
    rear->next = NULL;
}

void Print(list head)
{
    list p = head->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}
void Reverse(list head)
{
    if (head->next == NULL)
    {
        return;
    }
    list cur = head->next;
    list next = NULL;
    list ReverseHead = head;
    while (cur != NULL)
    {
        next = cur->next;
        cur->next = ReverseHead->next;
        ReverseHead->next = cur;
        cur = next;
    }
    head->next = ReverseHead->next;
}

int GetNode1(list head)
{
    int cnt = 0;
    while (head->data != 5)
    {
        head = head->next;
        cnt++;
    }
    return cnt;
}
int GetNode2(list head)
{
    static int cnt1 = 0;
    int cnt2 = 0;
    while (cnt2 < 2)
    {
        while (head->data != 5)
        {
            head = head->next;
            cnt1++;
        }
        cnt2++;
    }
    return cnt1;
}
