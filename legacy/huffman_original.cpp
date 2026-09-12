#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8

//哈夫曼树类型定义 存储哈夫曼树的静态三叉链表类型定义
typedef struct
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;

typedef char ** HuffmanCode;//动态分配数组存储赫夫曼树


//字符、权值、对应编码组成的结构体类型
struct s
{
    char c;
    int weight;
    char code[N];
};

//此处函数定义请自行编写
void Select(HuffmanTree HT, int end, int *s1, int *s2)
{
        int min1, min2;
        //遍历数组初始下标为 1
        int i = 1;
        //找到还没构建树的结点
        while (HT[i].parent != 0 && i <= end)
        {
            i++;
        }
        min1 = HT[i].weight;
        *s1 = i;

        i++;
        while (HT[i].parent != 0 && i <= end)
        {
            i++;
        }
        //对找到的两个结点比较大小，min2为大的，min1为小的
        if (HT[i].weight < min1)
        {
            min2 = min1;
            *s2 = *s1;
            min1 = HT[i].weight;
            *s1 = i;
        }
        else
        {
            min2 = HT[i].weight;
            *s2 = i;
        }
        //两个结点和后续的所有未构建成树的结点做比较
        for (int j = i + 1; j <= end; j++)
        {
            //如果有父结点，直接跳过，进行下一个
            if (HT[j].parent != 0)
            {
                continue;
            }
            //如果比最小的还小，将min2=min1，min1赋值新的结点的下标
            if (HT[j].weight < min1)
            {
                min2 = min1;
                min1 = HT[j].weight;
                *s2 = *s1;
                *s1 = j;
            }
            //如果介于两者之间，min2赋值为新的结点的位置下标
            else if (HT[j].weight >= min1 && HT[j].weight < min2)
            {
                min2 = HT[j].weight;
                *s2 = j;
            }
        }
}
//HT数组中存放的哈夫曼树，end表示HT数组中存放结点的最终位置，s1和s2传递的是HT数组中权重值最小的两个结点在数组中的位置

