/*
请在你实现的链式存储的List基础上实现插入排序。
【输入】
第一行，待排序序列个数n，序列长度小于1000；
第二行，n个整数序列；
【输出】
插入排序的中间结果，即当有序序列长度为n/2时的中间结果；
插入排序的最终结果；
例如：
【输入】
5
9 3 8 2 5
【输出】
3 9 8 2 5//输出有序序列长度为2（5/2）时的结果
2 3 5 8 9
*/

#include<iostream>
using namespace std;

enum Error_code{underflow,overflow,rangeerror,success};
const int max_list=1000;
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
    Error_code retrieve(int position,List_entry &x) const;
    void traverse(void (*visit)(List_entry &));
    void insert_sort();
    int sorted_length();
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
    x=following->entry;
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

Error_code List::retrieve(int position,List_entry &x) const
{
    if(position<0||position>=count)
        return rangeerror;
    Node *p=set_position(position);
    x=p->entry;
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

int List::sorted_length()
{
    if(head==NULL)
        return 0;
    int length=1;
    Node *p=head;
    while (p->next!=NULL&&p->entry<=p->next->entry)
    {
        length++;
        p=p->next;
    }
    return length;
}

void print(List_entry &x)
{
    cout<<x<<" ";
}

void List::insert_sort()
{
    Node *first_unsorted,*last_sorted,*current,*trailing;
    if(head!=NULL)
    {
        last_sorted=head;
        while(last_sorted->next!=NULL)
        {
            first_unsorted=last_sorted->next;
            if(first_unsorted->entry<head->entry)
            {
                last_sorted->next=first_unsorted->next;
                first_unsorted->next=head;
                head=first_unsorted;
            }
            else
            {
                trailing=head;
                current=trailing->next;
                while(first_unsorted->entry>current->entry)
                {
                    trailing=current;
                    current=trailing->next;
                }
                if(first_unsorted==current)
                    last_sorted=first_unsorted;
                else
                {
                    last_sorted->next=first_unsorted->next;
                    first_unsorted->next=current;
                    trailing->next=first_unsorted;
                }
            }
            if (size()/2==sorted_length()) 
            {
                traverse(print);
                cout<<endl;
            }
        }
    }
}

int main()
{
    List l;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        l.insert(l.size(),x);
    }
    l.insert_sort();
    l.traverse(print);
    return 0;
}