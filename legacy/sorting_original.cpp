#include <stdio.h>
#define MAXSIZE 20 //一个用作示例的小顺序表的最大长度

typedef int KeyType; //定义关键字类型为整数类型

typedef struct
{
    int key; //关键字项0
} RecordType; //记录类型

typedef struct
{
    RecordType r[MAXSIZE + 1]; //r[0]闲置或用作哨兵单元
    int length; //顺序表长度
} SqList; //顺序表类型 结构体别名

void insSort(SqList &L)
{
    int i, j;
    for (i = 2; i <= L.length; i++)
    {
        L.r[0] = L.r[i];
        j = i - 1;
        while (L.r[0].key < L.r[j].key)
        {
            L.r[j + 1] = L.r[j];
            j = j - 1;
        }
        L.r[j + 1] = L.r[0];
    }

}
void BinSort(SqList &T)
{
    int i, j, low, high, mid;
    for (i = 2; i <= T.length; i++) //找要插入元素的位置下标，最终low的值为要插入的位置下标
    {
        T.r[0] = T.r[i];
        low = 1, high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            if (T.r[mid].key > T.r[0].key)
                high = mid - 1;
            else
                low = mid + 1;
        }
        //从下标为row的元素开始一直到下标为i-1的元素为止，所有元素后退一个
        for (j = i - 1; j >= low; j--)
            T.r[j + 1] = T.r[j];
        //将要插入的元素放入到下标为low的位置
        T.r[low] = T.r[0];
    }
}

int Partition(SqList & L, int low, int high)
{
    RecordType q;
    int pivotkey = L.r[low].key;
    while (low < high)
    {
        while (low < high && L.r[high].key >= pivotkey)
            --high;
            
        q = L.r[low];
        L.r[low] = L.r[high];
        L.r[high] = q;
        
        while (low < high && L.r[low].key <= pivotkey)
            ++low;
            
        q = L.r[low];
        L.r[low] = L.r[high];
        L.r[high] = q;

    }
    return low;//注意此处要有一个 return 语句，返回一个整数。
}

void QSort(SqList & L, int low, int high)
{
    if (low < high)
    {
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }

}
void HeapAdjust (SqList & H, int s, int m)
{
    RecordType rc = H.r[s];
    for (int j = 2 * s; j <= m; j *= 2)
    {
        if (j < m && H.r[j].key < H.r[j + 1].key)
            j++;
        if (rc.key >= H.r[j].key)
            break;
        H.r[s] = H.r[j];
        s = j;
    }
    H.r[s] = rc;

}
void HeapSort(SqList & H)
{
    int n = H.length;
    int i;
    RecordType q;
    //将初始状态调整为初始大根堆
    for (i = n / 2; i > 0; i = i - 1)
        HeapAdjust(H, i, n);
    //由初始大根堆开始,经过n-1次调整,最终排好序
    for (i = n; i >= 2; i = i - 1)
    {
        //将堆顶记录与最后一个记录交换
           q = H.r[1];
           H.r[1] = H.r[i];
           H.r[i] = q;
        //进行调整,使得调整后的序列变成一个堆
        HeapAdjust(H, 1, i - 1);
    }
}
void output(SqList &L)
{
    for (int i = 1; i <= L.length; i++)
    {
        printf("%d ", L.r[i].key);
    }
    printf("\n");
}
int main()
{
    int ch;
    int n;
    SqList L, T; //输入的数据放入 L，每次排序前将变量 L 的值赋值给 T。
    printf("输入整形数据 n, n 表示数据个数:");
    scanf("%d", &n);
    int low = 1, high = n;
    L.length = n;
    printf("请输入%d个整数：", n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &L.r[i].key);
    }//请输入 n 个整数，存放在顺序表 L 中。
//以下为排序代码和数据输出代码
    do
    {
        printf("\n");
        printf("**************************\n");
        printf("1:直接插入排序\n");
        printf("2:折半插入排序\n");
        printf("3:快速排序\n");
        printf("4:堆排序\n");
        printf("5:退出系统\n");
        printf("**************************\n");
        printf("根据菜单选择输入 1-5 中的任一个数字：");
        scanf("%d", &ch);
        while (ch != 1 && ch != 2 && ch != 3 && ch != 4 && ch != 5)
        {
            printf("输入错误请重新输入 1-5 中的任一个字符：");
            scanf("%d", &ch);
        }
        switch (ch)
        {
            case 1:
            {
                T = L;
                printf("排序前：\n");
                output(T);
                printf("此处调用直接插入排序函数\n");
                insSort(T);
                printf("排序后：\n");
                output(T);
                break;
            }
            case 2:
                T = L;
                printf("排序前：\n");
                output(T);
                printf("此处调用折半插入排序函数\n");
                BinSort(T);
                printf("排序后：\n");
                output(T);
                break;
            case 3:
                T = L;
                printf("排序前：\n");
                output(T);
                printf("此处调用快速排序函数\n");
                QSort(T, low, high);//QSort(T,1,n);直接传入实参更好！不然high的定义要放在输入n之后，不然出问题啦!
                printf("排序后：\n");
                output(T);
                break;
            case 4:
                T = L;
                printf("排序前：\n");
                output(T);
                printf("此处调用堆排序函数\n");
                HeapSort(T);
                printf("排序后：\n");
                output(T);
                break;
        }
    }
    while (ch != 5);
    return 0;
}
