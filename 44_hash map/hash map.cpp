/*
Design a HashMap without using any built-in hash table libraries.
Note:请用链地址法解决冲突；

To be specific, your design should include these functions:

put(key, value) : 
    Insert a (key, value) pair into the HashMap. 
    If the value already exists in the HashMap, update the value. 
    Note:新值插入链表头部，如果已经存在值，则更新这个值
get(key): Returns the value to which the specified key is mapped, 
          or -1 if this map contains no mapping for the key.
remove(key):Remove the mapping for the value key 
            if this map contains the mapping for the key.

Example:

MyHashMap hashMap;
hashMap.put(“abc”, “abc”);
hashMap.put(“abcd”, “abcd”);
hashMap.get(“abc”); // returns 1
hashMap.get(“cat”); // returns -1 (not found)
hashMap.put(“abcd”, “ABCD”); // update the existing value
hashMap.get(“abcd”); // returns 1
hashMap.remove(“abcd”); // remove the mapping for 2
hashMap.get(“abcd”); // returns -1 (not found)

Key字符串类型的转换借助于BKDR Hash Function
// BKDR Hash Function

unsigned int BKDRHash(char *str)
{
    unsigned int seed = 31; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
    while(*str)
    {
        hash = (hash * seed + (*str++))% Hash_Size;
    }
    return (hash% Hash_Size); //使hash函数返回值在hash表的有效地址范围
}
【输入】
第一行，整数n和m，n表示hash表的大小，m代表插入hash表的元素个数。n小于1000的素数，m小于n。
       注意n可理解为BKDRHash中Hash_Size的值。
第二行，m对的值
第三行，1组//insert到Hash Map
第四行，任意的Key1//删除Key
第五行，任意查询的key2
【输出】
第一行，对应于输入第三行插入到Hash Map的地址信息；
第二行，对应于输入第四行删除key1的过程；
第三行，对应于输入第五行探测的key2的过程；

注意若key在hash表中不存在，则输出NULL。
例如：
【输入】
7 6
computer 电脑 eye 眼睛 hello 你好 train 火车 wait 等待 zebra 斑马
train 火车，训练
dog
hello

注意：此时Key的位置信息为computer:1; eye:1; hello:0; train:3; wait:2; zebra:0

【输出】
3//输出train对应的地址码；
6 dog NULL//dog的地址码为6，删除dog失败；
0 zebra hello 你好//hello的地址码为0，先访问到zebra然后访问到hello。
*/
#include <iostream>
using namespace std;

enum Error_code{not_present,underflow,overflow,rangeerror,duplicate_error,success};
const int max_list=1000;
const int Hash_size=997;
int hash_size;

class Key
{
private:
    string key;
public:
    Key();
    Key(string x);
    string the_key()const;
};

Key::Key()
{}

Key::Key(string x)
{
    key=x;
}

string Key::the_key()const
{
    return key;
}

bool operator==(const Key& x, const Key& y)
{
    return x.the_key()==y.the_key();
}

class Record
{
public:
    operator Key();
    Record();
    Record(string x,string y);
    string the_key()const;
    string the_other()const;
private:
    string key;
    string other;
};

Record::operator Key()
{
    Key tmp(key);
    return tmp;
}

Record::Record()
{}

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

bool operator!=(const Record& x,const Record& y)
{
    return x.the_other()!=y.the_other();
}

bool operator==(const Record& x,const Record& y)
{
    return x.the_key()==y.the_other();
}

typedef Record Node_entry;
typedef Record List_entry;

struct Node
{
    Node_entry entry;
    Node *next;
    Node();
    Node(Node_entry item,Node* add_on=NULL); 
};

Node::Node()
{
    next=NULL;
}


Node::Node(Node_entry item,Node* add)
{
    entry=item;
    next=add;
}

class List
{
public:
    List();
    ~List();
    List(const List &copy); 
    void operator=(const List &copy); 
    int size()const; 
    bool full()const; 
    bool empty()const;
    void clear(); 
    Error_code insert(int position,const List_entry &x);
    Error_code remove(int position,List_entry &x);
    Error_code replace(int position,const List_entry &x);
    Error_code retrieve(int position,List_entry &x) const;
    void traverse(void (*visit)(List_entry &));
protected:
    int count; 
    Node *head;
    Node *set_position(int position)const;
    mutable int current_position;
	mutable Node *current;
};

Node* List::set_position(int position)const
{
    Node* q=head;
    for(int i=0;i<position;i++)
        q=q->next;
    return q;
}

List::List()
{
    count = 0;
    head = NULL;
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

void List::operator=(const List &copy)
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

unsigned int BKDRHash(char *str)
{
    unsigned int seed=31;
    unsigned int hash=0;
    while(*str)
    {
        hash=(hash*seed+(*str++))%hash_size;
    }
    return hash%hash_size;
}

class Hash_map
{
public:
    void clear();
    Error_code insert(const Record& new_entry);
    Error_code retrieve(const Key& target, Record& found)const;
    Error_code remove(const Key& target, Record& found);
private:
    List table[Hash_size];
};

void Hash_map::clear()
{
    for(int i=0;i<hash_size;i++) 
        table[i].clear();
}

Error_code Hash_map::insert(const Record& new_entry)
{
    int probe=BKDRHash((char*)new_entry.the_key().c_str());
    for(int i=0;i<table[probe].size();i++)
    {
        Record tmp;
        table[probe].retrieve(i,tmp);
        if(tmp.the_key()==new_entry.the_key())
        {
            table[probe].remove(i,tmp);
            table[probe].insert(i,new_entry);
            return success;
        }
    }
    table[probe].insert(0,new_entry);
    return success;
}

Error_code Hash_map::retrieve(const Key& target, Record& found)const
{
    int probe=BKDRHash((char*)target.the_key().c_str());
    for(int i = 0; i < table[probe].size(); i++)
    {
        Record tmp;
        table[probe].retrieve(i,tmp);
        cout<<tmp.the_key()<<' ';
        if(target==tmp) 
        {
            found=tmp;
            return success;
        }
    }
    return not_present;
}

Error_code Hash_map::remove(const Key& target,Record& found)
{
    int probe=BKDRHash((char*)target.the_key().c_str());
    for(int i=0;i<table[probe].size();i++)
    {
        Record tmp;
        table[probe].retrieve(i,tmp);
        cout<<tmp.the_key()<<' ';
        if(target==tmp)
        {
            table[probe].remove(i,found);
            return success;
        }
    }
    return not_present;
}

int main()
{
    Hash_map a;
    int m,n;
    string key,other;
    cin>>n>>m;
    hash_size=n;
    for(int i=0;i<m;i++)
    {
        cin>>key>>other;
        a.insert(Record(key,other));
    }

    cin>>key>>other;
    a.insert(Record(key,other));
    cout<<BKDRHash((char*)key.c_str())<<endl;

    Error_code result;
    Record tmp;
    cin>>key;
    cout<<BKDRHash((char*)key.c_str())<<' ';
    result=a.remove(key,tmp);
    if(result==success)
        cout<<tmp.the_other()<<endl;
    else cout<<key<<' '<<"NULL"<<endl;

    cin>>key;
    cout<<BKDRHash((char*)key.c_str())<<' ';
    result=a.retrieve(key,tmp);
    if(result==success)
        cout<<tmp.the_other();
    else cout<<key<<' '<<"NULL";
    return 0;
}