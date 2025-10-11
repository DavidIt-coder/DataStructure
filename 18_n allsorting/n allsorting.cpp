/*
给定整数n，n<=10，请求出n的全排列。
N=3时，1-3的排列可以为：
1:1 2 3
2:1 3 2
3:2 1 3
4:2 3 1
5:3 1 2
6:3 2 1
一共有6种情况
【输入】 整数n，n<=20
【输出】
1-n的排列 （排列数大于10的，仅输出前10组即可）
总的全排列数，do not need to按字典序输出。
例如：
【输入】 4
【输出】
1:1 2 3 4
2:1 2 4 3
3:1 3 2 4
4:1 3 4 2
5:1 4 2 3
6:1 4 3 2
7:2 1 3 4
8:2 1 4 3
9:2 3 1 4
10:2 3 4 1
24
*/
#include <iostream>
using namespace std;

class permutation
{
public:
    permutation(int N);
    void print()const;
    void swap(int &x,int &y);
    void solution(int step);
    int count;
private:
    int n;
    int num[20+1];
};

int main() 
{
    int n;
    cin>>n;
    permutation p(n);
    p.solution(0);
    cout<<p.count;
    return 0;
}

permutation::permutation(int N)
{
    n=N;
    count=0;
    for(int i=0;i<n;i++)
        num[i]=i+1;
}

void permutation::print()const
{
    if(count<=10)
    {
        cout<<count<<":";
        for(int i=0;i<n;i++)
            cout<<num[i]<<" ";
        cout<<endl;
    }
}

void permutation::swap(int &x,int &y)
{
    int &t1=x,&t2=y,t;
    t=t1;
    t1=t2;
    t2=t;
}

void permutation::solution(int step)
{  
    if(step==n-1)
    {
        count++;
        print();
    }
    else
    {
        for(int i=step;i<n;i++)
        {
            swap(num[step],num[i]);
            solution(step+1);
            swap(num[step],num[i]);
        }
    }
}