void CreateHuffmanTree(HuffmanTree *HT, int *w, int n)
{
    if(n<=1) 
	return; // 如果只有一个编码就相当于0
    int m = 2*n-1; // 哈夫曼树总节点数，n就是叶子结点
    *HT = (HuffmanTree) malloc((m+1) * sizeof(HTNode)); // 0号位置不用
    HuffmanTree p = *HT;
    // 初始化哈夫曼树中的所有结点
    for(int i = 1; i <= n; i++)
    {
        (p+i)->weight = *(w+i-1);
        (p+i)->parent = 0;
        (p+i)->lchild = 0;
        (p+i)->rchild = 0;
    }
    //从树组的下标 n+1 开始初始化哈夫曼树中除叶子结点外的结点
    for(int i = n+1; i <= m; i++)
    {
        (p+i)->weight = 0;
        (p+i)->parent = 0;
        (p+i)->lchild = 0;
        (p+i)->rchild = 0;
    }
    //构建哈夫曼树
    for(int i = n+1; i <= m; i++)
    {
        int s1, s2;
        Select(*HT, i-1, &s1, &s2);
        (*HT)[s1].parent = (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

//从叶子到根逆向求每个字符的哈夫曼编码
void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC,int n)
{
    *HC = (HuffmanCode) malloc((n+1) * sizeof(char *));
    char *cd = (char *)malloc(n*sizeof(char)); //存放结点哈夫曼编码的字符串数组
    cd[n-1] = '\0';//字符串结束符
   
    for(int i=1; i<=n; i++)
	{
        //从叶子结点出发，得到的哈夫曼编码是逆序的，需要在字符串数组中逆序存放
        int start = n-1;
        //当前结点在数组中的位置
        int c = i;
        //当前结点的父结点在数组中的位置
        int j = HT[i].parent;
        // 一直寻找到根结点
        while(j != 0)
		{
            // 如果该结点是父结点的左孩子则对应路径编码为0，否则为右孩子编码为1
            if(HT[j].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
            //以父结点为孩子结点，继续朝树根的方向遍历
            c = j;
            j = HT[j].parent;
        }
        //跳出循环后，cd数组中从下标 start 开始，存放的就是该结点的哈夫曼编码
        (*HC)[i] = (char *)malloc((n-start)*sizeof(char));
        strcpy((*HC)[i], &cd[start]);
    }
    //使用malloc申请的cd动态数组需要手动释放
    free(cd);
}

//打印哈夫曼编码函数
void PrintfHuffmanCode(char string[100], int n, char data[100], HuffmanCode HC)
{
	int j = 0;
	printf("该字符串对应的哈夫曼编码是：");
	while (string[j] != '\0')
	{
		for ( int i = 0; i < n; i++)
		{
			if (string[j] == data[i])//对比
			{
				printf("%s", HC[i + 1]);
			}
		}
		++j;
	}
}

//解码函数
void PrintfHuffmanTranslateCode(HuffmanTree HT, int n, char data[100])
{
	int m = 2 * n - 1;
	int i, j = 0;
	char string[100];
	scanf("%s", string);
	printf(("该哈夫曼编码对应的字符串为："));
	while (string[j] != '\0') 
	{
		i = m;
		while (0 != HT[i].lchild && 0 != HT[i].rchild)//搜索到没有“孩子”就下一个，这是判断是否为下一个字符的条件。
		{
			//从根节点往下搜索
			if ('0' == string[j])
			{
				//如果是0 则往左子树走
				i = HT[i].lchild;
			}
			else
			{
				//如果是1 则往往右子树走
				i = HT[i].rchild;
			}
			++j;//开始下一次遍历（下一个字母的编码匹配）
		}
		printf("%c", data[i - 1]);
	}
}

int main()
{
//变量初始化
    HuffmanTree HT;
    HuffmanCode HC;
    char *cd;
    int *w, n=8, i, m;
    char string[100];//存放输入的字符串
	char data[100];//存放输入的字符

//输入相关数据（字符、权值），并存入相应的数组中。
    for(i=0;i<8;i++)
    {
		printf("请输入第%d个字符：",i+1);
		scanf(" %c",&data[i]);//注意注意!!这里在%前要加一个！空格！，不然之后会出问题的。弄了好久！
		printf("请输入该字符的权值：");
		scanf("%d",&w[i]);
	}
	
//哈夫曼树的建立和编码的生成
	printf("\n哈夫曼树如下所示：");
	printf("\nweight\tparent\tlchild\trchild\n");
    CreateHuffmanTree(&HT, w, n);
    m = 2 * n - 1;
    for (i = 1; i <= m; i++)
	{
		printf("%d\t%d\t%d\t%d\n", HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	}
    HuffmanCoding(HT, &HC, n);

//打印哈夫曼树中字符对应的权值、编码（打印输出哈夫曼树数据）
    printf("\n%d个字符的字符，权值及哈夫曼树编码如下：\n", n);
    for (i = 0; i < n; i++)
	{
		printf("%c\t%d\t%s\n", data[i], HT[i + 1].weight, HC[i + 1]);
	}
	
//编码（用户输入任意一个由 N 个字符组成的字符串，输出该字符串对应的哈夫曼编码字符串）
	printf("\n请输入一个字符串，该字符串只能包括8个字符（ABCDEFGH）:");
	scanf("%s", string);
	PrintfHuffmanCode(string, n, data, HC);
	printf("\n");
	
//解码（用户输入哈夫曼编码(由 01 组成)，将进行解码，输出对应的字符串）
	printf("\n请输入0或者1的哈夫曼树编码进行译码：");
	PrintfHuffmanTranslateCode(HT, n, data);

//释放内存
	for (i = 1; i <= n; i++)
	{
		free(HC[i]);
	}
		free(HC);
		free(HT);
    return 0;
}
