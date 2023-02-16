#include <stdio.h>
#define MAXSIZE 100
typedef struct SNODE *Stack;
struct  SNODE
{
    char Data[MAXSIZE];
    int top;
};

void Push(Stack Ptrs,char item)
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

char Pop(Stack Ptrs)
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

void Assume(Stack Ptrs,char ch)
{
    if(Ptrs->Data[Ptrs->top]=='*'||Ptrs->Data[Ptrs->top]=='/')
    {
        Pop(Ptrs);
        Pop(Ptrs);
        Push(Ptrs,ch);
    }
    else if(Ptrs->Data[Ptrs->top]=='')
}

int main()
{
    Stack Structure;
    Structure->top=-1;
    char ch,out;
    ch=getchar();
    while(ch!='@')
    {
        switch(ch)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:printf("%c",ch);break;
            case '(':
            case '*':
            case '/':
            case '+':
            case '-':Push(Structure,ch);break; 
        }
    }
}