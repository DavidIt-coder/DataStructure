/*
（前向和后向的最近邻值）给定一个包含有m个节点的双链表，链表每个节点的值均为正整数：
（1）节点i的前向最近邻值需要满足j小于i,且节点j的值小于节点i的值，j为满足条件的最大位置点。
节点j的值即为节点i的前向最近邻值。若j不存在，节点i的前向最近邻值为0。
（2）节点i的后向最近邻值需要满足j大于i,且节点j的值大于节点i的值，j为满足条件的最小位置点。
节点j的值即为节点i的后向最近邻值。若j不存在，节点i的后向最近邻值为0。
【输入】双链表中的m个值以-1结束
【输出】
按顺序输出每个节点的前向最近邻值；
按顺序输出每个节点的后向最近邻值；
例如：
【输入】 2 1 5 -1
【输出】
0 0 1
5 5 0
【输入】 2 7 3 4 5 -1
【输出】
0 2 2 3 4
7 0 4 5 0
*/
#include<iostream>
#include<string>
using namespace std;
enum Error_code{success,underflow,overflow,rangeerror,not_present};
const int max_list=2000;

typedef int List_entry;
struct Node
{
    List_entry entry;
    Node *next;
    Node();
    Node(List_entry item,Node* add=NULL);
};

class List
{
public:
    List(); 
    ~List(); 
    List(const List &copy); 
    void operator=(const List &copy); 
    int size() const; 
    bool full() const; 
    bool empty() const; 
    void clear(); 
    Error_code insert(int position,const List_entry &x); 
    Error_code remove(int position,List_entry &x); 
    Error_code replace(int position,const List_entry &x); 
    Error_code retrieve(int position,List_entry &x)const; 
    void traverse(void (*visit)(List_entry &)); 
protected:
    int count; 
    Node *head; 
    Node *set_position(int position)const; 
    mutable int current_position;
	mutable Node *current;
};

Node::Node()
{
    next=NULL;
}

Node::Node(List_entry item,Node* add)
{
    entry=item;
    next=add;
}

List::List()
{
    count=0;
    head=NULL;
}

Node* List::set_position(int position)const
{
    Node* q=head;
    for(int i=0;i<position;i++)
        q=q->next;
    return q;
}

List::~List()
{
    clear();
}

List::List(const List &copy)
{
    count=0;
    head=NULL;
    Node *q=copy.head;
    while(q!=NULL)
    {
        insert(count,q->entry);
        q=q->next;
    }
}

void List::operator = (const List &copy)
{
    if(this==&copy)
        return;
    clear();
    Node* q=copy.head;
    int i=0;
    while(q!=NULL)
    {
        insert(i,q->entry);
        q=q->next;
        i++;
    }
}

int List::size() const
{
    return count;
}

bool List::full() const
{
    if(count==max_list)
        return true;
    return false;
}

bool List::empty() const
{
    if(count==0)
        return true;
    return false;
}

void List::clear()
{
    List_entry x;
    while(!empty())
        remove(0,x);
}

Error_code List::insert(int position,const List_entry &x)
{
    if(full())
        return overflow;
    if(position<0||position>count)
        return rangeerror;
    Node* new_node,*previous,*following;
    if(position>0)
    {
        previous=set_position(position-1);
        following=previous->next;
    }
    else following=head;
    new_node=new Node(x,following);
    if(position==0)
        head=new_node;
    else 
        previous->next=new_node;
    count++;
    return success;
}

Error_code List::remove(int position,List_entry &x)
{
    if(empty( ))
        return underflow;
    if(position<0||position>=count)
        return rangeerror;
    Node *previous,*following;
    if(position==0)
    {
        following=head;
        head=head->next;
    }
    else
    {
        previous=set_position(position-1);
        following=previous->next;
        previous->next=following->next;
    }
    List_entry& y=x;
    y=following->entry;
    delete following;
    count--;
    return success;
}

Error_code List::replace(int position,const List_entry &x)
{
    if(position<0||position>=count)
        return rangeerror;
    Node *p=set_position(position);
    p->entry=x;
 return success;
}

Error_code List::retrieve(int position,List_entry &x)const
{
    if(position<0||position>=count)
        return rangeerror;
    Node *p=set_position(position);
    List_entry &y=x;
    y=p->entry;
    return success;
}

void List::traverse(void (*visit)(List_entry &))
{
    Node *p=head;
    while(p!=NULL)
    {
        (*visit)(p->entry);
        p=p->next;
    }
}

void initialize(List &l,List &front,List_entry &x)
{
    while(cin>>x&&x!=-1)
    {
        int k=l.size();
        if(k==0)
            front.insert(front.size(),0);
        l.insert(k,x);
        for(int i=k-1;i>=0;i--)
        {
            int num;
            l.retrieve(i,num);
            if(num<x)
            {
                front.insert(front.size(),num);
                break;
            }
            if(i==0)
                front.insert(front.size(),0);
        }
    }
}

void behind_printfront(List &l,List &front,List &behind)
{
    for(int i=0;i<l.size();i++)
    {
        if(i==l.size()-1)
            behind.insert(behind.size(),0);
        int num;
        l.retrieve(i,num);
        for(int j=i+1;j<l.size();j++)
        {
            int temp;
            l.retrieve(j,temp);
            if(temp>num)
            {
                behind.insert(behind.size(),temp);
                break;
            }
            if(j==l.size()-1)
                behind.insert(behind.size(),0);
        }
        front.retrieve(i,num);
        cout<<num<<" ";
    }
    cout<<endl;
}

void printbehind(List &l,List &behind)
{
    for(int i=0;i<l.size();i++)
    {
        int num;
        behind.retrieve(i,num);
        cout<<num<<" ";
    }
    cout<<endl;
}

int main()
{
    int x;
    List l,front,behind;
    initialize(l,front,x);
    behind_printfront(l,front,behind);
    printbehind(l,behind);
    return 0;
}