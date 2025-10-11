/*
（Sqrt function）Implement int sqrt(int x).
Compute and return the square root of x, where x is guaranteed to be a non-negative integer.
Since the return type is an integer, 
the decimal digits are truncated and only the integer part of the result is returned.
【输入】x的值，x为整数
【输出】x的平方根（整数）
例如：
【输入】 4
【输出】 2
【输入】 8
【输出】 2 //8的开方为2.82842，结果只需要输出整数，故输出2即可。
*/
#include <iostream>
using namespace std;

long long int sqrt(int x)
{
    long long int left=0,right=x;
    while(left<=right)
    {
        long long int mid=(left+right)/2;
        if(mid*mid<=x)
            left=mid+1;
        else
            right=mid-1;
    }
    return right;
}

int main()
{
    long long int x;
    cin>>x;
    cout<<sqrt(x);
    return 0;
}