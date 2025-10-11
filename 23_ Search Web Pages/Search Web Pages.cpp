/*
（页面的相关系数）
有N个 Web 页面，给每个Web页面分配一个相关系数 Vi（Vi为正整数），
请输出具有最大相关系数的页面，如果具有最大相关系数的页面有多个，那么将这些页面全部输出。
*请尝试用自己编写的MyList来辅助完成该题。
【输入】
第 1 行：一个正整数 N (0<N<=150)
第 2 行 ~ N+1 行：
每行包含一个字符串和一个整数 Vi，两者之间用一个空格分隔。
字符串表示Web页面的URL（字符串长度不超过 100 个字符,且不含有空格）,
整数 Vi(1<=Vi<=100)为页面的相关系数。
【输出】
输出具有最大相关系数的页面的URL，
如果具有最大相关系数的页面有多个，则按照输入的顺序依次将它们都输出。
每行的最后有一个换行符。
例如：
【输入】
10
www.youtube.com 1
www.google.com 13
www.google.com.hk 3
www.alibaba.com 13
www.taobao.com 5
www.bad.com 10
www.good.com 7
www.baidu.com 8
www.university.edu.cn 9
www.ecnu.edu.cn 13
【输出】
www.google.com
www.alibaba.com
www.ecnu.edu.cn
*/
#include<iostream>
#include<string>
using namespace std;

enum Error_code{underflow,overflow,rangeerror,success};
const int max_list=150;
typedef string List_entry;

struct Node
{
    List_entry entry;
    Node *next;
    Node *back;
    Node(); 
    Node(List_entry item,Node *link_back = NULL,Node *link_next = NULL); 
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
    void reverse_traverse(void (*visit)(List_entry &));
protected:
    int count; 
    Node *head; 
    mutable int current_position;
	mutable Node *current;
    Node *set_position(int position)const; 
};

Node::Node()
{
    next=NULL;
    back=NULL;
}

Node::Node(List_entry item,Node *link_back,Node *link_next)
{
    entry=item;
    next=link_next;
    back=link_back;
}

List::List()
{
    count=0;
    head=NULL;
    current_position=0;
    current=head;
}

Node* List::set_position(int position)const
{
    if(position<0||position>=count||count==0)
        return NULL;
    if(current_position<=position)
        for(;current_position!=position;current_position++)
            current=current->next;
    else
        for(;current_position!=position;current_position--)
            current=current->back;
    return current;
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

Error_code List :: insert(int position, const List_entry &x)
{
	Node *new_node, *following, *preceding;
	if (position < 0 || position > count) 
        return rangeerror;
	if (position == 0)
    {
		if (count == 0) following = NULL;
		else 
        {
			set_position(0);	
			following = current;
		}
		preceding = NULL;
	}
	else 
    {
		set_position(position - 1);
		preceding = current;
		following = preceding->next;
	}
    new_node = new Node(x, preceding, following);
	if (new_node == NULL) return overflow;
	if (preceding != NULL) preceding->next = new_node;
	if (following != NULL) following->back = new_node;
        current = new_node;
	current_position = position;
	if (position == 0)head = new_node;
 	count++;
	return success;
}


Error_code List::remove(int position,List_entry &x)
{
    if(position<0||position>=count)
		return rangeerror;
	Node *previous,*following;
	if (position>0) 
    {
		previous=set_position(position-1);
		following=previous->next;
		previous->next=following->next;
		if(following->next)
            following->next->back=previous;
    }
    else
    {
		following=head;
		head=head->next;
		if(head)
            head->back=NULL;
		current_position=0;
		current=head;
	}
    List_entry &y=x;
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

Error_code List::retrieve(int position,List_entry &x) const
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

void List::reverse_traverse(void (*visit)(List_entry &))
{
    Node *last=set_position(count-1);
    while (last != NULL) 
    {
        visit(last->entry);
        last = last->back;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void print(List_entry &x)
{
    cout<<x<<endl;
}

class page
{
public:
    string url;
    int vi;
    page(string u,int v);
};
page::page(string u,int v)
{
    url=u;
    vi=v;
}

int main()
{
    List l;
    int n;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        string url;
        int vi;
        cin>>url>>vi;
        page p(url,vi);
        string entry=to_string(vi)+" "+url;
        l.insert(i,entry);
    }
    int max_vi=0;
    List maxl;
    for(int i=0;i<n;i++)
    {
        string entry;
        l.retrieve(i,entry);
        int vi=stoi(entry.substr(0,entry.find(" ")));
        if(vi>max_vi)
        {
            max_vi=vi;
            maxl.clear();
            maxl.insert(0,entry.substr(entry.find(" ")+1));
        }
        else if(vi==max_vi)
            maxl.insert(maxl.size(),entry.substr(entry.find(" ")+1));
    }
    maxl.traverse(print);
    return 0;
}
/*
上面用到的string函数：
size_t find(const string& str, size_t pos = 0)：
            返回str在当前字符串中第一次出现的位置，从pos开始搜索
int stoi(const string& str)：
            将字符串转换为整数
string substr(size_t pos = 0, size_t len = npos)：
            返回从pos开始的len个字符的子串
string substr(size_t pos):
            返回从pos开始到结尾的子串
string to_string(int value)：将整数转换为字符串
*/