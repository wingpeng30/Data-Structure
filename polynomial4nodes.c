#include <stdio.h>
#include <stdlib.h>

// 不要求逻辑上物理元素相邻
typedef struct LNode *List;
struct LNode{
    int DATA;
    List Next;
};
struct LNode L;
List Ptrl;

List Create_emptylink()
{
    List Ptrl;
    Ptrl=(List)malloc(sizeof(struct LNode));
    Ptrl->Next=NULL;
    return Ptrl;
}

// 1.求表长
int Length(List Ptrl)
{
    List p=Ptrl;
    int i=0;
    while(p)
    {
        p=p->Next;
        i++;
    }
    return i;
}

// 2.查找
// 2.1 按序号查找：FindKth
List FindKth(List Ptrl,int K)
{
    List tmp=Ptrl;
    int i=1;
    while(tmp!=NULL&&i<K)
    {
        tmp=tmp->Next;
        i++;
    }
    if(i==K)
        return tmp;
    else
        return NULL;
}

// 2.2 按照值查找
List Find(int K,List Ptrl)
{
    List p=Ptrl;
    while(p->DATA!=K&&p)
    {
        p=p->Next;
    }
    return p;
}

// 3.插入
List insert(int x,int i,List Ptrl)
{
    List p,s;
    if(i==1)
    {
        p=(List)malloc(sizeof(struct LNode));
        p->DATA=x;
        p->Next=Ptrl;
        return p;
    }
    p=FindKth(i-1,Ptrl);
    if(p==NULL)
    {
        printf("参数错");
        return;
    }
    else
    {
        s=(List)malloc(sizeof(struct LNode));
        s->DATA=x;
        s->Next=p->Next;
        p->Next=s;
        return Ptrl;
    }
}

List delete(int i,List Ptrl)
{
    List s,p;
    if(i==1)
    {
        p=Ptrl;
        if(Ptrl)
            Ptrl=Ptrl->Next;
        else
            return NULL;
        free(p);
        return Ptrl;
    }

    p=FindKth(i-1,Ptrl);
    if(p==NULL)
    {
        printf("%d个参数不存在",i-1);
        return;
    }
    else if(p->Next==NULL)
    {
        printf("%d个参数不存在",i);
        return;
    }
    else
    {
        s=p->Next;
        p->Next=s->Next;
        free(s);
        return Ptrl;
    }
}

typedef struct Polynode{
    int coef;
    int exp;
    struct Polynode *next;
}Polynode,*Polylist;

void Polyadd(Polylist polya,Polylist polyb)
{
    Polynode *p,*q,*tail,*tmp;
    int sum;
    p=polya->next,q=polyb->next;
    tail=polya;
    while(p!=NULL&&q!=NULL)
    {
        if(p->exp<q->exp)
        {
            tail->next=p;
            tail=p;
            p=p->next;
        }
        else if(p->exp==q->exp)
        {
            sum=p->coef+q->coef;
            if(sum!=0)
            {
                p->coef=sum;
                tail->next=p;
                tail=p;
                p=p->next;
                tmp=p;
                q=q->next;
                free(tmp);
            }
            else
            {
                tmp=p;p=p->next;free(p);
                tmp=q;q=q->next;free(q);
            }
        }
        else
        {
            tail->next=q;
            tail=q;
            q=q->next;
        }
    }
    if(p!=NULL)
    {
        tail->next=p;
    }
    if(q!=NULL)
    {
        tail->next=q;
    }
}