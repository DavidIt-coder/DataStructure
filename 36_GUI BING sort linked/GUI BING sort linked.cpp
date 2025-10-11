/*
请在你实现的链式存储的List基础上实现归并排序。
【输入】
第一行，待排序序列个数n，序列长度小于1000；
第二行，n个整数序列；
【输出】
归并排序的中间结果，即归并前的子序列1和子序列2；
归并排序的最终结果；
例如：
【输入】
5
9 3 8 2 5
【输出】
3 8 9//归并前的子序列1
2 5//归并前的子序列2
2 3 5 8 9
*/
#include<iostream>
using namespace std;
enum Error_code{underflow, overflow, range_Error, success};
typedef int List_entry;
typedef int Node_entry;
bool is_first=true;

struct Node
{
    Node_entry entry;
    Node* next;
    Node();
    Node(Node_entry item, Node* add_on=NULL);
};

Node::Node()
{
    next=NULL;
}

Node::Node(Node_entry item, Node* add_on)
{
    entry=item;
    next=add_on;
}

class List
{
public:
    List();
    ~List();
    List(const List& copy);
    void operator=(const List& copy);
    int size()const;
    bool full()const;
    bool empty()const;
    void clear();
    Node*& get_head();
    Error_code insert(int position, const List_entry& x);
    Error_code remove(int position, List_entry& x);
    Error_code retrieve(int position, List_entry& x)const;
    Error_code replace(int position, List_entry& x);
    void traverse(void(*visit)(List_entry& x));
protected:
    int count;
    Node* head;
    Node* set_position(int position)const;
};

Node* List::set_position(int position)const
{
    Node* q=head;
    for(int i=0;i<position;i++)q=q->next;
    return q;
}

List::List()
{
    count=0;
    head=NULL;
}

List::~List()
{
    List_entry x;
    while(!empty())
        remove(0,x);
}

List::List(const List& copy)
{
    count=0;
    head=NULL;
    Node* newptr=copy.head;
    while(newptr)
    {
        insert(size(),newptr->entry);
        newptr=newptr->next;
    }
}

void List::operator=(const List& copy)
{
    List_entry x;
    if(this==&copy)return;
    while(!empty())remove(0,x);
    Node* newptr=copy.head;
    while(newptr){
        insert(size(),newptr->entry);
        newptr=newptr->next;
    }
}

int List::size()const
{
    return count;
}

bool List::full()const
{
    Node* newptr=new Node();
    if(newptr==NULL)return true;
    delete newptr;
    return false;
}

bool List::empty()const
{
    if(count==0)return true;
    return false;
}

void List::clear()
{
    List_entry x;
    remove(0,x);
}

Error_code List::insert(int position, const List_entry& x)
{
    if(position<0||position>count)return range_Error;
    Node* newptr,* previous=NULL,* following;
    if(position>0){
        previous=set_position(position-1);
        following=previous->next;
    }
    else following=head;
    newptr=new Node(x,following);
    if(newptr==NULL)return overflow;
    if(position==0)head=newptr;
    else previous->next=newptr;
    count++;
    return success;
}

Error_code List::remove(int position, List_entry& x)
{
    if(position<0||position>=count)return range_Error;
    Node* previous,* following;
    if(position>0){
        previous=set_position(position-1);
        following=previous->next;
        previous->next=following->next;
    }
    else{
        following=head;
        head=head->next;
    }
    x=following->entry;
    delete following;
    count--;
    return success;
}

Error_code List::retrieve(int position, List_entry& x)const
{
    if(position<0||position>=count)return range_Error;
    Node* newptr=set_position(position);
    x=newptr->entry;
    return success;
}

Error_code List::replace(int position, List_entry& x)
{
    if(position<0||position>=count)return range_Error;
    Node* newptr=set_position(position);
    newptr->entry=x;
    return success;
}

void List::traverse(void(*visit)(List_entry& x))
{
    Node* newptr=head;
    while(newptr){
        (*visit)(newptr->entry);
        newptr=newptr->next;
    }
}

Node*& List::get_head()
{
    return head;
}

void print(List_entry& x)
{
    cout<<x<<' ';
}

Node* divide_from(Node* sub_list)
{
    Node* position,* midpoint,* second_half;
    if((midpoint=sub_list)==NULL)return NULL;
    position=midpoint->next;
    while(position!=NULL)
    {
        position=position->next;
        if(position!=NULL)
        {
            midpoint=midpoint->next;
            position=position->next;
        }
    }
    second_half=midpoint->next;
    midpoint->next=NULL;
    return second_half;
}

Node* merge(Node* first, Node* second)
{
    Node* last_sorted;
    Node combined;
    last_sorted=&combined;
    while(first!=NULL&&second!=NULL)
    {
        if(first->entry<=second->entry)
        {
            last_sorted->next=first;
            last_sorted=first;
            first=first->next;
        }
        else
        {
            last_sorted->next=second;
            last_sorted=second;
            second=second->next;
        }
    }
    if(first==NULL)
        last_sorted->next=second;
    else
        last_sorted->next=first;
    return combined.next;
}

void recursive_Mergesort(Node*& sub_list)
{
    if(sub_list!=NULL&&sub_list->next!=NULL)
    {
        Node* second_half=divide_from(sub_list);
        recursive_Mergesort(sub_list);
        recursive_Mergesort(second_half);
        sub_list=merge(sub_list,second_half);
    }
}

int main()
{
    List a,b,c;
    int n,num;
    cin>>n;
    if(n%2==0)
    {
        for(int i=0;i<n/2;i++)
        {
            cin>>num;
            a.insert(i,num);
        }
        for(int i=0;i<n/2;i++)
        {
            cin>>num;
            b.insert(i,num);
        }
    }
    else{
        for(int i=0;i<n/2+1;i++)
        {
            cin>>num;
            a.insert(i,num);
        }
        for(int i=0;i<n/2;i++)
        {
            cin>>num;
            b.insert(i,num);
        }
    }
    recursive_Mergesort(a.get_head());
    recursive_Mergesort(b.get_head());
    a.traverse(print);
    cout<<endl;
    b.traverse(print);
    cout<<endl;
    int i=0,temp;
    while(!a.empty())
    {
        a.remove(0,temp);
        c.insert(i++,temp);
    }
    while(!b.empty())
    {
        b.remove(0,temp);
        c.insert(i++,temp);
    }
    recursive_Mergesort(c.get_head());
    c.traverse(print);
    return 0;
}