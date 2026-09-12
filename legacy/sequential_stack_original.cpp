#include <stdio.h>
#include <stdlib.h>
//建立顺序栈，输入 10 个数，依次入栈，输出栈顶元素，再依次出栈打印输出。
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
//顺序栈结构类型定义
#define STACK_INIT_SIZE 100 // 栈存储空间的初始分配量
#define STACKINCREMENT 10 // 栈存储空间的分配增量
typedef int SElemType;

typedef struct 
{
	SElemType *base; //栈空间基址
	SElemType *top;//栈顶指针
	int stacksize; //当前分配的栈空间大小
} SqStack;

//顺序栈初始化函数定义
Status InitStack_Sq(SqStack &S) 
{ //开辟，如果开辟不成功，头尾指针在一起，空间总量
	S.base = (SElemType *)malloc(STACKINCREMENT * sizeof(SElemType));
	if (!S. base) exit(OVERFLOW);   //如果开辟的空间是0，则分配空间失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

//顺序栈销毁函数定义
Status DestroyStack_Sq(SqStack &S ) 
{ //如果没空间return ERROR，释放，头尾指针等于NULL，空间总量为0
	if (!S.base)	return ERROR; //尚未分配空间
	free(S.base);
	S.base = S.top = NULL; //null是不行的，必须是NULL才行，不然会出错！
	S.stacksize = 0;
	return OK;
}
//进顺序栈函数定义
Status Push(SqStack &S, SElemType e) 
{ //如果栈已满(realloc，开辟失败，栈顶指针从原来的空间总量开始s.base+s.stacksize,新的空间总量),栈顶指针所指向内存赋值，栈顶指针跳下一位，
	if (S.top - S.base >= S.stacksize) 
	{
		S.base = (SElemType *)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType)); //本质是复制数据到一片新空间
		if (! S. base) 
exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
		//TODO
	}
	*S.top = e;
	S.top++;
	return OK;
}
//取顺序栈顶元素函数定义
Status GetTop_Sq(SqStack S, SElemType &e) 
{ //取栈与出栈类似，都是：判空，赋值栈顶（S.top-1）给e
	if (S.base == S.top) 
return ERROR;
	e = *(S.top - 1);
	return OK;
}
//出顺序栈函数定义
Status Pop(SqStack &S, SElemType &e ) 
{   //取栈与出栈类似，都是：判空，赋值栈顶（S.top-1）给e
	if (S.base == S.top)
return ERROR;
	--S.top;
	e = *S.top;
	return OK;
}
int main() 
{
	SqStack S;
	SElemType e;
	SElemType top;//变量定义
	InitStack_Sq(S);//初始化栈函数调用
	for (SElemType i = 0; i < 10; i++) 
    {
		scanf("%d", &e);
		Push(S, e);
	}//顺序输入 10 个数，入栈
	GetTop_Sq(S, top);
	printf("栈顶元素为：%d  ", top);	//取顺序栈顶元素
	printf("该栈的打印情况如下：");
	for (SElemType i = 0; i < 10; i++) 
    {
		Pop(S, e);
		printf("%d  ", e);
	}//出顺序栈，依次打印输出 10 个数
	DestroyStack_Sq(S);//顺序栈销毁函数调用
	return 0;
}
