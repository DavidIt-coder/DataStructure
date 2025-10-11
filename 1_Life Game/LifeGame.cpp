/*
Life Game
Definitions：
Life is really a simulation, not a game with players. 
It takes place on unbounded rectangular grid in which each cell can either be occupied 
by an organism or not. 
Occupied cells are called alived; unoccupied cells are called dead. 
Which cells are alive changes from generation to generation according to the number of 
neighboring cells that are alive, as follows transition rules:
(1) The neighbors of a given cell are the eight cells that touch it vertically, horizontally, 
    or diagonally.
(2) If a cell is alive but either has no neighboring cells alive or only one alive, 
    then in the next generation the cell dies of loneliness.
(3) If a cell is alive and has four or more neighboring cells also alive, then 
    in the next generation the cell dies of overcrowding.
(4) A living cell with either two or three living neighbors remains alive in the next generation.
(5) If a cell is dead, then in the next generation it will become alive 
    if it has exactly three neighboring cells, no more or fewer, that are already alive. 
    All other dead cells remain dead in the next generation.
(6) All births and deaths take place at exactly the same time.
(7) The size of grid is 20*60（棋盘有20行输入范围1-20，有60列输入范围1-60）

Input: the coordinates of living cells (Terminate the list with the special pair -1 -1).
The number (n) of generation. (n=0 means the initial Grid)
Output: the next n generations of the grid.

For example：
【输入】
5 3
5 4
5 5
5 6
-1 -1 //输入结束
3 //输出第3代的结果
【输出】

------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
---**-------------------------------------------------------
--*--*------------------------------------------------------
---**-------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
定义：
生活真的是一场模拟，而不是与玩家的游戏。
它发生在无界矩形网格上，其中每个单元格都可以被占用
无论是否是生物体。
被占领的细胞被称为活细胞；未被占用的细胞被称为死细胞。
哪些细胞是活的，会根据细胞的数量代代相传
如以下转换规则所示：
（1） 给定单元的邻居是垂直、水平和垂直接触它的八个单元，
或对角线。
（2） 如果一个细胞是活的，但没有相邻的活细胞或只有一个活细胞，
然后，在下一代，细胞会因孤独而死亡。
（3） 如果一个细胞是活的，并且有四个或更多的相邻细胞也是活的，那么
在下一代，牢房因过度拥挤而死亡。
（4） 一个有两个或三个活邻居的活细胞在下一代中仍然存活。
（5） 如果一个细胞已经死亡，那么在下一代中它将变得活着
如果它恰好有三个相邻的已经存活的细胞，不多也不少。
所有其他死细胞在下一代中仍然死亡。
（6） 所有的出生和死亡都发生在同一时间。
（7） 网格尺寸为20*60（有20个输入框1-20，有60个输入框1-60）

输入：活细胞的坐标（用特殊对-1-1终止列表）。
世代数（n）。（n=0表示初始网格）
输出：下一代的网格。
*/


//version 1 :
#include<cstdio>
#include<iostream>
using namespace std;

int rule(int x,int y,int a[22][62])
{
    int k=0;
    for(int i=x-1;i<x+2;i++)
    {
        for(int j=y-1;j<y+2;j++)
        {
            if(a[i][j]==1&&(i!=x||j!=y))
                k++;
        }
    }
    if(k==3)
        return 1;
    else if(k==2&&a[x][y]==1)
        return 1;
    else
        return 0;
}

int next_generation(int a[22][62])
{
    int net[22][62];
    for(int i=0;i<22;i++)
    {
        for(int j=0;j<62;j++)
        {
            net[i][j]=a[i][j];
        }
    }
    for(int i=1;i<21;i++)
    {
        for(int j=1;j<61;j++)
        {
            a[i][j]=rule(i,j,net);
        }
    }
}

void Printf(int a[22][62])
{
    for(int i=1;i<21;i++)
    {
        for(int j=1;j<61;j++)
        {
            if(a[i][j]==1)
                printf("*");
            else
                printf("-");
        }
        printf("\n");
    }
}

int main()
{
    int network[22][62];
    for(int i=0;i<22;i++)
    {
        for(int j=0;j<62;j++)
        {
            network[i][j]=0;
        }
    }
    int x,y,n;
    cin>>x>>y;
    while(x!=-1&&y!=-1)
    {
        network[x][y]=1;
        cin>>x>>y;
    }
    cin>>n;
    for(int i=0;i<n;i++)
        next_generation(network);
    Printf(network);
    return 0;
}