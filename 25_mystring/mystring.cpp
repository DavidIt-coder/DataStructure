/*
【输入】输入数据共3行；
第1行为字符串个数N（1<=N<=1000）；
第2行为输入的字符串序列，以空格隔开；
第3行为N（N>=0）对数a b（0<=a，b<=length-1），以-1 -1结束，判断第a个字符串是否是第b个字符串的子串，若是则输出第b个字符串中第一次出现第a个字符串的位置（以0开始），若不是则输出-1。
【输出】输出数据共2行；
第1行为输入数据第二行的结果，以空格隔开；
第2行为字符串序列的字典序输出。
例如：
【输入】
3
abc abcd cba
0 1 0 2 -1 -1
【输出】
0 -1 // abc在abcd中首次出现的位置是0，abc不是cba的子串
abc abcd cba // 字典序输出
*/
#include<iostream>
#include<cstring>
using namespace std;

enum Error_code{underflow,overflow,rangeerror,success};
const int max_list=100;
typedef char List_entry;

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

class String 
{
    public:
        String();
        String(const String &copy);//拷贝构造函数
        String(const char *copy);//char *copy为字符串的起始地址，构造函数将其复制到entries中
        String(List &copy);//List &copy为字符串的List类型，构造函数将其复制到entries中
        ~String();
        const char* c_str() const;//返回entries中的字符串
        void operator = (const String &copy);
    protected:
        char *entries;
        int length;//
    };
    bool operator == (const String &first,const String &second);
    bool operator > (const String &first,const String &second);
    bool operator < (const String &first,const String &second);
    bool operator >= (const String &first,const String &second);
    bool operator <= (const String &first,const String &second);
    bool operator != (const String &first,const String &second);
    void strncpy(String &to,const String &from, int n);//将from的前n个字符复制到to中    
    void strcat(String &add_to,const String &add_on);//将add_on添加到add_to的末尾
    int strstr(const String &text,const String &target); //返回target在text中首次出现的位置，若不存在则返回-1
    String read_in(istream &input);//istream &input为输入流，返回值为String类型
    void write(String &s);//write函数将字符串s输出到cout中

String::String()
{
    length=0;
    entries=new char[1];//分配一个长度为1的数组，并将entries指向这个数组
    entries[0]='\0';//初始化为空字符串
}

String::String(const String &copy)
{
    if(copy.length==0)
        string();
    length=copy.length;
    entries=new char[length+1];
    strcpy(entries,copy.entries);
}

String::String(const char *copy)
{
    if(copy==NULL)
        string();
    length=strlen(copy);
    entries=new char[length+1];
    strcpy(entries,copy);
}

String::String(List &copy)
{
    length=copy.size();
    entries=new char[length+1];
    for(int i=0;i<length;i++)
        copy.retrieve(i,entries[i]);
    entries[length]='\0';
}

String::~String()
{
    delete[] entries;
}

const char* String::c_str() const
{
    return (const char*)entries;
}

void String::operator=(const String &copy)
{
    if(this==&copy)
        return;
    delete[] entries;
    length=copy.length;
    entries=new char[length+1];
    strcpy(entries,copy.entries);
}

bool operator==(const String &first,const String &second)
{
    return strcmp(first.c_str(),second.c_str())==0;
}

bool operator!=(const String &first,const String &second)
{
    return strcmp(first.c_str(),second.c_str())!=0;
}

bool operator>(const String &first,const String &second)
{
    return strcmp(first.c_str(),second.c_str())>0;
}

bool operator<(const String &first,const String &second)
{
    return strcmp(first.c_str(),second.c_str())<0;
}

bool operator>=(const String &first,const String &second)
{
    return strcmp(first.c_str(),second.c_str())>=0;
}

bool operator<=(const String &first,const String &second)
{
    return strcmp(first.c_str(),second.c_str())<=0;
}

void strncpy(String &to, const String &from, int n)
{
    const char* cfrom=from.c_str();
    char* copy=new char[n+1];  // 分配 n+1 个字符的空间以容纳空终止符
    strncpy(copy,cfrom,n);
    copy[n]='\0';  // 确保在 n 个字符后添加空终止符
    to=String(copy);  // 使用改进后的 copy 初始化 to
    delete[] copy;
}


void strcat(String &add_to,const String &add_on)
{
    const char* cadd_on=add_on.c_str();
    char* concat=new char[strlen(add_to.c_str())+strlen(cadd_on)+1];
    strcpy(concat,add_to.c_str());
    add_to=strcat(concat,cadd_on);
    delete[] concat;
}

int strstr(const String &text,const String &target)
{
    const char* ctarget=target.c_str();
    const char* ctext=text.c_str();
    return strstr(ctext,ctarget)-ctext;//-ctext是为了将结果转换为相对于字符串text的位置
}

String read_in(istream &input)
{
    List temp;
    int size=0;
    char c;
    while((c=input.peek())!=EOF&&(c=input.get())!='\n')
        temp.insert(size++,c);
    String answer(temp);
    return answer;
}

void write(String &s)
{
    cout<<s.c_str()<<endl;
}

void print(List_entry &x)
{
    cout<<x<<" ";
}

int main()
{
    int n;
    cin>>n;

}