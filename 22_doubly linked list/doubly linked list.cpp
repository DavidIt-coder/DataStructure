#include<iostream>
using namespace std;

enum Error_code{underflow,overflow,rangeerror,success};
const int max_list=100;
typedef int List_entry;

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

void print(List_entry &x)
{
    cout<<x<<" ";
}

void initialize(List &l)
{
    List_entry x;
    while(cin>>x && x!=-1)
    {
        l.insert(l.size(),x);
    }
}

void insertions(List &l)
{
    List_entry x, y;
    while(cin>>x>>y && (x!=-1 || y!=-1))
    {
        l.insert(x,y);
    }
}

void removals(List &l)
{
    List_entry x, y;
    while(cin>>x && x!=-1)
    {
        l.remove(x,y);
    }
}

void replacements(List &l)
{
    List_entry x, y;
    while(cin>>x>>y && (x!=-1 || y!=-1))
    {
        l.replace(x,y);
    }
}

int main()
{
    List l;
    initialize(l);
    insertions(l);
    removals(l);
    replacements(l);  
    l.traverse(print);
    cout<<endl;
    l.reverse_traverse(print);
    return 0;
}

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