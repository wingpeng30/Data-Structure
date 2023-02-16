#include <stdio.h>
#include <stdlib.h>

typedef struct LINK *linknode;
struct LINK{
    int n;
    struct LINK *next;
}linklist;

void ReverseList(linknode L)
{
    linknode p,q;
    p=L->next;
    L->next=NULL;
    // L为p前一个结点，p为处理中结点，q为p后一个节点 
    while(p!=NULL)
    {
        q=p->next;
        p->next=L->next;
        L->next=q;
        p=q;
    }
}