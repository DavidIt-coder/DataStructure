/*
请用链式存储的二叉查找树实现单词信息的查找。包含的操作有：插入元素、删除元素、查找元素等。
注意：Record包含key和other部分。其中key为英文单词，other为单词的中文解释。
【输入】
第1行，插入的单词数量，插入二叉查找树的单词信息，若干条包含key（string）和other（string）的序列；（单词数量小于2000）
第2行，删除的单词数量，从二叉查找树中删除的单词清单；（若为多个单词，会用空格隔开）（请用其前驱节点代替删除节点）
第3行，查询目标target1（英文单词）
第4行，查询目标target2（英文单词）

【输出】
第1行，查询目标1所在的路径信息和查询目标的内容（key和other），若单词不存在则输出NULL即可。
第2行，查询目标2所在的路径信息和查询目标的内容（key和other），若单词不存在则输出NULL即可。

例如
【输入】
6 train 火车 eye 眼睛 hello 你好 computer 电脑 wait 等待 zebra 斑马//插入
1 eye//删除
hello//查询目标1
eye//查询目标2
【输出】
train computer hello 你好//从根节点train开始，经过左孩子computer，然后右孩子，查找成功
train computer hello NULL//不存在
【说明】：
6个单词（train 火车 eye 眼睛 hello 你好 computer 电脑 wait 等待 zebra 斑马）生成的二叉查找树为：
t
/ \
e w
/ \ \
c h z

删除eye之后的查找树：
t
/ \
c w
\ \
h z
在此基础上查找hello：访问路径为 t，c，h；成功
在此基础上查找eye，访问路径为：t，c，h，null；失败（h->left为空）

[example]
6 train 火车 eye 眼睛 hello 你好 computer 电脑 wait 等待 zebra 斑马
1 eye
hello
eye
*/
#include<iostream>
using namespace std;

enum Error_code{underflow,overflow,success,not_present,duplicate_error};
const int maxstack=2001;

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

template<class Record>
class Search_tree : public Binary_tree<Record> 
{
public:
    Error_code insert(const Record& new_data);
    Error_code remove(const Record& target);
    Error_code tree_search(Record& target) const;
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
    if (found!=NULL) 
    {
        target=found->data;
        cout<<target.the_other()<<endl;
        return success;
    } 
    else 
    {
        cout <<"NULL"<<endl;
        return not_present;
    }
}

template<class Record>
Binary_node<Record>* Search_tree<Record>::search_for_node(Binary_node<Record>* sub_root,const Record& target) const 
{
    if (sub_root==NULL) return NULL;
    cout << sub_root->data.the_key()<<" ";
    if (sub_root->data==target) return sub_root;
    if (sub_root->data<target) return search_for_node(sub_root->right,target);
    else return search_for_node(sub_root->left,target);
}

template<class Record>
Error_code Search_tree<Record>::insert(const Record& new_data) 
{
    Error_code result=search_and_insert(this->root,new_data);
    if (result==success) this->count++;
    return result;
}

template<class Record>
Error_code Search_tree<Record>::search_and_insert(Binary_node<Record>*& sub_root,const Record& new_data) 
{
    if (sub_root==NULL) 
    {
        sub_root=new Binary_node<Record>(new_data);
        return success;
    } 
    else if (new_data<sub_root->data)
        return search_and_insert(sub_root->left,new_data);
    else if (new_data>sub_root->data)
        return search_and_insert(sub_root->right,new_data);
    else
        return duplicate_error;
}

template<class Record>
Error_code Search_tree<Record>::remove(const Record& target) 
{
    Error_code result = search_and_destroy(this->root,target);
    if (result==success) this->count--;
    return result;
}

template<class Record>
Error_code Search_tree<Record>::search_and_destroy(Binary_node<Record>*& sub_root, const Record& target) 
{
    if (sub_root==NULL)
        return not_present;
    else if (target<sub_root->data)
        return search_and_destroy(sub_root->left,target);
    else if (target>sub_root->data)
        return search_and_destroy(sub_root->right,target);
    else
        return remove_root(sub_root);
}

template<class Record>
Error_code Search_tree<Record>::remove_root(Binary_node<Record>*& sub_root) 
{
    if (sub_root==NULL)
        return not_present;
    Binary_node<Record>* to_delete=sub_root;
    if (sub_root->right==NULL)
        sub_root=sub_root->left;
    else if (sub_root->left==NULL)
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

int main()
{
    Search_tree<Record> tree;
	string word,meaning;
	int n;
	cin>>n;
	while(n--)
	{
		cin>>word>>meaning;
		tree.insert(Record(word,meaning));
	}
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>word;
		tree.remove(Record(word,""));
	}
	for(int i=0;i<2;i++)
	{
		cin>>word;
		Record target(word,"");
		tree.tree_search(target);
	}
	return 0;
}