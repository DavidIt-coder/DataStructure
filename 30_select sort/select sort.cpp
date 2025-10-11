/*
请在你实现的顺序存储的List基础上实现选择排序（按照找最小值的方法来实现选择排序）。
【输入】
第一行，待排序序列个数n，序列长度小于1000；
第二行，n个整数序列；
【输出】
选择排序的中间结果，即当有序序列长度为n/2时的中间结果；
选择排序的最终结果；
例如：
【输入】
5
9 3 8 2 5
【输出】
2 3 8 9 5//输出有序序列长度为2（5/2）时的结果
2 3 5 8 9
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
    void select_sort();
    int min_key(int low,int high);
    void swap(int low,int high);
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

int List::min_key(int low,int high)
{
    int min,current;
    min=low;
    for(current=low+1;current<=high;current++)
    {
        if(entry[current]<entry[min])
            min=current;
    }
    return min;
}

void List::swap(int low,int high)
{
    int temp;
    temp=entry[low];
    entry[low]=entry[high];
    entry[high]=temp;
}

void print(List_entry &x)
{
    cout<<x<<" ";
}

void List::select_sort()
{
    for(int position=0;position<count-1;position++)
    {
        int min=min_key(position,count-1);
        swap(position,min);
        if(position==count/2-1)
        {
            traverse(print);
            cout<<endl;
        }
    }
    traverse(print);
}

int main()
{
    int n;
    cin>>n;
    List l;
    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        l.insert(i,x);
    }
    l.select_sort();
    return 0;
}