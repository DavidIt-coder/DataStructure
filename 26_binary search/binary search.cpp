/*
（二分查找的实现）请尝试用你实现的顺序存储List实现二分查找。
List中的Record包含key和other部分。其中key为英文单词，other为单词的中文解释。
【输入】
第一行，查询目标target（英文单词）
第二行，若干条包含key（string）和other（string）的序列，序列按照key的升序排列；（单词数量小于2000）
【输出】查询目标所在的下标，查询目标的内容（key和other），若单词不存在则输出-1即可。
例如
【输入】
wait
computer 电脑 eye 眼睛 hello 你好 train 火车 wait 等待 zebra 斑马
【输出】
4
wait 等待
【输入】
apple
computer 电脑 eye 眼睛 hello 你好 train 火车 wait 等待 zebra 斑马
【输出】
-1 //不存在
*/
#include<iostream>
#include<string>
using namespace std;
enum Error_code{success,underflow,overflow,rangeerror,not_present};
const int max_list=2000;

class Record
{
private:
    string key;
    string other;
public:
    Record();
    Record(string x,string y);
    string the_key()const;
    string the_other()const;
};

Record::Record(){}

Record::Record(string x,string y)
{
    key=x;
    other=y;
}

string Record::the_key()const
{
    return key;
}

string Record::the_other()const
{
    return other;
}

class Key
{
private:
    string key;
public:
    Key(string x);
    Key(const Record& r);
    string the_key()const;
};

bool operator == (const Key& x,const Key& y)
{
    return x.the_key()==y.the_key();
}

Key::Key(string x)
{
    key=x;
}

Key::Key(const Record& r)
{
    key=r.the_key();
}

string Key::the_key()const
{
    return key;
}

typedef Record List_entry;
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
    Error_code binary_search(const Key &x,int &position,string &others)const; 
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

Error_code List::retrieve(int position,List_entry &x)const
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

Error_code List::binary_search(const Key &target,int &positions,string &others)const
{
    int& position=positions;
    string& other=others;
    Record data;
    int bottom=0,top=count-1;
    while(bottom<top)
    {
        int mid=(bottom+top)/2;
        retrieve(mid,data);
        if(data.the_key()<target.the_key())
            bottom=mid+1;
        else
            top=mid;
    }
    if(top<bottom)
        return not_present;
    position=top;
    retrieve(position,data);
    if(data.the_key()==target.the_key())
    {
        other=data.the_other();
        return success;
    }
    return not_present;
}

int main()
{
    List l;
    string key,other;
    int i=0,position;
    cin>>key;
    Key target(key);
    while(cin>>key>>other)
    {
        Record temp(key,other);
        l.insert(i,temp);
        i++;
    }
    Error_code result=l.binary_search(target,position,other);
    if(result==not_present)
        cout<<"-1"<<endl;
    else
        cout<<position<<endl<<target.the_key()<<" "<<other<<endl;
    return 0;
}