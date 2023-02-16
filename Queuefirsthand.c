#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000
#define TRUE 1
#define FALSE 0

struct QNode
{
    int data[MAXSIZE];
    int top;
    int rear;
};
typedef struct QNode *Queue;
// 先进先出 FIFO



Queue CreateQueue(int Maxsize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->top = Q->rear = 0;
    return Q;
}

// 为了保证能保证空与满且两状态不重复
// 只用Maxsize-1的存储空间
// 开始时rear=top
// 队列满时rear与top相邻
// 则用求余公式表示

int Isfull(Queue Q)
{
    if((Q->rear+1)%MAXSIZE==Q->top)
        return TRUE;
    else
        return FALSE;
}

int Isempty(Queue Q)
{
    if(Q->rear==Q->top)
        return TRUE;
    else
        return FALSE;
}

void AddQ(Queue Q,int item)
{
    if(Isfull(Q))
    {
        printf("队满");
        return;
    }
    else
    {
        Q->rear=(Q->rear+1)%MAXSIZE;
        Q->data[Q->rear]=item;
        return; 
    }
}

int DeleteQ(Queue Q)
{
    if(Isempty(Q)==1)
    {
        printf("空");
        return -1;
    }
    else
    {
        Q->top=(Q->top+1)%MAXSIZE;
        return Q->data[Q->top];
    }
}

void PrintQ(Queue Q)
{
    int i;
    for(i=Q->top+1;i<=Q->rear;i++)
    {
        printf("%d\n",Q->data[i]);
    }
    return;
}

int main()
{
    Queue Q;
    Q=CreatQueue();
    AddQ(Q,3);
    AddQ(Q,4);
    DeleteQ(Q);
    AddQ(Q,5);
    PrintQ(Q);

    system("pause");
    return 0;
}