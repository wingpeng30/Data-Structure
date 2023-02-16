#include <stdio.h>
#define MAXSIZE 1000

// 利用数组的连续储存空间顺序存放线性表的各元素
typedef struct LNode *List;
struct LNode{
    int DATA[MAXSIZE];
    int Last;
};
struct LNode L;
List Ptrl;

// 1.初始化(建立空的顺序表)
List MakeEmpty()
{
    List Ptrl;
    Ptrl=(List)malloc(sizeof(struct LNode));
    Ptrl->Last=-1;
    return Ptrl;
}

// 2.查找
int Find(int x,List Ptrl)
{
    int i=0;
    while(i<=Ptrl->Last&&Ptrl->DATA[i]!=x)
        i++;
    if(i>Ptrl->Last)
        return -1;
    else
        return i;
}

// 3.插入
void insert(int i,List Ptrl,int X)
{
    int j;
    if(i<1||i>Ptrl->Last+2)
    {
        printf("位置不合法");
        return;
    }
    if(Ptrl->Last==MAXSIZE-1)
    {
        printf("表满");
        return;
    }
    for(j=Ptrl->Last;j>=i-1;j--)
    {
        Ptrl->DATA[j+1]=Ptrl->DATA[j];
    }
    Ptrl->DATA[i-1]=X;
    Ptrl->Last++;
    return;
}
// 4.删除
void delete(int i,List Ptrl)
{
    int j;
    if(i<1||i>Ptrl->Last+1)
    {
        printf("不存在第%d个元素",i);
        return;
    }
    for(j=i;j<=Ptrl->Last;j++)
    {
        Ptrl->DATA[j-1]=Ptrl->DATA[j];
    }
    Ptrl->Last--;
    return;
}

// 5.查找
// 循环+if即可

// 6.长度：ptrl.last+1