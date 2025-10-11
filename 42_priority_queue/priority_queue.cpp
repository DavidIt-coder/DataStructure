/*
优先级队列（priority queue） 是0个或多个元素的集合，每个元素都有一个优先权
（在此假设数字越大优先权越高，一样大的数字优先权一样大）。
对优先级队列执行的操作有（1）查找（2）插入一个新元素 （3）删除 
一般情况下，查找操作用来搜索优先权最大的元素，删除操作用来删除该元素。
对于优先权相同的元素，可按先进先出次序处理或按任意优先权进行。
请借助于堆实现优先级队列的数据结构。
要求：
（1）采用顺序存储；
（2）支持的操作有：删除元素操作（即取出最大优先级的元素）；插入元素操作；
【输入】
第一行，n个初始元素（元素大于0，顺序随机），以-1结束；n小于1000；
第二行，删除的元素个数m，m小于n
第三行，需要插入到优先级队列的元素序列，以-1结束；
【输出】
第一行，初始优先级队列的信息；（ 书本build_heap算法建堆）
第二行，删除m个元素后的优先级队列信息；
第三行，插入了若干元素后的优先级队列信息；（需要采用自下而上的算法插入堆）
【样例输入】
6 3 8 2 5 -1//初始序列
2//从优先级队列中删除2个元素
12 7 9 -1//依次插入3个新的值，插入12时，先把12追加到堆的尾部，然后再自下而上的调整堆。
【样例输出】
8 5 6 2 3
5 2 3//删除了2个元素8，6后的优先级队列
12 7 9 2 5 3//依次插入12，7，9后的堆
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
    void insert_heap(const List_entry &current,int low,int high);
    Error_code priority_insert_heap(int position,const List_entry &x);
    void build_heap();
    Error_code delete_max();
private:
    void swap(int i,int j);
};

Error_code Sortable_list::priority_insert_heap(int position,const List_entry &x)
{
	insert(position,x);
    while(position>0)
    {
        int parent=(position-1)/2;
        if(entry[position]>entry[parent])
            swap(position,parent);
        position=parent;
    }
    return success;
}

void Sortable_list::swap(int i,int j)
{
    List_entry temp=entry[i];
    entry[i]=entry[j];
    entry[j]=temp;
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

Error_code Sortable_list::delete_max()
{
    if(empty())
        return underflow;
    List_entry x;
    swap(0,count-1);
    remove(count-1,x);
    int parent=0;
    int child=2*parent+1;
    while(child<count)
    {
        if(child+1<count&&entry[child]<entry[child+1])
            child++;
        if(entry[parent]<entry[child])
        {
            swap(parent,child);
            parent=child;
            child=2*parent+1;
        }
        else break;
    }
    return success;
}

int main()
{
    List_entry x;
    Sortable_list list;
    while(cin>>x&&x!=-1)
        list.insert(list.size(),x);
    list.build_heap();
    list.traverse(print);
    cout<<endl;
    int m;
    cin>>m;
    while(m--)
        list.delete_max();
    list.traverse(print);
    cout<<endl;
    while(cin>>x&&x!=-1)
        list.priority_insert_heap(list.size(),x);
    list.traverse(print);
    return 0;
}