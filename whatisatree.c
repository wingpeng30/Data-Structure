#include <stdio.h>
#include <malloc.h>
#define Maxsize 100
#define MAXSIZE 100
// 1.用数组表示
// 只能在完全二叉树中实现
// 非完全：补全为完全二叉树(wasted)

// 非根结点（i>1）的父结点序号为i/2
// 左儿子为2i,右为2i+1

// 2.链表表示
// 儿子兄弟表示法
// 二叉树 四十五度表示法 左为子树，右为同层

typedef struct TreeNode *BinTree;
typedef BinTree Position;

struct TreeNode
{
    int Data;
    // 下一层
    BinTree FirstChild;
    // 同一层
    BinTree NextSibling;
};

typedef struct SNode *Stack;
struct SNode{
    int Data;
    struct SNode *next;
};

struct QNode
{
    int data[MAXSIZE];
    int top;
    int rear;
};
typedef struct QNode *Queue;
// 先进先出 FIFO



Queue CreateQueue(int M)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->top = Q->rear = 0;
    return Q;
}

// top在链表最左端（方便插入、删除）
// 有一个空的头结点 方便操作
Stack Stackcreate()
{
    Stack S;
    S=(Stack)malloc(sizeof(struct SNode));
    S->next=NULL;
    return S;
}

int Isempty(Stack S)
{
    return (S->next==NULL);
}

void Push(Stack S,int item)
{
    Stack tmp;
    tmp=(Stack)malloc(sizeof(struct SNode));
    tmp->Data=item;
    tmp->next=S->next;
    S->next=tmp;
}

int Pop(Stack S)
{   
    Stack Firstcell;
    int Topelem;
    if(Isempty(S))
    {
        printf("表空");
        return -1;
    }
    else
    {
        Firstcell=S->next;
        S->next=Firstcell->next;
        Topelem=Firstcell->Data;
        free(Firstcell);
        return Topelem;
    }
}
 

//  1.先序遍历：根，左，右

void PreOrderTraversal(BinTree BT)
{
    if(BT)
    {
        printf("%4d",BT->Data);
        PreOrderTraversal(BT->FirstChild);
        PreOrderTraversal(BT->NextSibling);
    }
}

// 2.中序:左根右
void InOrderTraversal(BinTree BT)
{
    if(BT)
    {
        InOrderTraversal(BT->FirstChild);
        printf("%4d",BT->Data);
        InOrderTraversal(BT->NextSibling);
    }
}


// 3.后序：左右根
void PostOrderTraversal(BinTree BT)
{
    if(BT)
    {
        PostOrderTraversal(BT->FirstChild);
        PostOrderTraversal(BT->NextSibling);
        printf("%4d",BT->Data);
    }
}

// 4.中序遍历非递归遍历算法 
// 使用堆栈
// 遇到一个结点，就把他压栈，并遍历左子树
// 遍历后弹出结点并访问它
// 按其右指针再去中序遍历结点右子树
void InOrderTraversal_Stack(BinTree BT)
{
    BinTree T=BT;
    Stack S=Stackcreate();
    while(T||!Isempty(S))
    {
        while(T)
        {
            // 已知向左压
            Push(S,T);
            T=T->FirstChild;
        }
        if(!Isempty(S))
        {
            T=Pop(S);
            printf("%5d",T);
            T=T->NextSibling;
        }
    }
}

// 5.层序遍历
// 第一步：根结点入队
// 然后循环：
// a.从队列中取出一个元素
// b.访问该元素所指结点
// c.若该元素所指结点的左、右孩子结点非空
// 则将其左右孩子的指针顺序入队

void LevelOrderTraversal(BinTree BT)
{
    Queue Q;BinTree T;
    if(!BT) return;
    Q=CreateQueue(MAXSIZE);
    AddQ(Q,BT);
    while(!IsemptyQ(Q))
    {
        T=DeleteQ(Q);
        // 访问取出队列的结点
        printf("%d",T->Data);
        if(T->FirstChild)   AddQ(Q,T->FirstChild);
        if(T->NextSibling)  AddQ(Q,T->NextSibling);
    }
}

// 树高度
int PostOrderGetHeight(BinTree BT)
{
    int HL,HR,MaxH;
    if(BT)
    {
        // 左子树
        HL=PostOrderGetHeight(BT->FirstChild);
        // 右子树
        HR=PostOrderGetHeight(BT->NextSibling);
        MaxH=(HL>HR)?HL:HR;
        return MaxH+1;
    }
    else 
        return 0;
}

// 二次运算表达式树及其遍历
// 中序得到正常表达式 但受到运算符优先级影响
// 通过列括号实现(左子树遍历前加括号)