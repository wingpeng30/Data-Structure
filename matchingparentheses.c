#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node
{
    char data;
    struct node *next;
}LinkStackNode;
typedef LinkStackNode *LinkStack;

void InitStack(LinkStack S)
{
    S=(LinkStack)malloc(sizeof(struct node));
    S->next=NULL;
}

void Push(LinkStack S,char item)
{
    LinkStack temp;
    temp=(LinkStack)malloc(sizeof(struct node));
    temp->data=item;
    temp->next=S->next;
    S->next=temp;
    return;
}

int Pop(LinkStack S,char *x)
{
    if(Isempty(S))
    {
        printf("空");
        return NULL;
    }
    else
    {
        LinkStack temp;
        temp=S->next;
        *x=temp->data;
        S->next=temp->next;
        free(temp);
        return TRUE;
    }
}

int Isempty(LinkStack S)
{
    if(S->next==NULL)
        return TRUE;
    else
        return FALSE;
}

int Gettop(LinkStack S,char *ch)
{
    if(Isempty(S)==0)
    {
        *ch=S->next->data;
        return TRUE;
    }
    else
        return FALSE;
}

int Match(char x,char y)
{
    if(x==y)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void Bracket(char *str)
{
    int i;
    LinkStack S;
    char ch;
    InitStack(&S);
    for(i=0;str[i]!='\0';i++)
    {
        switch (str[i])
        {
        case '(':
        case '{':
        case '[':Push(&S,str[i]);break;
        case ')':
        case ']':
        case '}':
            if(Isempty(S))
            {
                printf("\n右括号多余");
                return;
            }
            else
            {
                Gettop(&S,&ch);
                if(Match(str[i],ch))
                    Pop(&S,&ch);
                else
                    {
                        printf("\n对应的左右括号不同类");
                        return;
                    }
            }
        
        default:
            break;
        }
    }
    if(Isempty(S))
        printf("\n括号匹配");
    else
        printf("\n左括号多余");
    return;
}

int main()
{
    char str[100];
    gets(str);
    Bracket(str);

    system("pause");
    return 0;
}