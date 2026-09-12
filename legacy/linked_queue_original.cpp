#include <stdio.h>
#include <stdlib.h>
//建立链表队列，输入 10 个数，依次入队，输出队头元素，再依次出队打印输出。
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
//链队列结构类型定义
typedef int QElemType;
//开辟失败的用exit(ERROR/OVERFLOW);，为空的用return ERROR(链表);
typedef struct Qnode 
{
	//链队列结点的类型定义
	QElemType data;
	struct Qnode *next; 
} QNode, *QueuePtr;

typedef struct 
{
	//链队列的"表头"结点的的类型定义
	QueuePtr front; //队头指针，指向链表的头结点
	QueuePtr rear; //队尾指针，指向队尾结点
} LinkQueue;

//链队列初始化函数定义
Status InitQueue(LinkQueue &Q) 
{    //开辟空间（结点类型），如果开辟失败，表尾（Q.front->next=NULL）
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode)); //开辟空间结点类型的
	if (!Q.front) 
	exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}
//链队列销毁函数定义
Status DestroyQueue(LinkQueue &Q) 
{ //当有Q.front时，Q.rear指向Q.front的后一个元素，再释放Q.front,两者再重新指向相同位置
	while (Q.front) 
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
		//TODO
	}
	return OK;
}
//链队列插入队尾元素函数定义
Status EnQueue(LinkQueue &Q, QElemType e) 
{ //定义一个结点p，给p开辟空间，如果开辟失败，赋值，将p指向连好，Q.rear永远指最后一个
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) 
	exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}
//取链队列队头元素函数定义
Status GetHead(LinkQueue Q, QElemType &e) 
{ //链表判空，赋值
	if (Q.front == Q.rear) 
	return ERROR;
	e = Q.front->next->data; //队头元素我们无从知道，只能从指向头结点的指针入手
	return OK;
}
//链队列删除队头元素函数定义
Status DeQueue(LinkQueue &Q, QElemType &e) 
{ //定义指针p，判空，p指向头元素（不是头结点），赋值，头元素指向第二个元素，若链表只有头元素则置空，释放p
	QueuePtr p;
	if (Q.front == Q.rear) 
	return ERROR;
	p = Q.front->next; //p指针指向了头元素
	e = p->data;
	Q.front->next = p->next; //Q.front的下一个元素（头元素）指向指向p的下一个元素（第二个元素）
	if (Q.rear == p) 
	{   //队列中只有一个元素且出去了
		Q.front = Q.rear; //置空链表
	}
	free(p);
	return OK;
}
int main() 
{
	LinkQueue Q;//变量定义 
	QElemType head, e;
	InitQueue(Q);//初始化链队列函数调用
	for (QElemType i=0; i < 10; i++) 
	{
		scanf("%d", &e);
		EnQueue(Q, e);
	}//顺序输入 10 个数，入队
	GetHead(Q, head); //取链队列队头元素函数调用
	printf("此时队头元素为：%d\n",head);
	printf("该队列的打印：");
	for (QElemType i=0; i < 10; i++) 
	{
		DeQueue(Q, e);
		printf("%d ", e);
	}//出链队列，依次打印输出 10 个数
	DestroyQueue(Q);//链队列销毁函数调用*/
	return 0;
}
