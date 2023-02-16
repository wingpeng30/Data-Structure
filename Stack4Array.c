#include <stdio.h>
#define MAXSIZE 100
typedef struct SNODE *Stack;
struct  SNODE
{
    int Data[MAXSIZE];
    int top;
};

void Push(Stack Ptrs,int item)
{
    if(Ptrs->top>=MAXSIZE-1)
    {
        printf("栈堆满");
        return;
    }
    else
    {
        Ptrs->Data[++Ptrs->top]=item;
        return;
    }
}

int Push(Stack Ptrs)
{
    if(Ptrs->top==-1)
    {
        printf("栈空");
        return -1;
    }
    else
    {
        return Ptrs->Data[Ptrs->top--];
    }
}


// 两个栈最大利用数组空间：
// 两个栈从数组两边向中间生长
// 栈顶指针相遇时（top1==top2-1)表示两个栈都满了

struct DStack
{
    int Data[100];
    int top1;
    int top2;
}S;

// S.top1==-1,S.top2==MAXSIZE
void Push2(struct DStack *Ptrs,int item,int Tag)
{ 
    // Tag作为区分两个堆栈的标志，取值为1,2
    if(Ptrs->top2-Ptrs->top1==1)
    {
        printf("满");return;
    }
    else
    {
        if(Tag==1)
            Ptrs->Data[++Ptrs->top1]=item;
        else
            Ptrs->Data[++Ptrs->top2]=item;
    }
}

int Pop2(struct DStack *Ptrs,int Tag)
{
    if(Tag==1)
    {
        if(Ptrs->top1==-1)
        {
            printf("空");
            return -1;
        }
        else
        {
            return Ptrs->Data[Ptrs->top1--];
        }
    }
    else
    {
        if(Ptrs->top2==-1)
        {
            printf("空");
            return -1;
        }
        else
        {
            // top向反方向增加
            return Ptrs->Data[Ptrs->top2++];
        }
    }
}