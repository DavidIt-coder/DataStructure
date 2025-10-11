/*
（Start and end position）Given an array of integers numbers sorted in ascending order,
find the starting and ending position of a given target value. 
Your algorithm’s runtime complexity must be in the order of O(log n). 
If the target is not found in the array, return [-1, -1].
【输入】
第一行，要查找的目标值
第二行，值按升序排列的整数数组，数组以-1结束（数组长度小于2000）
【输出】 目标值在数组里，第一次以及最后一次出现的下标
例如：
【输入】
8
5 7 7 8 8 10 -1
【输出】
[3,4]
【输入】
6
5 7 7 8 8 10 -1
【输出】
[-1,-1]
*/
#include<iostream>
using namespace std;

void first(int arr[],int target,int length)
{
    int left=0,right=length-1;
    while(left<=right)
    {
        int mid=(left+right)/2;
        if(arr[mid]>=target)
            right=mid-1;
        else
            left=mid+1;
    }
    if(left<length&&arr[left]==target)
        cout<<"["<<left<<",";
    else
        cout<<"["<<-1<<",";
}

void last(int arr[],int target,int length)
{
    int left=0,right=length-1;
    while(left<=right)
    {
        int mid=(left+right)/2;
        if(arr[mid]<=target)
            left=mid+1;
        else
            right=mid-1;
    }
    if(right>=0&&arr[right]==target)
        cout<<right<<"]";
    else
        cout<<-1<<"]";
}

int main()
{
    int target,num,length=0;
    cin>>target;
    int arr[2001];
    while(cin>>num&&num!=-1)
    {
        arr[length]=num;
        length++;
    }
    first(arr,target,length);
    last(arr,target,length);
    return 0;
}