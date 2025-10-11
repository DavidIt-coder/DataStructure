/*
请在你实现的顺序存储的List基础上实现堆排序。
【输入】
第一行，待排序序列个数n，序列长度小于1000；
第二行，n个整数序列；
【输出】
初始的堆；（大根堆）
堆排序后的结果；
例如：
【输入】
5
6 3 8 2 5
【输出】
8 5 6 2 3//输入序列构造的初始大根堆
2 3 5 6 8
*/
#include<iostream>
using namespace std;

enum Error_code{underflow,overflow,rangeerror,success};
const int max_list=1000;
typedef int List_entry;

class List
{
public:
	List();
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
	List_entry entry[max_list];
};

List::List()
{
    count=0;
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
    count=0;
}

Error_code List::insert(int position,const List_entry &x)
{
    if(full())
        return overflow;
    if(position<0||position>count)
        return rangeerror;
    for(int i=count-1;i>=position;i--)
        entry[i+1]=entry[i];
    entry[position]=x;
    count++;
    return success;
}

Error_code List::remove(int position,List_entry &x)
{
    if(empty( ))
        return underflow;
    if(position<0||position>=count)
        return rangeerror;
    List_entry &y=x;
    y=entry[position];
	for(int i=position;i<count-1;i++)
        entry[i]=entry[i+1];
	count--;
	return success;

}

Error_code List::replace(int position,const List_entry &x)
{
    if(position<0||position>=count)
        return rangeerror;
    entry[position]=x;
	return success;
}

Error_code List::retrieve(int position,List_entry &x) const
{
    if(position<0||position>=count)
        return rangeerror;
    List_entry &y=x;
    y=entry[position];
    return success;
}

void List::traverse(void (*visit)(List_entry &))
{
    for(int i=0;i<count;i++)
        (*visit)(entry[i]);
}

void print(List_entry &x)
{
    cout<<x<<" ";
}

class Sortable_list: public List
{
public:
    void heap_sort();
    void insert_heap(const List_entry &current,int low,int high);
    void build_heap();
};

void Sortable_list::heap_sort()
{
	List_entry current;
	int last_unsorted;
	build_heap();
	for(last_unsorted=count-1;last_unsorted>0;last_unsorted--) 
    {
		current=entry[last_unsorted];
		entry[last_unsorted]=entry[0];
		insert_heap(current,0,last_unsorted-1);
	}
}

void Sortable_list::insert_heap(const List_entry &current,int low,int high)
{
	int large;
	large=2*low+1;
	while (large<=high) 
    {
		if(large<high&&entry[large]<entry[large+1])
			large++;
		if(current>=entry[large])
			break;
		else 
        { 
			entry[low]=entry[large];
			low=large;
			large=2*low+1;
		} 
	} 
	entry[low]=current;
}

void Sortable_list::build_heap()
{
	int low;
	for (low=count/2-1;low>=0;low--) 
    {
		List_entry current=entry[low];
		insert_heap(current,low,count-1);
	} 
}

int main()
{
    int n;
    cin>>n;
    Sortable_list list;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        list.insert(i,x);
    }
    list.build_heap();
    list.traverse(print);
    cout<<endl;
    list.heap_sort();
    list.traverse(print);
    return 0;
}