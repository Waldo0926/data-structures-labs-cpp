#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20
//typedef VertexType int;
typedef enum {DG, DN, AG, AN} GraphKind;

//边（弧）结点的类型定义
typedef struct ArcNode
{
    int adjvex; //边（弧）的另一顶点的在数组中的位置
    struct ArcNode *nextarc; //指向下一条边（弧）结点的指针
} ArcNode;

//顶点结点和数组的类型定义
typedef struct Vnode
{
    int data; //顶点信息
    ArcNode * firstarc; //指向关联该顶点的边（弧）链表
} Vnode, AjList[MAX_VERTEX_NUM];

//图的定义
typedef struct
{
    AjList vertices;//
    int vexnum, arcnum; //图的当前顶点数和弧数
    GraphKind kind; //图的种类标志 kind为枚举类型变量
} ALGraph;

int visited[MAX_VERTEX_NUM]; //visited数组作为一个标志数组，用来判断顶点是否遍历过

void create(ALGraph &g)
{
    int n, i, j, sum = 0, count, t;
    int x, k;
    ArcNode *p; //定义一个工作指针
    printf("请输入图的顶点数目：");
    scanf("%d", &n);
    printf("请输入%d 个顶点的编号，空格分隔：", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &g.vertices[i].data);
        g.vertices[i].firstarc = NULL;
    }
    printf("请按照顶点输入顺序，依次输入和该点有边相连的顶点信息：\n");
    for (i = 0; i < n; i++)
    {
        printf("输入与顶点编号%d 有边相连的条数：", g.vertices[i].data);
        scanf("%d", &count);
        sum = sum + count;
        printf("再依次输入与顶点编号%d 有边相连的顶点编号，中间用空格分隔：", g.vertices[i].data);
        for (j = 0; j < count; j++)
        {
            scanf("%d", &x);
            //求出顶点对应的下标值
            for (t = 0; t < n; t++)
                if (g.vertices[t].data == x)
                {
                    k = t;
                    break;
                }
            p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = k;
            p->nextarc = g.vertices[i].firstarc;
            g.vertices[i].firstarc = p;
        }
    }
    g.kind = AG;
    g.vexnum = n;
    g.arcnum = sum / 2;
}

//图深度优先遍历函数定义
void DepthFirstSearch(ALGraph g, int i) //参数 i 表示顶点的下标
{
    ArcNode *p; //工作指针
    printf("%d ", g.vertices[i].data);  //打印遍历结果
    visited[i] = 1; //表示已遍历过该顶点
    p = g.vertices[i].firstarc;  //指向连接该顶点的另一个顶点
    while (p)
    {
        if (!visited[p->adjvex]) //若另一个顶点没有遍历过，则用递归，继续遍历
            DepthFirstSearch(g, p->adjvex); //递归
        p = p->nextarc; //接着下一个顶点
    }
}

void DFSTranverse(ALGraph &g)
{
    for (int v = 0; v < g.vexnum; v++)
        visited[v] = 0; //先全部初始化，没有遍历过，为后续遍历时的标志做准备
    for (int v = 0; v < g.vexnum; v++)
    {
        if (!visited[v])
            DepthFirstSearch(g, v); //逐个遍历
    }
}

//图广度优先遍历函数定义

//*建立队列的数据结构方便进行广度优先遍历
typedef struct
{
    int data[MAX_VERTEX_NUM] ; //队列中存放顶点的值
    int head, tail ;  //队头与队尾
} Quene ;

//*进行广度优先搜索遍历

void BreadthFirstSearch(ALGraph g, int k)
{
    int i, j ;
    Quene q ; //定义队列
    ArcNode *p;
    q.head = 0 ;
    q.tail = 0 ; //进行队列的初始化
    printf("%d", g.vertices[k].data);   //与深度遍历一样，遍历第一个，然后打印出来遍历结果
    visited[k] = 1 ;  //标志已遍历过
    q.data[q.tail++] = k ; //将已遍历过的顶点入队
    while (q.head  % (MAX_VERTEX_NUM - 1) != q.tail % (MAX_VERTEX_NUM - 1)) //以下为顶点遍历入队、遍历结束出队的过程
    {
        i = q.data[q.head++] ;
        p = g.vertices[i].firstarc;
        while (p)
        {
            if (!visited[p->adjvex])
            {
                printf(" %d", g.vertices[p->adjvex].data) ;
                visited[p->adjvex] = 1 ;
                q.data[q.tail++] = p->adjvex ;
            }
            p = p->nextarc;
        }
    }
}
void BFSTraverse(ALGraph g)
{
    int i ;
    for (i = 0 ; i < g.vexnum ; i++)
    {
        visited[i] = 0 ;
    }
    for (i = 0 ; i < g.vexnum; i++)
    {
        if (!visited[i])
        {
            BreadthFirstSearch(g, i) ;
        }
    }
}

int main()
{
    int i, j, n;
    ArcNode *p;
    ALGraph g;
    create(g);
    printf("图的邻接表结构如下，以下出现的数字均为每个顶点的编号，而非下标值：\n");
    for (i = 0; i < g.vexnum; i++)
    {
        printf("%d--->", g.vertices[i].data);
        p = g.vertices[i].firstarc;
        while (p != NULL)
        {
            j = p->adjvex;
            printf("%d ", g.vertices[j].data);
            p = p->nextarc;
        }
        printf("\n");
    }
    printf("该图有%d 个顶点，有%d 条边。\n", g.vexnum, g.arcnum);
    printf("\n");
//图深度优先遍历函数调用
    printf("图的深度优先遍历结果为：\n");
    DFSTranverse(g);
//图广度优先遍历函数调用
    printf("\n");
    printf("\n图的广度优先遍历结果为：\n");
    BFSTraverse(g);
    return 0;
}
