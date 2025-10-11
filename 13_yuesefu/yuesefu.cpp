#include <iostream>
using namespace std;

enum  outcome{underflow, overflow, success};
#define maxqueue 100
typedef int type;

struct node
{
    type entry;
    node *next;
    node();
    node(type item,node* add=NULL);
};

node::node()
{
    next=NULL;
}

node::node(type item,node* add)
{
    entry=item;
    next=add;
}

void game(int &n,int m)
{
    node *head=new node(1);
    node *prev=head;
    for (int i=2;i<=n;i++)
    {
        node *newptr=new node(i);
        prev->next=newptr;
        prev=newptr;
        if(i==n)
            prev->next=head;
    }
    node *cur=head;
    int k=1;
    for(prev=NULL;cur!=cur->next;)
    {
        if(k==m)
        {
            k=1;
            n--;
            node *temp=cur;
            cur=cur->next;
            prev->next=cur;
            delete temp;
            continue;
        }
        k++;
        prev=cur;
        cur=cur->next;
    }
    cout<<cur->entry;
    delete cur;
}

int main()
{
    int n,m;
    cin>>n>>m;
    if(m==1)
    {
        cout<<n;
        return 0;
    }
    game(n,m);
    return 0;
}