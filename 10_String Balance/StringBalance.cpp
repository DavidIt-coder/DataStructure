/*
（字符串的平衡性分析）P92 Programming Project 3.3
Write a program that will read one line of input from the terminal. The input is supposed to consist of two parts separated by a colon :. As its result, your program should produce a single character as follows:
N No colon on the line.
L The left part (before the colon) is longer than the right.
R The right part (after the colon) is longer than the left.
D The left and right parts have the same length but are different.
S The left and right parts are exactly the same.
Examples:
Input Output
Sample Sample N
Left:Right R
Sample:Sample S
Dog:Cat D
Rabbit:Dog L
*/
#include <iostream>
#include <string>
using namespace std;

enum outcome{underflow,overflow,success};
#define maxqueue 100
typedef char type;

class cirqueue
{
private:
    type arr[maxqueue];
    int count;
    int front,rear;
public:
    cirqueue();
    int size()const;
    bool empty()const;
    bool full()const;
    void clear();
    outcome append(const type &item);
    outcome serve();
    outcome retrieve(type &item)const;
    outcome serve_and_retrieve(type &item);
    outcome deserve();
    outcome deretrieve(type &item)const;
    outcome deserve_and_deretrieve(type &item);
};

void input(string &x,cirqueue &c1,cirqueue &c2,int &k)
{
    for(char c:x)
    {
        if(c==':')
        {
            k=1;
            continue;
        }
        if(k==0)
            c1.append(c);
        else
            c2.append(c);
    }
}

bool equal(cirqueue &c1,cirqueue &c2)
{
    int num=c1.size();
    char x,y;
    for(int i=0;i<num;i++)
    {
        c1.serve_and_retrieve(x);
        c2.serve_and_retrieve(y);
        if(x!=y)
            return false;
    }
    return true;
}

int output(cirqueue &c1,cirqueue &c2,int k)
{
    int l1=c1.size();
    int l2=c2.size();
    if(k==0)
        return 0;
    else if(l1>l2)
        return 1;
    else if(l1<l2)
        return 2;
    else if(l1==l2)
    {
        if(equal(c1,c2)==true)
            return 3;
        return 4;
    } 
}

int main()
{
    int n,k;
    cin>>n;
    int c[n];
    getchar();
    string x;
    cirqueue c1,c2;
    for(int i=0;i<n;i++)
    {
        c1.clear();
        c2.clear();
        k=0;
        getline(cin,x);
        input(x,c1,c2,k);
        c[i]=output(c1,c2,k);
    }
    for(int i=0;i<n;i++)
    {
        switch(c[i])
        {
            case 0:
                cout<<"N"<<endl;
                break;
            case 1:
                cout<<"L"<<endl;
                break;
            case 2:
                cout<<"R"<<endl;
                break;
            case 3:
                cout<<"S"<<endl;
                break;
            default:
                cout<<"D"<<endl;
                break;
        }
    }
    return 0;
}

cirqueue::cirqueue()
{
    front=0;
    rear=maxqueue-1;
    count=0;
}

bool cirqueue::empty()const
{
    return count==0;
}

outcome cirqueue::append(const type &item)
{
    if(count>=maxqueue)
        return overflow;
    count++;
    rear=((rear+1)==maxqueue)?0:rear+1;
    arr[rear]=item;
    return success;
}

outcome cirqueue::serve()
{
    if(count<=0)
        return underflow;
    count--;
    front=((front+1)==maxqueue)?0:front+1;
    return success;
}

outcome cirqueue::deserve()
{
    if(count<=0)
        return underflow;
    count--;
    rear=((rear-1)==-1)?maxqueue:rear-1;
    return success;
}

outcome cirqueue::retrieve(type &item)const
{
    if(count<=0)
        return underflow;
    type& t=item;
    t=arr[front];
    return success;
}

outcome cirqueue::deretrieve(type &item)const
{
    if(count<=0)
        return underflow;
    type& t=item;
    t=arr[rear];
    return success;
}

int cirqueue::size()const
{
    return count;
}

bool cirqueue::full()const
{
    return count==maxqueue;
}

void cirqueue::clear()
{
    front=0;
    rear=maxqueue-1;
    count=0;
}

outcome cirqueue::serve_and_retrieve(type &item)
{
    if(count<=0)
        return underflow;
    type& t=item;
    t=arr[front];
    front=((front+1)==maxqueue)?0:front+1;
    count--;
    return success;
}

outcome cirqueue::deserve_and_deretrieve(type &item)
{
    if(count<=0)
        return underflow;
    type& t=item;
    t=arr[rear];
    rear=((rear-1)==-1)?maxqueue:rear-1;
    count--;
    return success;
}