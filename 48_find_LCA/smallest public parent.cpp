/*
给定一个二分查找树和两个树中的节点，请找出这两个节点在这棵二分查找树中最矮(离叶子节点最接近)的公共祖先。

【输入】
第一行，插入的整数数量，空格隔开的若干不重复的整数，数量小于2000
第二行，两个整数p和q，空格隔开。（p和q是树中的节点值）
【输出】
最矮的公共祖先

例如：【输入】
8 6 2 8 4 3 5 7 9
2 8
【输出】
6

【输入】
8 6 2 8 4 3 5 7 9
2 4
【输出】
2

【解释】
二叉查找树为：
    6
   / \
  2   8
  \   / \
  4  7  9
  / \
 3  5
2和8的最矮公共祖先是6；
2和4的最矮公共祖先为2；
*/
#include<iostream>
using namespace std;

enum Error_code{underflow,overflow,success,not_present,duplicate_error};
const int maxstack=2001;

class Record
{
public:
    Record(int x=0);
    int the_key()const;
private:
    int key;
};

Record::Record(int x)
{
    key=x;
}

int Record::the_key()const
{
    return key;
}

bool operator==(const Record& x,const Record& y)
{
    return x.the_key()==y.the_key();
}

bool operator>(const Record &x,const Record &y)
{
	return x.the_key()>y.the_key();
}

bool operator<(const Record &x,const Record &y)
{
	return x.the_key()<y.the_key();
}

ostream & operator<<(ostream &output,Record &x)
{
	output<<x.the_key();
	output<<"  ";
	return output;
}

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
protected:
	void recursive_preorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &));
	void recursive_inorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &));
	void recursive_postorder(Binary_node<Entry> *sub_root,void(*visit)(Entry &));
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
	Binary_node<Entry>* current = root;
	while (true) {
		if (x < current->data) {
			if (current->left == NULL) {
				current->left = new Binary_node<Entry>(x);
				break;
			} else current = current->left;
		} else {
			if (current->right == NULL) {
				current->right = new Binary_node<Entry>(x);
				break;
			} else current = current->right;
		}
	}
	count++;
}

template<class Record>
class Search_tree : public Binary_tree<Record> 
{
public:
    Error_code insert(const Record& new_data);
    Error_code remove(const Record& target);
    Error_code tree_search(Record& target) const;
    int find_LCA(int p,int q) const;
private:
    Binary_node<Record>* search_for_node(Binary_node<Record>* sub_root,const Record& target) const;
    Error_code search_and_insert(Binary_node<Record>*& sub_root,const Record& new_data);
    Error_code remove_root(Binary_node<Record>*& sub_root);
    Error_code search_and_destroy(Binary_node<Record>*& sub_root,const Record& target);
};

template<class Record>
Error_code Search_tree<Record>::tree_search(Record& target) const 
{
    Binary_node<Record>* found=search_for_node(this->root,target);
    if(found!=NULL) 
    {
        target=found->data;
        return success;
    } 
    else 
        return not_present;
}

template<class Record>
Binary_node<Record>* Search_tree<Record>::search_for_node(Binary_node<Record>* sub_root,const Record& target) const 
{
    if(sub_root==NULL) return NULL;
    if(sub_root->data==target) return sub_root;
    if(sub_root->data<target) return search_for_node(sub_root->right,target);
    else return search_for_node(sub_root->left,target);
}

template<class Record>
Error_code Search_tree<Record>::insert(const Record& new_data) 
{
    Error_code result=search_and_insert(this->root,new_data);
    if(result==success) this->count++;
    return result;
}

template<class Record>
Error_code Search_tree<Record>::search_and_insert(Binary_node<Record>*& sub_root,const Record& new_data) 
{
    if(sub_root==NULL) 
    {
        sub_root=new Binary_node<Record>(new_data);
        return success;
    } 
    else if(new_data<sub_root->data)
        return search_and_insert(sub_root->left,new_data);
    else if(new_data>sub_root->data)
        return search_and_insert(sub_root->right,new_data);
    else
        return duplicate_error;
}

template<class Record>
Error_code Search_tree<Record>::remove(const Record& target) 
{
    Error_code result = search_and_destroy(this->root,target);
    if(result==success) this->count--;
    return result;
}

template<class Record>
Error_code Search_tree<Record>::search_and_destroy(Binary_node<Record>*& sub_root, const Record& target) 
{
    if(sub_root==NULL)
        return not_present;
    else if(target<sub_root->data)
        return search_and_destroy(sub_root->left,target);
    else if(target>sub_root->data)
        return search_and_destroy(sub_root->right,target);
    else
        return remove_root(sub_root);
}

template<class Record>
Error_code Search_tree<Record>::remove_root(Binary_node<Record>*& sub_root) 
{
    if(sub_root==NULL)
        return not_present;
    Binary_node<Record>* to_delete=sub_root;
    if(sub_root->right==NULL)
        sub_root=sub_root->left;
    else if(sub_root->left==NULL)
        sub_root=sub_root->right;
    else 
    {
        to_delete=sub_root->left;
        Binary_node<Record>* parent=sub_root;
        while (to_delete->right!=NULL) 
        {
            parent=to_delete;
            to_delete=to_delete->right;
        }
        sub_root->data=to_delete->data;
        if (parent==sub_root)
            sub_root->left=to_delete->left;
        else
            parent->right=to_delete->left;
    }
    delete to_delete;
    return success;
}

template<class Record>
int Search_tree<Record>::find_LCA(int p, int q) const 
{
    Binary_node<Record>* current=this->root;
    while (current!=NULL) 
    {
        int val=current->data.the_key();
        if (p<val&&q<val) current=current->left;
        else if(p>val &&q>val) current=current->right;
        else return val;
    }
    return -1;
}

int main()
{
    Search_tree<Record> tree;
    int n,x;
    cin>>n;
    for(int i=0;i<n;i++) 
    {
        cin>>x;
        tree.insert(Record(x));
    }
    cin>>n>>x;
    cout<<tree.find_LCA(n,x)<<endl;
    return 0;
}