/*
A magic square is a square array or integers such that the sum of every row, 
the sum of every column, and sum of each of the two diagonals are all equal.
Write a program that generates a magic square by the following method. 
This method works only when the size of the square is an odd number. 
Start by placing 1 in the middle of the top row. 
Write down successive integers 2, 3, … along a diagonal going upward and to the right. 
When you reach the top row(as you do immediately since 1 is in the top now), 
continue to the bottom row as though the bottom row were immediately above the top row. 
When you reach the rightmost column, 
continue to the leftmost column as though it were immediately to the right of the rightmost one.
When you reach a position that is already occupied, 
instead drop straight down one position from the previous number to insert the new one. 
The 5*5 magic square constructed by this method is shown as follows.
17 24 1 8 15
23 5 7 14 16
4 6 13 20 22
10 12 19 21 3
11 18 25 2 9

【输入】奇数n，1<=n<=101.
【输出】
n
×
n
n×n的magic square.(数字之间为两个空格，每行最后一个数字后面无空格。)

For example,
【输入】 5
【输出】
17  24  1  8  15
23  5  7  14  16
4  6  13  20  22
10  12  19  21  3
11  18  25  2  9


幻方是一个正方形数组或整数，使得每一行的和,每一列的和 和两个对角线中的每一个的和 都相等。
写一个程序，用下面的方法生成一个幻方。
此方法仅在正方形的大小为奇数时有效。
从在上一行中间放置1开始。
沿着向上和向右的对角线写下连续的整数2、3......。
当您到达顶端行时（因为现在1在顶端，所以您会立即这样做），
继续到底行，好像底行紧挨着顶行。
当你到达最右边的栏时，
继续到最左边的列，好像它就在最右边的列的右边。
当你到达一个已经被占用的职位时，
相反，从上一个数字直接向下下降一个位置，插入新的数字。

*/

#include<iostream>
#include<cstdio>

using namespace std;

class MagicSquare
{
private:
    int n;
    int a[102][102];
public:
    void initialize();
    void progrise();
    void print();
};


void MagicSquare::initialize()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
           a[i][j]=0;
        }
    }
}

void MagicSquare::print()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
           printf("%d",a[i][j]);
           cout<<" "<<' ';
        }
        cout<<endl;
    }
}

void MagicSquare::progrise()
{
    int t=2;
    int x,y;
    x=1;
    y=(n+1)/2;
    a[x][y]=1;
    while(t<=n*n)
    {
        if(x==1&&y!=n)
        {
            x=n;
            y++;
        }
        else if(x!=1&&y==n)
        {
            x--;
            y=1;
        }
        else if(x==1&&y==n)
        {
            x=n;
            y=1;
        }
        else
        {
            x--;
            y++;
        }
    judge:
        if(a[x][y]!=0)
        {
            if(x==n&&y==1)
            {
                x=1;
                y=n;
            }
            else
            {
                x++;
                y--;
            }
            if(x==n)
                x=1;
            else
                x++;
            goto judge;
        }
        else
        {
            a[x][y]=t;
            t++;
        }
    }
}

int main()
{
    MagicSquare ms;
    ms.initialize();
    ms.progrise();
    ms.print();
    return 0;
}