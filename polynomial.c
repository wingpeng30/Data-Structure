#include <stdio.h>
#include <math.h>
#include <time.h>

clock_t start,stop;

double duration;
#define MAXN 10
#define MAXK 1e7

double f1(int n,double a[],double x)
{
    int i;
    double p=a[0];
    for(i=1;i<=n;i++)
    {
        p+=a[i]*pow(x,i);
    }
    return p;
}

double f2(int n,double a[],double x)
{
    int i;
    double p=a[n];
    for(i=n;i>0;i--)
    {
        p=a[i-1]+x*p;
    }
    return p;
}


// 让被测函数重复运行充分多次
// 使得测出的总的时钟打点间隔充分长
// 最后计算被测函数平均每次运行的时间即可
int main()
{
    double a[MAXN]={1,2,3,4,5,6,7,8,9,10};
    double tmp;
    int i;
    start=clock();
    for(i=1;i<=MAXK;i++)
    {
        tmp=f1(MAXN-1,a,1.1);
    }
    stop=clock();
    duration=((double)(stop-start))/CLK_TCK/MAXK;
    printf("tickel=%lf",(double)(stop-start));
    printf("\n duration=%6.2e\n",duration);

    start=clock();
    for(i=1;i<=MAXK;i++)
    {
        tmp=f2(MAXN-1,a,1.1);
    }
    stop=clock();
    duration=((double)(stop-start))/CLK_TCK/MAXK;
    printf("tickel=%lf",(double)(stop-start));
    printf("\n duration=%6.2e\n",duration);

    system("pause");
    return 0;
}

// 推荐第二个算法：降低运行所需时间
// 解决问题效率与解决方式有关