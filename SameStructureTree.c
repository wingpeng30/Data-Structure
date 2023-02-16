#include <stdio.h>

#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

// 结构数组表示二叉树：静态链表

struct TreeNode
{
    ElementType Element;
    // -1表示无连接 即为Null
    Tree Left;
    Tree Right;
}T1[MaxTree],T2[MaxTree];//数组下标表示节点编号
// 所有Left,Right的数字没指向的即为根


Tree BuildTree(struct TreeNode T[])
{
    // 创建一个check数组表示子结点，1为子节点，0为根节点
    // 之后通过遍历找到根节点
    Tree N,i,check[100];
    Tree Root=0;
    ElementType cl,cr;
    scanf("%d",&N);
    if(N)
    {
        for(i=0;i<N;i++)
            check[i]=0;
        for(i=0;i<N;i++)
        {
            scanf("%c %c %c",&T[i].Element,&cl,&cr);
            getchar();
            if(cl!='-')
            {
                // 类型转换
                T[i].Left=cl-'0';
                // 是子树/有父节点的标记为1
                check[T[i].Left]=1;
            }
            // 否则标记为无连接
            else T[i].Left=Null;
            if(cr!='-')
            {
                // 类型转换
                T[i].Right=cl-'0';
                // 是子树/有父节点的标记为1
                check[T[i].Right]=1;
            }
            // 否则标记为无连接
            else T[i].Right=Null;
        }
        for(i=0;i<N;i++)
            if(!check[i])
                break;
        Root=i;
    }
    return Root;
}

Tree Isomorphic(Tree R1,Tree R2)
{
    // 都是空树 
    if(R1==Null&&R2==Null)
        return 1;
    // 其中一个是子树
    if(((R1==Null)&&(R2!=Null))||((R2==Null)&&(R1!=Null)))
        return 0;
    // 根节点不同
    if(T1[R1].Element!=T2[R2].Element)
        return 0;
    // 都没有左子树
    if((T1[R1].Left==Null)&&(T2[R2].Left==Null))
        return Isomorphic(T1[R1].Right,T2[R2].Right);
    // 不用交换左右子树
    if(((T1[R1].Left!=Null)&&(T2[R2].Left!=Null))&&
       ((T1[T1[R1].Left].Element)==(T2[T2[R2].Left].Element)))
        return (Isomorphic(T1[R1].Left,T2[R2].Left)&&Isomorphic(T1[R1].Right,T2[R2].Right));
    // 需要交换左右子树
    else
        return (Isomorphic(T1[R1].Right,T2[R2].Left)&&Isomorphic(T1[R1].Left,T2[R2].Right));
}


int main()
{
    Tree R1,R2;

    // 建二叉树1
    R1=BuildTree(T1);
    // 建二叉树2
    R2=BuildTree(T2);
    // 判别是否同构并输出
    if(Isomorphic(R1,R2))
        printf("Yes\n");
    else
        printf("No\n");

    system("pause");
    return 0;
}