#include <stdio.h>
#include <malloc.h>
#define ElementType int

typedef struct TreeNode *BinTree;

struct TreeNode
{
    int Data;
    // 下一层
    BinTree FirstChild;
    // 同一层
    BinTree NextSibling;
};



// 动态查找：可插入删除  
// 二叉搜索树（BST）
// 1、非空左子树的所有键值小于其根结点的键值
// 2、非空右子树的所有键值大于其根结点的键值
// 3、左右子树都是二叉搜索树


// 查找操作
// 结点关键字与X比较
// 1.若X小于根结点键值，只需在左子树进行搜索
// 2.若X大于根结点键值，在右节点继续搜索
// 3.相等 搜索完成 返回指针

BinTree PositionFind(ElementType X,BinTree BST)
{
    if(!BST) return NULL;
    if(X>BST->Data)
    // 右子树
        return PositionFind(X,BST->NextSibling);
    else if(X<BST->Data)
    // 左子树
        return PositionFind(X,BST->FirstChild);
    else
        return BST;
}

BinTree PositionFind2(ElementType X,BinTree BST)
{
    while(BST)
    {
        if(X>BST->Data)
            BST=BST->NextSibling;
        else if(X<BST->Data)
            BST=BST->FirstChild;
        else
            return BST;
    }
    return NULL;
}

// 查找最大，最小元素
// 最大元素:最右分支端结点
// 最小元素:最左分支端节点


BinTree PositionFindMin(BinTree BST)
{
    if(!BST)    return NULL;
    else if(!BST->FirstChild)   return BST;
    else
        return PositionFindMin(BST->FirstChild);
}

BinTree PositionFindMax(BinTree BST)
{
    if(BST)
    {
        while (BST->NextSibling)
        {
            BST=BST->NextSibling;
        }
    }
    return BST;
}
// 插入：先查找在递归插入

BinTree Insert(BinTree BST,ElementType X)
{
    if(!BST)
    {
        BST=malloc(sizeof(struct TreeNode));
        BST->Data=X;
        BST->FirstChild=BST->NextSibling=NULL;
    }
    else
    {
        if(X<BST->Data)
        // 可以通过递归返回到原来第一次调用的位置
            BST->FirstChild=Insert(X,BST->FirstChild);
        // 如果直接return：会return最后一个位置
        else if(X>BST->Data)
            BST->NextSibling=Insert(X,BST->NextSibling);
    }
    return BST;
}

// 删除：三种情形

BinTree Delete(ElementType X,BinTree BST)
{
    BinTree Tmp;
    if(!BST)    printf("要删除元素未找到");
    else if(X<BST->Data)//左子树递归删除
        BST->FirstChild=Delete(X,BST->FirstChild);
    else if(X>BST->Data)//右子树递归删除
        BST->NextSibling=Delete(X,BST->NextSibling);
    else //找到节点
    {
        if(BST->FirstChild&&BST->NextSibling) //被删除结点有两个子结点
        {
            // 右子树中找最小的元素填充删除结点
            Tmp=PositionFindMin(BST->NextSibling);
            BST->Data=Tmp->Data;
            // 再删除节点的右子树中删除最小元素
            BST->NextSibling=Delete(BST->Data,BST->NextSibling);
        }
        else//删除节点有一个或无子结点
        {
            Tmp=BST;
            if(!BST->FirstChild)//有右孩子或无子结点
                BST=BST->NextSibling;
            else if(!BST->NextSibling)//有左孩子或无子结点
                BST=BST->FirstChild;
            free(Tmp);
        }
    }
    return BST;

}