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
总的全排列数，按字典序输出。
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

#define maxn 20

class permutation
{
public:
    permutation(int N);
    void print()const;
    int solution(int step);
    int count;
private:
    int n;
    int num[maxn]={0};
    int used[maxn]={0};
};

int main()
{
    int n;
    cin>>n;
    permutation p(n);
    p.solution(0);
    p.count=1;
    for(int i=1;i<=n;i++)
        p.count*=i;
    cout<<p.count<<endl;
    return 0;
}

permutation::permutation(int N)
{
    n=N;
    count=0;
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

int permutation::solution(int step)
{
    if(step==n)
    {
        count++;
        print();
    }
    else if(count==10)
        return 0;
    else
    {//need deeply understand this code
        for(int i=0;i<n;i++)
        {
            if(!used[i])
            {
                used[i]=1;
                num[step]=i+1;
                solution(step+1);
                used[i]=0;
            }
        }
    }
    return 0;
}