#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
struct repo* repo1 = NULL;
struct repo* repo2 = NULL;
int AIresult[2];//返回值
pthread_mutex_t lock;//加锁
int* AI(int[320][320],int X,int Y);

void PushRepo(struct repo**, int, int, int);
void ChangeRepo(struct repo*,int,int,int);
void DeleteRepo(struct repo**, int, int);
struct repo* createRepo(struct repo* repo);
struct repo* reverse(struct repo* head);
struct repo* getTail(struct repo* L);
struct repo* Quicksort(struct repo** listHead, struct repo** listTail);
int evaluate(int pawn[320][320], int xPos, int yPos);
int IniEvaluate(int pawn[320][320], int xPos, int yPos);

int Getmax1(int pawn[320][320], struct repo* repo,struct repo* revrepo, int xPos, int yPos, int alpha, int beta);
int Getmin1(int pawn[320][320], struct repo* repo,struct repo* revrepo, int xPos, int yPos, int alpha, int beta);
int Getmax2(int pawn[320][320], struct repo* repo,struct repo* revrepo, int xPos, int yPos, int alpha, int beta);
int Getmin2(int pawn[320][320], struct repo* repo,struct repo* revrepo, int xPos, int yPos, int alpha, int beta);
int Evaluate(int pawn[320][320], int xPos,int yPos);
//多线程
void* multithread(void* args);


//构建一个仓库储存每层每个空位的价值，以便尽早剪枝，由于需要频繁删改，所以使用链表
struct repo {
	int xPos;
	int yPos;
	int value;
	struct repo* next;
};
struct arg {
	int (*pawn)[320];
	struct repo* repo;
	int xPos;
	int yPos;
};

