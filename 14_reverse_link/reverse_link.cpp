/*
（链表置逆）设有一个表头指针为h的单链表。
试设计一个算法，通过遍历一趟链表，将链表中所有结点的链接方向逆转。
要求逆转结果链表的表头指针h指向原链表的最后一个结点。
*/
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

void reverse(node *&head,node *&prev,node *&head2)
{
    node *pre=NULL;
    for(node *cur=head,*next;cur!=NULL;)
    {
        next=cur->next;
        cur->next=pre;
        pre=cur;
        cur=next;
    }
    head2=pre;
}

int main()
{
    int n,m;
    cin>>n;
    cin>>m;
    node *prev=new node(m);
    node *head=prev;
    for (int i=1;i<n;i++)
    {
        cin>>m;
        node *newptr=new node(m);
        prev->next=newptr;
        prev=newptr;
    }
    node *head2;
    reverse(head,prev,head2);
    for (node *p=head2;p!=NULL;p=p->next)
        cout<<p->entry<<" ";
    while(head!=0)
    {
        node*p=head;
        head=head->next;
        delete p;
    }
    return 0;
}