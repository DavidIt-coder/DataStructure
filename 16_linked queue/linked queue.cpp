/*
（链式存储的队列）请用链式存储实现队列的数据结构MyLinkedQueue。
你所实现的队列应包括：出队、入队、访问队首、判断队列是否已满，判断队列是否为空等功能。
利用你实现的MyLinkedQueue实现输入整数序列的顺序输出。
【输入】整数序列以-1结束，序列长度小于100
【输出】输入整数序列的顺序序列
例如：
【输入】3 9 8 2 5 -1
【输出】3 9 8 2 5
*/
#include <iostream>
using namespace std;

enum Error_code{underflow, overflow, success};
typedef int type;

struct Node
{
    type entry;
    Node *next;
    Node();
    Node(type item,Node* add=NULL);
};

Node::Node()
{
    next=NULL;
}

Node::Node(type item,Node* add)
{
    entry=item;
    next=add;
}

class queue 
{
private:
    int count;
public:
	queue();
	queue(const queue &original);
	bool empty() const;
	Error_code append(const type &item);
	Error_code serve();
	Error_code retrieve(type &item) const;
	int size()const;
	void clear();
	~queue();
protected:
	Node *front, *rear;
};

queue::queue()
{
    front=rear=0;
    count=0;
}

queue::queue(const queue &original)
{
    front=rear=0;
    count=0;
    Node *p=original.front;
    while(p!=0)
    {
        append(p->entry);
        p=p->next;
    }
}

bool queue::empty()const
{
    if(count==0) return true;
    return false;
}

Error_code queue::append(const type &item)
{
    Node *new_rear=new Node(item);
    if (new_rear==0) 
        return overflow;
    if (rear==0) 
        front=rear=new_rear;
    else 
    {
        rear->next=new_rear;
        rear=new_rear;
    }
    count++;
    return success;

}

Error_code queue::serve()
{
    if(front==0) 
        return underflow;
    Node *old_front=front;
    front=old_front->next;
    if(front==0) 
        rear=0;
    delete old_front;
    count--;
    return success;
}

Error_code queue::retrieve(type &item)const
{
    if(front==0) 
        return underflow;
    type &t=item;
    t=front->entry;
    return success;
}

int queue::size()const
{
    return count;
}

void queue::clear()
{
    count=0;
    while(!empty())
        serve();
}

queue::~queue()
{
    count=0;
    while(!empty())
        serve();
}

int main()
{
    queue q;
    int n;
    while(cin>>n&&n!=-1)
        q.append(n);
    while(!q.empty())
    {
        q.retrieve(n);
        cout<<n<<" ";
        q.serve();
    }
    return 0;
}