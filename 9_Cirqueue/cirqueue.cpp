#include<iostream>
using namespace std;

enum  outcome{underflow, overflow, success};
#define maxqueue 100
typedef char type;

class cirqueue
{
public:
   cirqueue();
   bool empty()const;
   outcome append(const type &item);
   outcome serve();
   outcome retrieve(type &item)const;
   bool full()const;
   int size()const;
   void clear();
   outcome serve_and_retrieve(type &item);
   outcome deserve();
   outcome deretrieve(type &item)const;
   outcome deserve_and_deretrieve(type &item);
private:
   int count;
   int front,rear;
   type arr[maxqueue];
};

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

int main()
{
    cirqueue c;
    int n;
    cin>>n;
    char x;
    while(cin>>x)
    {
        if(c.full()==false)
            c.append(x);
        else
        {
            c.serve();
            c.append(x);
        }
    }
    int t=(n>c.size())?c.size():n;
    for(int i=0;i<t;i++)
    {
        c.deserve_and_deretrieve(x);
        cout<<x<<' ';
    }
    return 0;
}
