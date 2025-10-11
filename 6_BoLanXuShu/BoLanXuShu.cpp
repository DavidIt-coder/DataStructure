/*
(10以内的后序波兰式求解) 请编写程序求解10以内的后序波兰式的值。
【输入】合法的10以内的后序波兰式
【输出】后序波兰式的值（按照整型计算的结果）
例如：
【输入】23+6*
【输出】30
【输入】23+=
【输出】5
【输入】23+* //非法的后序表达式
【输出】none //表示无对应结果
*/
#include<iostream>
using namespace std;

#define maxstack 100

enum outcome{overflow,underflow,success};

class stack
{
private:
    int count;
    int arr[maxstack+1];
public:
    stack();
    outcome push(const int &item);
    outcome pop();
    outcome top(int &now_top)const;
    bool empty()const;
    bool full()const;
};

stack::stack()
{
    count=0;
}

outcome stack::push(const int &item)
{
    if(count<maxstack)
    {
        count++;
        arr[count]=item;
        return success;
    }
    return overflow;
}

outcome stack::pop()
{
    if(count>0)
    {
        count--;
        return success;
    }
    return underflow;
}


outcome stack::top(int &now_top)const
{
    if(count==0)
        return underflow;
    int& tmp = now_top;
    tmp = arr[count];
    return success;
}

bool stack::empty()const
{
    if(count==0)
        return true;
    return false;
}

bool stack::full()const
{
    if(count==maxstack)
        return true;
    return false;
}

bool match(stack &s,char a,int &k)
{
    int x,y;
    s.top(y);
    s.pop();
    s.top(x);
    s.pop();
    k--;
    switch(a)
    {
    case '+':
        s.push(x+y);
        break;
    case '-':
        s.push(x-y);
        break;
    case '*':
        s.push(x*y);
            break;
    case '/':
        if(y==0)
            return false;
        s.push(x/y);
        break;
    case '=':
        s.push(x);
        s.push(y);
        k++;
        break;
    default:
        return false;
    }
    return true;
}

bool judge(char str[100],stack &s,int &k)
{
    for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            s.push(str[i]-'0');
            k++;
        }
        else
        {
            if(k>=2)
            {
                if(match(s,str[i],k)==false)
                    return false;
            }
            else if(k==1)
            {
                if(str[i]=='=')
                    continue;
                else
                    return false;
            }
            else return false;
        }
    }
    return true;
}

int main()
{
    stack s;
    char str[100];
    cin.getline(str,100);
    int x,k;
    k=0;
    if(judge(str,s,k)==true&&k==1&&s.top(x)==success)
    {
        cout<<x;
        return 0;
    }
    cout<<"none";
    return 0;
}