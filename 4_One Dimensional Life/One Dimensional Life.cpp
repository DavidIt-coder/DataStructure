/*
One-Dimensional Life:alignas
One-Dimensional Life takes place on a straight line instead of a rectangular grid. 
Each cell has four neighboring positions: 
those at distance one or two from it on each side. 
The rules are similar to those of two-dimensional Life 
    except (1) and (2) 
a dead cell with either two or three living neighbors will become alive in the next generation,
a living cell dies if it has zero, one, or three living neighbors. 
(Hence a dead cell with zero, one, or four living neighbors stays dead; 
 a living cell with two or four living neighbors stays alive.) 
The progress of sample communities is shown in Figure 1.6(Textbook page44）. 
Design, write, and test a program for one-dimensional Life.
The total count of the cells is less than 60.

Input: the position of living cells 
(1<=postion<=60. Terminate the list with the special number -1).
The number (n) of generation. (n=0 means the initial Grid)
Output: the next n generations of the grid.

For example：
【输入】
5 7 -1
1
【输出】

-----*------------------------------------------------------
*/
#include<iostream>
#include<cstdio>

using namespace std;

class life
{
private:
    int a[63];
public:
    void initialize();
    void judge();
    void upgrade();
    void print();
};

void life::initialize()
{
    for(int i=0;i<63;i++)
        a[i]=0;
    int n=0;
    cin>>n;
    while(n!=-1)
    {
        a[n]=1;
        cin>>n;
    }
}

void life::print()
{
    for(int i=1;i<61;i++)
    {
        if(a[i])
            cout<<"*";
        else
            cout<<"-";
    }
    cout << endl; // 换行以分隔不同代数的输出
}

void life::judge()
{
    int b[65] = {0};
    for(int i=1;i<=60;i++)
    {
        int nei = 0;
        for(int j=i-2; j<=i+2; j++)
        {
            if(j>=1 && j<=60 && j!=i) // 确保j在有效范围内
            {
                if(a[j])
                    nei++;
            }
        }
        // 根据邻居数量更新状态
        if(nei == 2 || (nei == 3 && !a[i]))
            b[i] = 1;
        else if(nei == 4 && a[i])
            b[i] = 1;
    }
    // 将新状态复制到原数组中
    for(int i=1; i<=60; i++)
    {
        a[i] = b[i];
    }
}

void life::upgrade()
{
    int k=0;
    cin>>k;
    for(int i=0;i<k;i++)
    {
        life::judge();
    }
    life::print(); // 每一代后输出当前状态
}

int main()
{
    life Life;
    Life.initialize();
    Life.upgrade();
    return 0;
}