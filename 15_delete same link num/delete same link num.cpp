/*
（删除链表中的重复元素）请编写程序删除链表中的多余节点，
即：若链表中有多个节点具有相同的值，则只保留其中的一个节点即可，使得处理后的链表中的值各不相同。
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

void deletesame(node *&head)
{
    for(node *p=head;p!=NULL;p=p->next)
    {
        node *q=p;
        while(q->next!=NULL)
        {
            if(p->entry==q->next->entry)
            {
                node *temp=q->next;
                if(q->next->next==NULL)//temp->next==NULL
                {
                    delete temp;
                    q->next=NULL;
                    break;
                }
                q->next=temp->next;
                delete temp;
            }
            else q=q->next;
        }
    }
}

int main()
{
    int n,m;
    cin>>n;
    cin>>m;
    if(n==1)
    {
        cout<<m;
        return 0;
    }
    node *prev=new node(m);
    node *head=prev;
    for (int i=1;i<n;i++)
    {
        cin>>m;
        node *newptr=new node(m);
        prev->next=newptr;
        prev=newptr;
    }
    deletesame(head);
    while(head!=0)
    {
        node*p=head;
        cout<<p->entry<<" ";
        head=head->next;
        delete p;
    }
    return 0;
}