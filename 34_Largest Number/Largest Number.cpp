/*
Given a list of non negative integers,
arrange them such that they form the largest number.
Example 1:
Input: [10,2]
Output: “210”
Example 2:
Input: [3,30,34,5,9]
Output: “9534330”
【输入】n个非负数，n大于1小于1000，序列n长度小于1000；
【输出】n个非负数组成的最大值。
例如：
【输入】
3 30 34 5 9
【输出】
9534330
*/
#include<iostream>
#include<string>
using namespace std;
enum Error_code{underflow,overflow,rangeerror,success};
const int max_list=1000;

template<typename List_entry>
void print(List_entry &x)
{
    cout<<x;
}

template<typename List_entry>
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
    void swap(int low,int high)
    {
        List_entry temp;
        temp=entry[low];
        entry[low]=entry[high];
        entry[high]=temp;
    }
    int max_key(int low,int high);
protected:
	int count;
	List_entry entry[max_list];
};

template<typename List_entry>
List<List_entry>::List()
{
    count=0;
}

template<typename List_entry>
int List<List_entry>::size() const
{
    return count;
}

template<typename List_entry>
bool List<List_entry>::full() const
{
    if(count==max_list)
        return true;
    return false;
}

template<typename List_entry>
bool List<List_entry>::empty() const
{
    if(count==0)
        return true;
    return false;
}

template<typename List_entry>
void List<List_entry>::clear()
{
    count=0;
}

template<typename List_entry>
Error_code List<List_entry>::insert(int position,const List_entry &x)
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

template<typename List_entry>
Error_code List<List_entry>::remove(int position,List_entry &x)
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

template<typename List_entry>
Error_code List<List_entry>::replace(int position,const List_entry &x)
{
    if(position<0||position>=count)
        return rangeerror;
    entry[position]=x;
	return success;
}

template<typename List_entry>
Error_code List<List_entry>::retrieve(int position,List_entry &x) const
{
    if(position<0||position>=count)
        return rangeerror;
    List_entry &y=x;
    y=entry[position];
    return success;
}

template<typename List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
{
    for(int i=0;i<count;i++)
        (*visit)(entry[i]);
}

bool compareString(const string& a,const string& b) 
{
    return a+b>b+a;
}

template<typename List_entry>
int List<List_entry>::max_key(int low,int high)
{
    int max,current;
    max=low;
    for(current=low+1;current<=high;current++)
    {
        if(compareString(entry[current],entry[max]))
            max=current;
    }
    return max;
}

template<typename List_entry>
void List<List_entry>::select_sort()
{
    for(int position=0;position<count-1;position++)
    {
        int max=max_key(position,count-1);
        swap(position,max);
    }
    traverse(print);
}

int main()
{
    int x;
    List<string> list;
    int i=0;
    while(cin>>x)
    {
        string s;
        s=to_string(x);
        list.insert(i,s);   
        i++;
    }
    list.select_sort();
    return 0;
}