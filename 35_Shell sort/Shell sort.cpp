/*
请在你实现的顺序存储的List基础上实现希尔排序。
【输入】
第一行，序列的个数n和希尔排序的分组数量m；n小于1000，m小于10；
第一行，n个整数序列，
第二行，m个分组长度。//5 3 1
【输出】
m行，对应于每次间隔下的排序中间结果
例如：
【输入】
7 3//7个整数，3个分组
26 33 35 29 19 12 22//整数序列
5 3 1//increment为5，3，1
【输出】
12 22 35 29 19 26 33 // increment为5的排序结果
12 19 26 29 22 35 33 // increment为3的排序结果
12 19 22 26 29 33 35 // increment为1的排序结果
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
    void sort(const int m,const int increment[]);
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

void List::sort(const int m, const int increment[]) 
{
    int start,first_unsorted,position,current,step;
    for(int i=0; i<m;i++) 
    {
        step=increment[i];
        start=0;
        for(first_unsorted=start+step;first_unsorted<count;first_unsorted++) 
        {
            current=entry[first_unsorted];
            position=first_unsorted;
            while(position>=start+step && entry[position-step]>current) 
            {
                entry[position]=entry[position-step];
                position-=step;
            }
            entry[position]=current;
        }
        traverse(print);
        cout<<endl;
    }
}

int main()
{
    int n,m,x;
    cin>>n>>m;
    List L;
    int increment[m];
    for(int i=0;i<n;i++)
    {
        cin>>x;
        L.insert(i,x);
    }
    for(int i=0;i<m;i++)
        cin>>increment[i];
    L.sort(m,increment);
    return 0;
}


// void Sortable_list :: shell_sort( )
// /* Post: The entries of theSortable list have been rearranged so that the keys in all
// the entries are sorted into nondecreasing order.
// Uses: sort_interval */
// {
// 	int increment, // spacing of entries in sublist
// 	     start; // starting point of sublist
// 	increment = count;
// 	do {
// 		increment = increment/3 + 1;
// 		for (start = 0; start < increment; start++)
// 		     sort_interval(start, increment); // modified insertion sort
// 	} while (increment > 1);
// } 
// void Sortable_list :: sort_interval(int start, int increment){
//     int first_unsorted; // position of first unsorted entry首个未排序项的位置
//     int position; // searches sorted part of list对列表已排序部分进行搜索
//     Record current; // holds the entry temporarily removed from list该条目暂时从列表中移除
//     for (first_unsorted = start + increment; first_unsorted < count; first_unsorted += increment )
//          if (entry[first_unsorted] < entry[first_unsorted - increment]) {
//          position = first_unsorted;
//         current = entry[first_unsorted]; // Pull unsorted entry out of the list.从列表中提取未排序的条目。
//         do { // Shift all entries until the proper position is found.将所有条目移位，直至找到合适的位置。
//             entry[position] = entry[position - increment];
//             position -= increment; // position is empty.
//         } while (position > start && entry[position - increment] > current);
//         entry[position] = current;
//     }
// }
    