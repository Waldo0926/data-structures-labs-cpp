//二叉树的二叉链表结构下的建立和遍历
//首先理解三种遍历的算法，然后理解二叉链表的建立
//课件的幻灯片第38张，这棵二叉树的先序建立为例，输入序列：ABD#F###CE###
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
typedef char Datatype;
typedef struct Node
{	Datatype data;
	struct Node *lchild;
    struct Node *rchild;
}BiTNode,*BiTree;

//先序建立二叉树
Status CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')T=NULL;
    else{
        T = (BiTree)malloc(sizeof(BiTNode));
		if (T==NULL)
			exit(OVERFLOW);
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return OK;
}

//先序遍历二叉树
Status PreOrderTraverse(BiTree T)
{
    if(T){
       printf("%c",T->data);
       PreOrderTraverse(T->lchild);
       PreOrderTraverse(T->rchild);
    }
	return OK;
}
 
//中序遍历
Status InOrderTraverse(BiTree T)
{
    if(T){
       InOrderTraverse(T->lchild);
       printf("%c",T->data);
       InOrderTraverse(T->rchild);
    }
   return OK;
}
//后序遍历
Status PostOrderTraverse(BiTree T)
{
    if(T){
       PostOrderTraverse(T->lchild);
       PostOrderTraverse(T->rchild);
       printf("%c",T->data);
    }
    return OK;
}
void main()
{
    BiTree T;
    CreateBiTree(T);//建立
    PreOrderTraverse(T);
	printf("\n");
	InOrderTraverse(T);
	printf("\n");
    PostOrderTraverse(T);
	printf("\n");

}