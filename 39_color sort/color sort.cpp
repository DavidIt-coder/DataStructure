/*
Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue. Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
请尝试编写适合该问题的排序算法。
最合适该问题的算法复杂度可控制在O(n)，辅助空间为常数。
【输入】0，1，2组成的任意整数序列，序列长度小于10000。
【输出】输出整数序列的顺序序列
例如：
【输入】2 0 2 1 1 0
【输出】0 0 1 1 2 2

counting sort算法是一种简单有效的排序算法，其时间复杂度为O(n)，辅助空间为O(1)。
计数排序的基本思想是：遍历输入数据，统计每个元素出现的频率，并根据频率将元素分配到输出数组中。
*/
#include <iostream>
using namespace std;

int main()
{
    int n,color[3];
    color[0]=color[1]=color[2]=0;
    while (cin>>n) 
    {
        if(n==0) 
            color[0]++;
        else if(n==1) 
            color[1]++;
        else
            color[2]++;
    }
    for(int i=0;i<3;i++) 
    {
        int temp=color[i];
        for (int j=0;j<temp;j++) 
            cout<<i<<' ';
    }
    return 0;
}
