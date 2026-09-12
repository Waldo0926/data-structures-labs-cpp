//二叉树的二叉链表结构下线索化和遍历
//教材127页图6.8b二叉树的先序建立为例，输入序列：ABC##DE#G##F###
//注意线索二叉树的数据结构有所变化，结构体中多了两个成员
//在这个二叉树基础上进行线索化：利用pre(前驱结点指针)和T(当前结点指针)之间的关系来加
//如果T所指向的结点没有左孩子的话，那么Ltag为thread,并且当前结点的前驱就是pre所指，
//如果pre所指向的结点没有右孩子的话，那么Rtag为thread,并且前驱结点的后继就是T所指。
//最后再遍历线索化二叉树
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef enum{link,thread}PointerTag;  //link=0, thread=1
typedef char Datatype;
typedef struct Node
{	Datatype data;
	struct Node *lchild;
    struct Node *rchild;
    PointerTag Ltag;
	PointerTag Rtag;
}BiTNode,*BiTree;
BiTree pre;

//先序建立二叉树
Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')T=NULL;
    else{
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = ch;
		T->Ltag=link;
		T->Rtag=link;
       CreateBiTree(T->lchild);
       CreateBiTree(T->rchild);
    }
	return OK;
}

//中序线索化二叉树的函数
Status Inthread(BiTree p)
{
	//其中pre始终指向刚访问过的结点，其初始值为NULL
	if(p)
	{
		Inthread(p->lchild);//线索化左子树
		//中间这一部分是针对中间结点进行的操作
        if (p->lchild==NULL)
		{
			p->Ltag=thread;
			p->lchild=pre;
		}
		if (pre->rchild==NULL)
		{
			pre->rchild=p;
			pre->Rtag=thread;
		}
		pre=p;//保证pre始终指向前驱结点
        Inthread(p->rchild);//线索化右子树
	}
	return OK;

}
//将二叉树加一个头结点,中序遍历时将其线索化
Status InOrderThreading(BiTree &Thrt,BiTree T)
{
	Thrt=(BiTree)malloc(sizeof(BiTNode));
	Thrt->Ltag=link;
	Thrt->Rtag=thread;
	Thrt->rchild=Thrt;
	if (T==NULL)
		Thrt->lchild=Thrt;//若二叉树为空,则左指针回指
	else
	{
		Thrt->lchild=T;
		pre=Thrt;
		Inthread(T);
		pre->rchild=Thrt;
		pre->Rtag=thread;
		Thrt->rchild=pre;
	}
	return OK;

}
//遍历线索化二叉树
Status InOrderTraverse(BiTree T) 
{
   BiTree p;
   p=T->lchild;
   while(p!=T)  
   {   //   空树或遍历结束时，p= =T
       while(p->Ltag==link)  
		   p= p->lchild;                   //找到最左下结点；访问之
       printf("%c",p->data);                                              
       while (p->Rtag==thread && p->rchild!=T)  
	   {     // 若p所指结点的右孩子域为线索且不是最后一个结点
		   p=p->rchild;    
		   printf("%c",p->data);                     //访问后继结点
       }
      p=p->rchild;
    } 
   return OK;
    
}



void main()
{
    BiTree Thrt,T;
    CreateBiTree(T);//建立
    InOrderThreading(Thrt,T);
	InOrderTraverse(Thrt);
	printf("\n");

}