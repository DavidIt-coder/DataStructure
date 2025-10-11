/*
请在你实现的顺序存储的List基础上实现快速排序。（假设序列中的最后一个元素为轴点），此题需要按照课本的方法进行序列划分。
【输入】
第一行，待排序序列个数n，序列长度小于1000；
第二行，n个整数序列；
【输出】
快速排序的中间结果，即第一轮排序后序列的排列情况；
快速排序的最终结果；
例如：
【输入】
5
6 3 8 2 5
【输出】
2 3 5 8 6
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

class Quick_sort:public List
{
public:
    void quick_sort();
    void swap(int i,int j);
    void half_sort();
private:
    void recursive_quick_sort(int low,int high);
    int partition(int low,int high);
};

void Quick_sort::half_sort()
{
    partition(0, count - 1);
}

void Quick_sort::quick_sort()
{
    recursive_quick_sort(0,count-1);
}

void Quick_sort::recursive_quick_sort(int low,int high)
{
    int pivot_position;
	if(low<high) 
    {
		pivot_position=partition(low,high);
		recursive_quick_sort(low,pivot_position-1);
		recursive_quick_sort(pivot_position+1,high);
	} 
}

int Quick_sort::partition(int low,int high)
{
    List_entry pivot;
    int i, last_small;
    swap(low,high);
    pivot=entry[low];
    last_small=low;
    for (i=low+1;i<=high;i++) 
    {
        if (entry[i]<pivot) 
        {
            last_small++;
            swap(last_small,i);
        }
    }
    swap(low,last_small);
    return last_small;
}

void Quick_sort::swap(int i,int j)
{
    List_entry temp;
    temp=entry[i];
    entry[i]=entry[j];
    entry[j]=temp;
}

int main()
{
    int n,x;
    cin>>n;
    Quick_sort l;
    for(int i=0;i<n;i++)
    {
        cin>>x;
        l.insert(i,x);
    }
    l.half_sort();
    l.traverse(print);
    cout<<endl;
    l.quick_sort();
    l.traverse(print);
    return 0;
}