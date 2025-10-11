#include<iostream>
using namespace std;

#define maxstack 1000

enum outcome{overflow,underflow,success};

template<class stack_entry>
class stack
{
private:
    int count;
    stack_entry arr[maxstack+1];
public:
    stack();
    outcome push(const stack_entry &item);
    outcome pop();
    outcome top(stack_entry &item)const;
    bool empty()const;
    bool full()const;
};

template<class stack_entry>
stack<stack_entry>::stack()
{
    count=0;
}

template<class stack_entry>
outcome stack<stack_entry>::push(const stack_entry &item)
{
    if(count<maxstack)
    {
        count++;
        arr[count]=item;
        return success;
    }
    else
        return overflow;
}

template<class stack_entry>
outcome stack<stack_entry>::pop()
{
    if(count>0)
    {
        count--;
        return success;
    }
    else
        return underflow;
}

template<class stack_entry>
outcome stack<stack_entry>::top(stack_entry &item)const
{
    if(count==0)
        return underflow;
    else
    {
        item=arr[count];
        return success;
    }
}

template<class stack_entry>
bool stack<stack_entry>::empty()const
{
    if(count==0)
        return true;
    return false;
}

template<class stack_entry>
bool stack<stack_entry>::full()const
{
    if(count==maxstack)
        return true;
    return false;
}

int main()
{
    stack<int> s;
    int x=0;
    while(x!=-1)
    {
        cin>>x;
        s.push(x);
    }
    s.pop();
    while(!s.empty())
    {
        s.top(x);
        cout<<x<<' ';
        s.pop();
    }
    return 0;
}

/*
#include<iostream>;
#include<cstdio>;
using namespace std;

enum Error{underflow,overflow,success};
const int maxstack=100;

class MyStack
{
public:
    MyStack();
    bool empty() const;
    Error push(const int &item);
    Error pop();
    Error top(int &item) const;
private:
    int count;
    int entry[maxstack];
};

bool MyStack::empty()const
{
    bool outcome=true;
    if(count>=0)
        outcome=false;
    return outcome;
}

Error MyStack::push(const int &item)
{
    Error outcome=success;
    if(count>=maxstack)
        outcome=overflow;
    else
    {
        count++;
        entry[count]=item;
    }
    return outcome;
}

Error MyStack::pop()
{
    Error outcome=success;
    if(!count)
        outcome=underflow;
    else
        count--;
    return outcome;
}

Error MyStack::top(int &amp;item)const
{
    Error outcome=success;
    if(!count)
        outcome=underflow;
    else
        item=entry[count];
    return outcome;
}

MyStack::MyStack()
{
    count=0;
}

int main()
{
    MyStack s;
    int x=1;
    while(x!=-1)
    {
        cin>>x;
        s.push(x);
    }
    s.pop();
    while(!s.empty())
    {
        s.top(x);
        cout<<x<<' ';
        s.pop();
    }
    return 0;
}
*/