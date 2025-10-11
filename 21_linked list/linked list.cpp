/*
（List的单链表实现）
请用单链表（需要记录最后一次访问的位置）实现通用线性表的数据结构MyList。
你所实现的List应包括：Insert，Remove，Retrieve，Replace, Traverse，Size，Full等功能。
利用你实现的MyList实现输入序列的增删及修改。
【输入】输入数据共4行，操作过程中序列长度始终小于100；
第1行为输入的整数序列，以-1结束；
第2行为N（N>=0）对数a b（0<=a<=length），表示在第a个位置前插入数b，以-1 -1结束；
第3行为M（M>=0）个数c（0<=c<=length-1），表示删除第c个位置的元素，以-1结束；
第4行为P（P>=0）对数d e（0<=d<=length-1），表示修改第d个位置的元素，以-1 -1结束。
**注意：插入，删除，修改操作均按照顺序在同一个序列中进行。
【输出】操作后的新序列。
例如：
【输入】
3 7 8 4 6 -1
1 2 -1 -1 //在第1个位置的元素7前插入数2，此时序列为3 2 7 8 4 6
3 -1 // 删除序列3 2 7 8 4 6第3个位置的元素8，此时序列为3 2 7 4 6
4 9 -1 -1//将现有序列第4个位置的元素6修改为9，此时序列为3 2 7 4 9
【输出】
3 2 7 4 9 // 输出操作后的新序列
*/

#include<bits/stdc++.h>
#include<iostream>
using namespace std;

// 定义错误代码枚举类型
enum Error_code{underflow,overflow,rangeerror,success};
// 定义链表的最大容量
const int max_list=100;
// 定义链表元素的数据类型
typedef int List_entry;

// 定义链表节点结构体
struct Node
{
    List_entry entry;
    Node *next;
    Node(); // 默认构造函数，初始化节点
    Node(List_entry item,Node* add=NULL); // 带参数构造函数，创建一个包含指定元素的节点
};

// 定义链表类
class List
{
public:
    List(); // 构造函数，初始化链表
    ~List(); // 析构函数，释放链表占用的内存
    List(const List &copy); // 拷贝构造函数，创建一个现有链表的副本
    void operator=(const List &copy); // 赋值运算符，将一个链表的内容赋值给另一个链表
    int size() const; // 返回链表中元素的数量
    bool full() const; // 判断链表是否已满
    bool empty() const; // 判断链表是否为空
    void clear(); // 清空链表中的所有元素
    Error_code insert(int position,const List_entry &x); // 在指定位置插入一个元素
    Error_code remove(int position,List_entry &x); // 删除指定位置的元素，并将其值赋给x
    Error_code replace(int position,const List_entry &x); // 替换指定位置的元素为x
    Error_code retrieve(int position,List_entry &x) const; // 获取指定位置的元素值，并赋给x
    void traverse(void (*visit)(List_entry &)); // 遍历链表，对每个元素调用visit函数
protected:
    int count; // 记录链表中元素的数量
    Node *head; // 指向链表头节点的指针
    Node *set_position(int position)const; // 设置当前指针到指定位置的节点
    mutable int current_position;// 记录最后一次访问的位置
	mutable Node *current;// 记录最后一次访问的节点
};

// 打印函数，用于遍历链表时输出元素
void print(List_entry &x)
{
    cout<<x<<" ";
}

int main()
{
    List l;
    int x;
    // 从标准输入读取整数，直到读取到-1为止，将每个整数插入到链表末尾
    while((cin>>x)&&(x!=-1))
    {
        l.insert(l.size(),x);
    }
    // 遍历链表并打印每个元素
    l.traverse(print);
    return 0;
}

// Node的默认构造函数，初始化指针为NULL
Node::Node()
{
    next=NULL;
}

// Node的带参数构造函数，创建一个包含指定元素的节点，并链接到下一个节点
Node::Node(List_entry item,Node* add)
{
    entry=item;
    next=add;
}

// List的构造函数，初始化空链表
List::List()
{
    count=0;
    head=NULL;
}

// 设置指针到指定位置的节点
Node* List::set_position(int position)const
{
    Node* q=head;
    for(int i=0;i<position;i++)
        q=q->next;
    return q;
}

// List的析构函数，释放链表占用的内存
List::~List()
{
    clear();
}

// 拷贝构造函数，创建一个现有链表的副本
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

// 赋值运算符，将一个链表的内容赋值给另一个链表
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

// 返回链表中元素的数量
int List::size() const
{
    return count;
}

// 判断链表是否已满
bool List::full() const
{
    if(count==max_list)
        return true;
    return false;
}

// 判断链表是否为空
bool List::empty() const
{
    if(count==0)
        return true;
    return false;
}

// 清空链表中的所有元素
void List::clear()
{
    List_entry x;
    while(!empty())
        remove(0,x);
}

// 在指定位置插入一个元素
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

// 删除指定位置的元素，并将其值赋给x
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
        following=previous->next;//fllowing指向被删除节点的下一个节点
        previous->next=following->next;
    }
    x=following->entry;
    delete following;
    count--;
    return success;
}

// 替换指定位置的元素为x
Error_code List::replace(int position,const List_entry &x)
{
    if(position<0||position>=count)
        return rangeerror;
    Node *p=set_position(position);
    p->entry=x;
 return success;
}

// 获取指定位置的元素值，并赋给x
Error_code List::retrieve(int position,List_entry &x) const
{
    if(position<0||position>=count)
        return rangeerror;
    Node *p=set_position(position);
    x=p->entry;
    return success;
}

// 遍历链表，对每个元素调用visit函数
void List::traverse(void (*visit)(List_entry &))
{
    Node *p=head;
    while(p!=NULL)
    {
        (*visit)(p->entry);
        p=p->next;
    }
}