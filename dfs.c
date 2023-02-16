#include <stdio.h>

/*// 终点坐标
int endx,endy;
int min=99999;
// 0表示空地,1表示障碍物
int Map[1000][1000];
// 0表示未访问，1表示访问
int Traits[1000][1000]={0};

void dfs(int x,int y,int step)
{
    if(x==endx&&y==endy)
    {
        if(step<min)
            min=step;
        return;//回溯寻找更小值
    }
    // 顺时针试探
    // 右
    if(!Map[x+1][y]&&!Traits[x+1][y])
    {
        Traits[x+1][y]=1;//已访问
        dfs(x+1,y,step+1);
        Traits[x+1][y]=0;//检索完成 回到此节点时修改为未访问
    }
    // 下
    if(!Map[x][y+1]&&!Traits[x][y+1])
    {
        Traits[x][y+1]=1;//已访问
        dfs(x,y+1,step+1);
        Traits[x][y+1]=0;//检索完成 回到此节点时修改为未访问
    }
    // 左
    if(!Map[x-1][y]&&!Traits[x-1][y])
    {
        Traits[x-1][y]=1;//已访问
        dfs(x-1,y,step+1);
        Traits[x-1][y]=0;//检索完成 回到此节点时修改为未访问
    }
    // 上
    if(!Map[x][y-1]&&!Traits[x][y-1])
    {
        Traits[x][y-1]=1;//已访问
        dfs(x,y-1,step+1);
        Traits[x][y-1]=0;//检索完成 回到此节点时修改为未访问
    }
}

int main()
{
    int startx,starty;
    int length,width;
    printf("请输入迷宫大小\n");
    scanf("%d%d",&length,&width);
    printf("请输入障碍物(0表示空地,1表示障碍物\n");
    for(int i=0;i<length;i++)
        for(int j=0;j<width;j++)
            scanf("%d",&Map[i][j]);
    printf("请输入起点坐标\n");
    scanf("%d%d",&startx,&starty);
    printf("请输入终点坐标\n");
    scanf("%d%d",&endx,&endy);
    Traits[startx][starty]=1;
    dfs(startx,starty,0);
    printf("最短路径为:%d步",min);

    system("pause");
    return 0;

}*/

int book[51][51],a[51][51];
int n,m,p,q,min=99999;
	int next[4][2]={
 				    {0,1}, //向右走一步
					{1,0},//向下走一步
					{0,-1},//向左走一步
					{-1,0}};//向上走一步

void dfs(int x,int y,int step){   //step用来表示找到小红，小明走了多少步
	int tx,ty,k;
	if(x==p&& y==q){  //说明已经找到了小红  
	/*
	还要说明一点：这里 为什么是（x，y），而不是（tx，xy） 
	其实很简单 就是上一个dfs()函数传过来的坐标 ，做了这个dfs()函数的形参 
	换句话说：就是判断点是否找到小红 
	*/ 
		if(step<min)
			min=step;
		return ;   
		/*返回上一步，继续寻找其他路径（就是退回到上一个坐标，重新找其他路径）
		   回到上一个dfs()函数 
		
		*/ 
		}
		
	for(k=0;k<=3;k++){   //下一步的坐标
		tx=x+next[k][0]; 
		ty=y+next[k][1];
	
			//判断是否越界,越界则重新进入for循环 
			if(tx<1 || tx>n || ty<1 || ty>m)
				continue;  
				//运行到这里，说明这条路，则需要换个方向，也就是重新进入for循环
			if(a[tx][ty]==0 && book[tx][ty]==0){
				book[tx][ty]=1; //标记这个点走过
				dfs(tx,ty,step+1); //进行下一步
				book[tx][ty]=0;   //重新尝试，退回到上一个点的位置
		}
	
		}
		return ;   //执行到这里，这层dfs()函数已经结束，则要回到上一层dfs()函数 
	}

int main(){
	int i,j,startx,starty;
	scanf("%d %d",&n,&m);    //输入迷宫的大小 
	
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]);  //输入迷宫的形状 
	
	scanf("%d %d",&startx,&starty);  //小明的坐标 
	scanf("%d %d",&p,&q);            //小红的坐标 
	
	book[startx][starty]=1;         //起始点标记，就不会回到这个点了 
	dfs(startx,starty,0);      //开始寻找最短路径 
	
	printf("%d",min);        //输出最短路径 

    system("pause");
	return 0;
}
