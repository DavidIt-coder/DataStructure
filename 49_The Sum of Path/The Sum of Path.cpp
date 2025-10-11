#include<iostream>
using namespace std;

enum Error_code{underflow,overflow,success,not_present,duplicate_error};
const int maxstack=2001;

template<class Stack_entry>
class MyStack
{
public:
    MyStack();
    Error_code push(const Stack_entry &item);
    Error_code pop();
    Error_code top(Stack_entry &item) const;
    bool empty() const;
    int size() const;
private:
    int count;
    Stack_entry entry[maxstack];
};

template<class Stack_entry>
MyStack<Stack_entry>::MyStack()
{
   count=0;
}

template<class Stack_entry>
Error_code MyStack<Stack_entry>::push(const Stack_entry &item)
{
    Error_code outcome=success;
    if(count>=maxstack)
        outcome=overflow;
    else
        entry[count++]=item;
    return outcome;
}

template<class Stack_entry>
Error_code MyStack<Stack_entry>::pop()
{
    Error_code outcome=success;
    if(count==0)
        outcome=underflow;
    else
        count--;
   return outcome;
}

template<class Stack_entry>
Error_code MyStack<Stack_entry>::top(Stack_entry &item) const
{
    Error_code outcome=success;
    Stack_entry &items=item;
    if(count==0)
        outcome=underflow;
    else
        items=entry[count-1];
    return outcome;
}

template<class Stack_entry>
bool MyStack<Stack_entry>::empty() const
{
    bool outcome=true;
    if(count>0)
        outcome=false;
    return outcome;
}

template<class Stack_entry>
int MyStack<Stack_entry>::size() const
{
    return count;
}

template<class Entry>
struct Binary_node
{
	Entry data;
	Binary_node *left;
	Binary_node *right;
	Binary_node();
	Binary_node(const Entry &x);
};

template<class Entry>
Binary_node<Entry>::Binary_node()
{
	left=NULL;
	right=NULL;
}

template<class Entry>
Binary_node<Entry>::Binary_node(const Entry &x)
{
    data=x;
	left=NULL;
	right=NULL;
}

template <class Entry>
class Binary_tree
{
public:
	Binary_tree();
	bool empty() const;
	void preorder(void(*visit)(Entry &));
	void inorder(void(*visit)(Entry &));
	void postorder(void(*visit)(Entry &));
	int size() const;
	int height() const;
	void insert(Entry &);
    bool has_path_sum(int target) const;
protected:
	void recursive_preorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &));
	void recursive_inorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &));
	void recursive_postorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &));
    bool recursive_has_path_sum(Binary_node<Entry> *node,int sum) const;
	Binary_node<Entry> *root;
	int count;
};

template <class Entry>
Binary_tree<Entry>::Binary_tree()
{
	root=NULL;
	count=0;
}

template <class Entry>
bool Binary_tree<Entry>::empty() const
{
	return root==NULL;
}

template <class Entry>
void Binary_tree<Entry>::preorder(void(*visit)(Entry &))
{
	recursive_preorder(root,visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &))
{
	if (sub_root!=NULL)
    {
		(*visit)(sub_root->data);
		recursive_preorder(sub_root->left,visit);
		recursive_preorder(sub_root->right,visit);
	}
}

template <class Entry>
void Binary_tree<Entry>::inorder(void(*visit)(Entry &))
{
	recursive_inorder(root,visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &))
{
	if (sub_root!=NULL)
    {
		recursive_inorder(sub_root->left,visit);
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->right,visit);
	}
}

template <class Entry>
void Binary_tree<Entry>::postorder(void(*visit)(Entry &))
{
	recursive_postorder(root,visit);
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &))
{
	if (sub_root!=NULL)
    {
		recursive_postorder(sub_root->left,visit);
		recursive_postorder(sub_root->right,visit);
		(*visit)(sub_root->data);
	}
}

template <class Entry>
int Binary_tree<Entry>::size() const
{
	return count;
}

template <class Entry>
int Binary_tree<Entry>::height() const
{
	int count=size();
	if(count==0)
        return 0;
	int tmp=1,i;
	for(i=-1;tmp<=count;i++)
        tmp*=2;
	return i;
}

template <class Entry>
void Binary_tree<Entry>::insert(Entry &x)
{
	if(empty())
    {
		root=new Binary_node<Entry>(x);
		count++;
		return ;
	}
	MyStack<int> numbers;
	int item=0;
    int tmpcount=size();
    while(tmpcount>0)
    {
		int a=(tmpcount-1)/2;
 	    int b=(tmpcount-2)/2;
	    if(tmpcount>1 && a==b)
		    numbers.push(2);
	    else
		    numbers.push(1);

	    tmpcount=(tmpcount-1)/2;

	}
	Binary_node<Entry> *current=root;
	while (numbers.size()>1)
    {
		numbers.top(item);
        if(item==1) current=current->left;
		if(item==2) current=current->right;
        numbers.pop();
	}
	numbers.top(item);
	if(item==1) current->left=new Binary_node<Entry>(x);
	if(item==2) current->right=new Binary_node<Entry>(x);
	count++;
}

template <class Entry>
void print(Entry &x)
{
	cout<<x<<' ';
}

template <class Entry>
bool Binary_tree<Entry>::has_path_sum(int target) const 
{
    return recursive_has_path_sum(root,target);
}

template <class Entry>
bool Binary_tree<Entry>::recursive_has_path_sum(Binary_node<Entry> *node,int sum) const
{
    if(node==NULL) return false;
	int current_data=node->data;
	if(node->left==NULL&&node->right==NULL)
		return current_data==sum;
	return recursive_has_path_sum(node->left,sum-current_data)||recursive_has_path_sum(node->right,sum-current_data);
}

int main()
{
    Binary_tree<int> tree;
	int n,x;
	cin>>n;
	for(int i=0;i<n;i++) 
    {
		cin>>x;
		tree.insert(x);
	}
	cin>>x;
	cout<<tree.height()<<" ";
	if(tree.has_path_sum(x)) cout<<"true";
	else cout<<"false";
    return 0;
}