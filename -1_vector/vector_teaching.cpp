#include<bits/stdc++.h>//万能头文件
#include<vector>//vector头文件
using namespace std;
/*
    
    */

int main()
{   
    vector<int>vec;//vector<数据类型>vec;声明一个叫作vec的int类型的动态数组,数据类型可自定义
    vector<int>vec1,vec2;
    vec.push_back(1);//目前[1]
    vec.push_back(2);//[1,2]
    vec.push_back(3);//[1,2,3]
    vec.pop_back();//[1,2]
    vec.pop_back();//[1]
    vec.pop_back();//[]
    vec.pop_back();//出错
    vec.size(); //返回vec的大小,动态数组的大小范围为[0,vec.size()-1]
    for(int i=0;i<vec.size();i++)
        cout<<vec[i]<<" ";//输出数组元素
    vec[0]=2;//修改数组元素
    vector<int>().swap(vec);//动态数组清空所有数据并释放内存
    vec.empty();//判断动态数组是否为空
    vec1=vec2;//赋值运算符
    sort(vec.begin(),vec.end());//升序排序
    sort(vec.begin(),vec.begin()+2,greater<int>());//降序排序
    vector<int>vec(100,0);//初始化100个元素为0的数组
    return 0;
}