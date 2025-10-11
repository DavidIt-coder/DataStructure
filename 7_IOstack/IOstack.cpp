/*
假设以I和O分别表示入栈和出栈操作。栈的初态和终态均为空，
入栈和出栈的操作序列可表示为仅由I和O组成的序列，可以操作的序列称为称为合法序列，否则称为非法序列。
例如：
A.IOIIOIOO 合法 B.IOOIOIIO 不合法
C.IIIOIOIO 合法 D.IIIOOIOO 合法
请写出一个算法，判断所给的操作序列是否合法。若合法，返回true，否则返回false
【输入】n n条I和O组成的序列(序列长度<=80)
【输出】n条序列的判断结果（true或者false）
例如：
【输入】
3
IOIIOIOO
IOOIOIIO
IIIOIOIO

【输出】
true
false
true
*/
#include<iostream>
#include<string>
using namespace std;

int main()
{
    int n,k;
    cin>>n;
    for(int j=0;j<n;j++)
    {
        k=0;
        string s;
        cin>>s;  
        int count=0;
        for(int i=0;s[i]!='\0';i++)
        {
            if(s[i]=='I')
                count++;
            else if(s[i]=='O')
            {
                if(count==0)
                {
                    k=1;
                    break;
                }
                count--;
            }
            else
            {
                k=1;
                break;
            }
        }
        if(k==1)
            cout<<"false"<<endl;
        else cout<<"true"<<endl;
    }
    return 0;
}