int* AI(int pawn[320][320],int X,int Y)
{
	
	
	int left = 20;//棋盘位置
	int right = 300;
	int bottom = 300;
	int top = 20;
	int width = 20;
	int value = 0;
	int alpha = -9999999;
    int beta = 99999999;
	
	struct repo* current=NULL;
	

//根节点，第零层
//第一次调用AI函数时初始化仓库
	if (repo1 == NULL)
	{
		int flag = -1;
		int i = 160;
		int j = 160;
		if (pawn[i][j] == 0)//对空白位置打分
		{
			value = IniEvaluate(pawn,i, j);
			PushRepo(&repo1, i, j, value);
			PushRepo(&repo2, i, j, value);
			if (value > alpha)
			{
				alpha = value;
				AIresult[0] = i;
				AIresult[1] = j;
			}
		}
		for (int count = 1; count < 15; count++)//从棋盘中间开始遍历
		{
			for (int m = 0; m < count; m++)
			{
				j += (flag * width);
				if (pawn[i][j] == 0)//对空白位置打分
				{
					value = IniEvaluate(pawn, i, j);
					PushRepo(&repo1, i, j, value);
					PushRepo(&repo2, i, j, value);
					if (value > alpha)
					{
						alpha = value;
						AIresult[0] = i;
						AIresult[1] = j;
					}
				}
			}
			for (int m = 0; m < count; m++)
			{
				i += (flag * width);
				
				if (pawn[i][j] == 0)//对空白位置打分
				{
					value = IniEvaluate(pawn, i, j);
					PushRepo(&repo1, i, j, value);
					PushRepo(&repo2, i, j, value);
					if (value > alpha)
					{
						alpha = value;
						AIresult[0] = i;
						AIresult[1] = j;
					}
				}
	}
			flag *= -1;


		}
		for (int i = 300, j = 280; j > 0; j -= 20)
		{
			if (pawn[i][j] == 0)//对空白位置打分
			{
				value = IniEvaluate(pawn, i, j);
				PushRepo(&repo1, i, j, value);
				PushRepo(&repo2, i, j, value);
				if (value > alpha) 
				{
					alpha = value;
					AIresult[0] = i;
					AIresult[1] = j;
				}
			}
		}
		
		
	}
	else {
		//pthread_t threads[10];
		int count = 0;
		//pthread_mutex_init(&lock, NULL);
		DeleteRepo(&repo1,X,Y);
		DeleteRepo(&repo2,X,Y);//删除玩家下过的位置
		struct repo* temp = repo1;
		//struct arg* multiarg = (struct arg*)malloc(sizeof(struct arg));
		while (temp != NULL)
		{
			temp->value=IniEvaluate(pawn, temp->xPos, temp->yPos);
			temp = temp->next;
		}
		struct repo* listTail = getTail(repo1);
		Quicksort(&repo1, &listTail);
	    listTail = getTail(repo2);
		Quicksort(&repo2, &listTail);
		repo2 = reverse(repo2);
		current = repo1;
		//multiarg->pawn = pawn;
		//multiarg->repo = repo1;
		while (current != NULL)
		{
			if (count == 9)
			{
				break;
			}
			/*multiarg->xPos = current->xPos;
			multiarg->yPos = current->yPos;*/
			//pthread_create(&threads[count], NULL, multithread,(void*)multiarg);
			value=Getmin1(pawn, repo1, repo1, current->xPos, current->yPos, alpha, beta);
			if (value > alpha)
			{
				alpha = value;
				AIresult[0] = current->xPos;
				AIresult[1] = current->yPos;
			}
			current = current->next;
			count++;
		}	
		/*for (int i = 0; i < 9; i++)
		{
			pthread_join(threads[i],NULL);

		}*/
		

	}
	
	DeleteRepo(&repo1,AIresult[0],AIresult[1]);
	DeleteRepo(&repo2,AIresult[0],AIresult[1]);
	
 
	


	
return AIresult;
}
int Getmin1(int pawn[320][320], struct repo* repo,struct repo* revrepo, int xPos, int yPos, int alpha, int beta)
{
	pawn[xPos][yPos] = 1;
	struct repo* current=repo;
	int value;
	while(current!=NULL)
	{
		if (pawn[current->xPos][current->yPos] == 0)
		{
			value = Getmax2(pawn, revrepo,repo ,current->xPos, current->yPos, alpha, beta);
			if (value <beta)
			{
				beta = value;
			}
			if (alpha >= beta)
			{
				goto OK;
			}
		}
		current = current->next;
    }
OK:
	pawn[xPos][yPos] = 0;
	return beta;

}
int Getmax2(int pawn[320][320], struct repo* repo,struct repo* revrepo, int xPos, int yPos, int alpha, int beta)
{
	pawn[xPos][yPos] = -1;
	struct repo* current = repo;
	int value;
	while (current != NULL)
	{
		if (pawn[current->xPos][current->yPos] == 0)
		{
        value = Getmin2(pawn,revrepo,repo, current->xPos, current->yPos, alpha, beta);
		if (value > alpha)
		{
			alpha = value;
		}
		if (alpha >= beta)
		{
			goto OK;
		}
		}
		
		current = current->next;
	}
OK:
	pawn[xPos][yPos] = 0;
	return alpha;
}
int Getmin2(int pawn[320][320], struct repo* repo,struct repo* revrepo, int xPos, int yPos, int alpha, int beta)
{
	pawn[xPos][yPos] = 1;
	struct repo* current = repo;
	int value;
	while (current != NULL)
	{
		if (pawn[current->xPos][current->yPos] == 0)
		{
			value =Evaluate(pawn,current->xPos,current->yPos);
			if (value < beta)
			{
				beta = value;
			}
			if (alpha >= beta) 
			{
				goto OK;
			}
		}

		current = current->next;
	}
OK:
	pawn[xPos][yPos] = 0;
	return beta;
}
int Evaluate(int pawn[320][320],int xPos,int yPos)
{
	pawn[xPos][yPos] = -1;
	int left = 20;//棋盘位置
	int right = 300;
	int bottom = 300;
	int top = 20;
	int width = 20;
	int value = 0;
	int clonepawn[320][320];
	for (int i = left; i <= right; i += width)
	{
		for (int j = top; j <= bottom; j += width)
		{
			clonepawn[i][j] = -pawn[i][j];
		}
	}
	for (int i = left; i <= right; i += width)
	{
		for (int j = top; j <= bottom; j += width)
		{

			value += evaluate(pawn, i, j);
			value -= evaluate(clonepawn, i, j);


		}
	}
	pawn[xPos][yPos]=0;
	return value;
}
int IniEvaluate(int pawn[320][320],int xPos, int yPos)
{
	pawn[xPos][yPos] = 1;
	
	int left = 20;//棋盘位置
	int right = 300;
	int bottom = 300;
	int top = 20;
	int width = 20;
	int value = 0;
	int clonepawn[320][320];
	for (int i = left; i <= right; i += width)
	{
		for (int j = top; j <= bottom; j += width)
		{
			clonepawn[i][j] = -pawn[i][j];
		}
	}
	for (int i = left; i <= right; i += width)
	{
 		for (int j = top; j <= bottom; j += width)
		{
			
                value += evaluate(pawn, i, j);
				value -= evaluate(clonepawn, i, j);
			
			

		}
	}
	
	pawn[xPos][yPos] = 0;
	return value;
}











struct repo* createRepo(struct repo* repo)
{
	struct repo* new = NULL;
	new = (struct repo*)malloc(sizeof(struct repo));
	new->value = repo->value;
	new->xPos = repo->xPos;
	new->yPos = repo->yPos;
	return new;
}

