#include <stdio.h>
#include <time.h>

double duration;
clock_t start,stop;

#define MAXK 1e7

int MaxSub1(int n,int a[])
{
    int i,j,k;
    int MaxSum=0,ThisSum=0;
    for(i=0;i<n;i++)//i是子列左端位置
    {
        // j是子列右端位置
        for(j=i;j<n;j++) 
        {
            ThisSum=0;//a[i]到a[j]的子列和
            for(k=i;k<=j;k++)
            {
                ThisSum+=a[k];
            }
            if(ThisSum>MaxSum)
            {
                // 如果子列和更大则更新结果
                MaxSum=ThisSum;
            }
        }
    }
    return MaxSum;
}
// 时间复杂度:o(n^3)

// 优化：减少一个循环
// k：每次都从i开始算，有点重复
// 进入下一个循环：只要在上一个结果的循环再加下一个元素即可
/* 方法二：确定子列的首部，逐个累加，时间复杂度 O(n^2)*/ 
int MaxSub2(int n,int a[]){
	int max = 0;
	for(int i=0;i<n;i++){   // 控制子列的首部
		int tmpSum = 0;  // 当前子列和
		for(int j=i;j<n;j++){  // 控制子列的尾部
			tmpSum+=a[j];
			if(max < tmpSum)
				max = tmpSum;
		}
	}
	return max;
}

// 还有点长 0(n^2)

// 算法三：分而治之（分割然后递归）先解决子问题 递归到总问题
/* 方法三：递归分成两份，分别求每个分割后最大子列和，时间复杂度为 O(n*logn)*/
/* 返回三者中最大值*/
int Max3(int A,int B,int C){
	return (A>B)?((A>C)?A:C):((B>C)?B:C);
}
/* 分治*/
int DivideAndConquer(int a[],int left,int right){
	
	/*递归结束条件：子列只有一个数字*/
	// 当该数为正数时，最大子列和为其本身
	// 当该数为负数时，最大子列和为 0
	if(left == right){
		if(0 < a[left])  
			return a[left];
		return 0;
	}
	
	/* 分别递归找到左右最大子列和*/ 
	int center = (left+right)/2; 
	int MaxLeftSum = DivideAndConquer(a,left,center);
	int MaxRightSum = DivideAndConquer(a,center+1,right);
	
	/* 再分别找左右跨界最大子列和*/
	int MaxLeftBorderSum = 0;
	int LeftBorderSum = 0;
	for(int i=center;i>=left;i--){  //应该从边界出发向左边找
		LeftBorderSum += a[i];
		if(MaxLeftBorderSum < LeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;	
	}
	int MaXRightBorderSum = 0;
	int RightBorderSum = 0;
	for(int i=center+1;i<=right;i++){  // 从边界出发向右边找
		RightBorderSum += a[i];
		if(MaXRightBorderSum < RightBorderSum)
			MaXRightBorderSum = RightBorderSum;
	}
	
	/*最后返回分解的左边最大子列和，右边最大子列和，和跨界最大子列和三者中最大的数*/
	return Max3(MaxLeftSum,MaxRightSum,MaXRightBorderSum+MaxLeftBorderSum);
}
int MaxSub3(int n,int a[]){
	return DivideAndConquer(a,0,n-1);
}

/* 方法五：直接累加，如果累加到当前的和为负数，置当前值或0，时间复杂度为 O(n)*/ 
// “贪心法”，即不从整体最优上加以考虑，只做出某种意义上的局部最优解。
// 其实最大子列和与它的首部和尾部都没有关系，
// 我们只关心它当前的大小。
// 当临时和加上当前值为负时，它对之后子列和肯定没有帮助（甚至只会让之后的和更小！)
// 我们抛弃这段临时和将它置0
int MaxSub4(int n,int a[]){
	int max = 0;
	int tmpSum=0;
	for(int i=0;i<n;i++){
		tmpSum+=a[i];
		if(tmpSum<0){
			tmpSum=0;
		}else if(max < tmpSum){
			max = tmpSum;
		}
	}
	return max;
}


int main()
{
    int n,i,a[100];
    printf("请输入数字个数\n");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    
    int sum1,sum2,sum3,sum4;
    
    start=clock();
    for(i=1;i<=MAXK;i++)
    {
        sum1=MaxSub1(n,a);
    }
    stop=clock();
    duration=((double)(stop-start))/CLK_TCK/MAXK;
    printf("%d ",sum1);
    printf("ticks1=%f ",(double)(stop-start));
    printf("duration1=%6.2e\n",duration);
    
    start=clock();
    for(i=1;i<=MAXK;i++)
    {
        sum2=MaxSub2(n,a);
    }
    stop=clock();
    duration=((double)(stop-start))/CLK_TCK/MAXK;
    printf("%d ",sum2);
    printf("ticks2=%f ",(double)(stop-start));
    printf("duration2=%6.2e\n",duration);
    
    start=clock();
    for(i=1;i<=MAXK;i++)
    {
        sum3=MaxSub3(n,a);
    }
    stop=clock();
    duration=((double)(stop-start))/CLK_TCK/MAXK;
    printf("%d ",sum3);
    printf("ticks3=%f ",(double)(stop-start));
    printf("duration3=%6.2e\n",duration);
    
    start=clock();
    for(i=1;i<=MAXK;i++)
    {
        sum4=MaxSub4(n,a);
    }
    stop=clock();
    duration=((double)(stop-start))/CLK_TCK/MAXK;
    printf("%d ",sum4);
    printf("ticks4=%f ",(double)(stop-start));
    printf("duration4=%6.2e\n",duration);

    system("pause");
    return 0;
}

