#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

#define maxstack 1501

enum outcome{overflow,underflow,success};

class stack
{
private:
    int count;
    char arr[maxstack+1];
public:
    int k,block,quote,judge;
    stack();
    outcome push(const char &item);
    outcome pop();
    outcome top(char &now_top)const;
    bool empty()const;
    bool full()const;
    bool in_string(char c,char d);
    bool in_line(char a,char b);
    bool in_block(char x,char y);
    int match(char y);
    int matching(char y);
    void is_matched(string str);
};

stack::stack()
{
    count=k=block=quote=0;
    judge=1;
}

outcome stack::push(const char &item)
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


outcome stack::top(char &now_top)const
{
    if(count==0)
        return underflow;
    char& tmp = now_top;
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

int stack::matching(char y)
{
    char x;
    k++;
    if(empty()==false)
    {
        top(x);
        pop();
        if((x=='('&&y==')')||(x=='['&&y==']')||(x=='{'&&y=='}'))
            return 0;
    }
    judge=0;
    return 0;
}

int stack::match(char y)
{
    if(y=='('||y=='['||y=='{')
    {
        k++;
        push(y);
    }
    else if(y==')'||y==']'||y=='}')
        matching(y);
    return 0;
}

void stack::is_matched(string str)
{
    for(int i=0;str[i]!='\0';i++)
    {
        if(in_string(str[i],str[i-1])==false)
        {      
            if(in_line(str[i],str[i+1])==true)
                break;
            if(in_block(str[i],str[i+1])==true)
                continue; 
        }
        match(str[i]);
    }
}

bool stack::in_string(char c,char d)
{
    if(c=='"'&&d!='\\')
        quote++;
    if(quote%2==0)
        return false;
    return true;
}

bool stack::in_line(char a,char b)
{
    if(a=='/'&&b=='/')
        return true;
    return false;
}

bool stack::in_block(char x,char y)
{
    if(x=='/'&&y=='*')
        block=1;
    else if(x=='*'&&y=='/')
        block=0;
    if(block==1)
        return true;
    return false;
}

int main()
{
    stack s;
    string str;
    while(getline(cin,str))
    {
        s.is_matched(str);
    }
    if(s.judge==1&&s.empty()==true)
        cout<<s.k<<" yes";
    else
        cout<<s.k<<" no";
    return 0;
}