void PushRepo(struct repo** repo, int xPos, int yPos, int value)
{
	struct repo* new=NULL;
	struct repo* previous=NULL;
	struct repo* current=*repo;
	new = (struct repo*)malloc(sizeof(struct repo));
	new->xPos = xPos;
	new->yPos = yPos;
	new->value = value;
	while (current != NULL && value < current->value)
	{
		previous = current;
		current = current->next;
	}
	new->next = current;
	if (previous == NULL)
	{
		*repo = new;
	}
	else {
		previous->next = new;
	}
}
void ChangeRepo(struct repo* repo, int xPos, int yPos, int value)
{
	struct repo* temp = repo;
	while (temp != NULL)
	{
		if (temp->xPos == xPos && temp->yPos)
		{
			temp->value = value;
			break;
		}
		temp = temp->next;
	}
};

void DeleteRepo(struct repo** repo, int xPos, int yPos)
{
	struct repo* temp = *repo;
	struct repo* previous = NULL;
	while (temp != NULL)
	{

		if (temp->xPos == xPos && temp->yPos == yPos)
		{
			break;
		}
		previous = temp;
		temp = temp->next;
	}
	if (previous == NULL)
	{

		*repo = temp->next;
	}
	else 
	{

		previous->next =temp->next;
	}
}

struct repo* getTail(struct repo* L)
{
	while (L->next)
		L = L->next;
	return L;
}
struct repo* Quicksort(struct repo** listHead,struct repo** listTail)
{
	struct repo* current;
	struct repo* lessHead = NULL, * lessTail = NULL, * moreHead = NULL, * moreTail = NULL;
	current = (*listHead)->next;//每次取首节点为枢纽，current指向第二个节点用于遍历
	if ((*listHead)->next != NULL)//当链表节点数不为1时(说明链表未排好序)
	{
		for (current = (*listHead)->next; current; current = current->next)
		{
			if (current->value >= (*listHead)->value)
			{
				if (lessHead == NULL)
					lessHead = current;
				else
					lessTail->next = current;
				lessTail = current;
			}//current结点key小于枢纽key时放入less链表
			else
			{
				if (moreHead == NULL)
					moreHead = current;
				else
					moreTail->next = current;
				moreTail = current;
			}//current结点key大于枢纽key时放入more链表
		}
		//根据枢纽结点将T链表分为less和more两个链表
		if (moreTail)
			moreTail->next = NULL;
		if (lessTail)
			lessTail->next = NULL;
		//将more链表尾结点next域置空
		if (moreHead != NULL)
		{
			moreTail->next = NULL;
			Quicksort(&moreHead, &moreTail);
			(*listHead)->next = moreHead;
			*listTail = moreTail;
		}
		//若moreHead不空，则current为more链表的尾结点，对more链表进行递归处理,将more链表接在枢纽节点后
		else
		{
			(*listHead)->next = NULL;
			*listTail = *listHead;
		}
		//若moreHead为空，则只有less链表(即结点key全小于枢纽)，将枢纽结点接在less节点后
		if (lessHead != NULL)
		{
			lessTail->next = NULL;
			Quicksort(&lessHead, &lessTail);
			lessTail->next = *listHead;
			*listHead = lessHead;
		}
		//若lesseHead不空，对less链表进行递归处理，再将枢纽节点接在less链表后
		else
		{
			lessHead = *listHead;
		}
		//若lesseHead为空，则枢纽结点作为首节点
		return lessHead;
	}
	else
		return *listHead;
}
struct repo* reverse(struct repo* head)
{
	
		struct repo* pre = NULL;   //初始化当前的前趋为NULL
		struct repo* nextp = NULL;   //定义指针nextp用于存放当前节点的后继
		while (head->next != NULL) {      //如果当前节点存在后继则循环，更改其后继指针为他的前趋指针    
			nextp = head->next;            //保存当前节点的后继节点指针
			head->next = pre;            // 将当前节点的后继节点指针更改为他的前趋节点指针
			pre = head;                    //将前趋节点指针将当前节点的指针
			head = nextp;                //进入下一节点
		}
		//使用head->next是否为NULL来判断是否进入了最后一个节点，循环中还没有更改最后一个节点的后继指针
		if (head->next == NULL)
			head->next = pre;         //更改最后一个节点的后继指针
		return head;    //返回反转后的节点指针
}
//void* multithread(void* args)
//{
//	struct arg* multiarg = (struct arg*)args;
//	int value = Getmin1(multiarg->pawn,multiarg->repo,multiarg->repo,multiarg->xPos,multiarg->yPos,alpha,beta);
//	//pthread_mutex_lock(&lock);
//	if (value > alpha)
//	{
//		alpha = value;
//		AIresult[0] = multiarg->xPos;
//		AIresult[1] = multiarg->yPos;		
//	}
//	//pthread_mutex_unlock(&lock);
//};
