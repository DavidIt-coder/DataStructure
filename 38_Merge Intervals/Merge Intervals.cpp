/*
Given a collection of intervals, merge all overlapping intervals.
Example 1:
Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:
Input: [[1,4],[4,5], [3,7]]
Output: [[1,7]]
Explanation: Intervals [1,4], [4,5] and [3, 7] are considered overlapping.
【输入】第一行，数字n，表示区间的数量，n大于1小于2000；
第二行，n对区间；
【输出】 合并后的区间。
例如：
【输入】
4
1 3 2 6 8 10 15 18
【输出】
1 6 8 10 15 18
*/
#include <iostream>
using namespace std;

enum Error_code{underflow,overflow,range_Error,success };
typedef int List_entry;
typedef int Node_entry;

struct Node
{
    Node_entry entry;
    Node* next;
    Node();
    Node(Node_entry item, Node* add_on = NULL);
};

Node::Node()
{
    next=NULL;
}

Node::Node(Node_entry item, Node* add_on)
{
    entry=item;
    next=add_on;
}

class List
{
public:
    List();
    ~List();
    List(const List& copy);
    void operator=(const List& copy);
    int size() const;
    bool full() const;
    bool empty() const;
    void clear();
    Node*& get_head();
    Error_code insert(int position, const List_entry& x);
    Error_code remove(int position, List_entry& x);
    Error_code retrieve(int position, List_entry& x) const;
    Error_code replace(int position, List_entry& x);
    void traverse(void(*visit)(List_entry& x));
protected:
    int count;
    Node* head;
    Node* set_position(int position) const;
};

Node* List::set_position(int position) const
{
    Node* q=head;
    for (int i=0;i<position;i++) 
        q=q->next;
    return q;
}

List::List()
{
    count=0;
    head=NULL;
}

List::~List()
{
    List_entry x;
    while(!empty())
        remove(0,x);
}

List::List(const List& copy)
{
    count=0;
    head=NULL;
    Node* newptr=copy.head;
    while (newptr)
    {
        insert(size(),newptr->entry);
        newptr=newptr->next;
    }
}

void List::operator=(const List& copy)
{
    List_entry x;
    if (this==&copy) 
        return;
    while (!empty()) 
        remove(0,x);
    Node* newptr=copy.head;
    while (newptr)
    {
        insert(size(), newptr->entry);
        newptr = newptr->next;
    }
}

int List::size() const
{
    return count;
}

bool List::full() const
{
    Node* newptr = new Node();
    if (newptr == NULL) return true;
    delete newptr;
    return false;
}

bool List::empty() const
{
    if (count == 0) return true;
    return false;
}

void List::clear()
{
    List_entry x;
    remove(0, x);
}

Error_code List::insert(int position, const List_entry& x)
{
    if (position < 0 || position > count) return range_Error;
    Node* newptr, * previous = NULL, * following;
    if (position > 0)
    {
        previous = set_position(position - 1);
        following = previous->next;
    }
    else following = head;
    newptr = new Node(x, following);
    if (newptr == NULL) return overflow;
    if (position == 0) head = newptr;
    else previous->next = newptr;
    count++;
    return success;
}

Error_code List::remove(int position, List_entry& x)
{
    if (position<0||position>=count) 
        return range_Error;
    Node* previous, * following;
    if (position>0)
    {
        previous = set_position(position - 1);
        following = previous->next;
        previous->next = following->next;
    }
    else
    {
        following=head;
        head=head->next;
    }
    List_entry& y=x;
    y=following->entry;
    delete following;
    count--;
    return success;
}

Error_code List::retrieve(int position, List_entry& x) const
{
    if (position < 0 || position >= count) return range_Error;
    Node* newptr = set_position(position);
    List_entry& y=x;
    y=newptr->entry;
    return success;
}

Error_code List::replace(int position, List_entry& x)
{
    if (position < 0 || position >= count) return range_Error;
    Node* newptr = set_position(position);
    newptr->entry = x;
    return success;
}

void List::traverse(void(*visit)(List_entry& x))
{
    Node* newptr = head;
    while (newptr)
    {
        (*visit)(newptr->entry);
        newptr = newptr->next;
    }
}

Node*& List::get_head()
{
    return head;
}

void print(List_entry& x)
{
    cout << x << ' ';
}

Node* divide_from(Node* sub_list)
{
    Node* position, * midpoint, * second_half;
    if ((midpoint = sub_list) == NULL) return NULL;
    position = midpoint->next;
    while (position != NULL)
    {
        position = position->next;
        if (position != NULL)
        {
            midpoint = midpoint->next;
            position = position->next;
        }
    }
    second_half = midpoint->next;
    midpoint->next = NULL;
    return second_half;
}

Node* merge(Node* first, Node* second)
{
    Node* last_sorted;
    Node combined;
    last_sorted = &combined;
    while (first != NULL && second != NULL)
    {
        if (first->entry <= second->entry)
        {
            last_sorted->next = first;
            last_sorted = first;
            first = first->next;
        }
        else
        {
            last_sorted->next = second;
            last_sorted = second;
            second = second->next;
        }
    }
    if (first == NULL)
        last_sorted->next = second;
    else
        last_sorted->next = first;
    return combined.next;
}

void recursive_Mergesort(Node*& sub_list)
{
    if (sub_list != NULL && sub_list->next != NULL)
    {
        Node* second_half = divide_from(sub_list);
        recursive_Mergesort(sub_list);
        recursive_Mergesort(second_half);
        sub_list = merge(sub_list, second_half);
    }
}

struct Interval
{
    int start;
    int end;
    Interval();
    Interval(int x, int y);
};

Interval::Interval()
{
    start = 0;
    end = 0;
}

Interval::Interval(int x, int y)
{
    start = x;
    end = y;
}

class Solution
{
public:
    List merge(List& starts, List& ends) 
    {
        recursive_Mergesort(starts.get_head());
        recursive_Mergesort(ends.get_head());
        List res;
        int j=0;
        for (int i=0;i<starts.size();i++) 
        {
            List_entry start,end;
            starts.retrieve(i,start);
            ends.retrieve(i,end);
            while (i<starts.size()-1) 
            {
                List_entry next_start;
                starts.retrieve(i+1,next_start);
                if (next_start>end) 
                    break;
                i++;
                ends.retrieve(i,end);
            }
            res.insert(res.size(),start);
            res.insert(res.size(),end);
        }
        return res;
    }
};

void print_interval(List_entry& x)
{
    static bool is_start = true;
    if (is_start) 
    {
        cout<<x<<' ';
        is_start=false;
    } 
    else 
    {
        cout<<x <<' ';
        is_start=true;
    }
}

int main()
{
    Solution a;
    List starts,ends;
    int n,s,e;
    cin>>n;
    for (int i = 0; i < n; i++) 
    {
        cin>>s>>e;
        starts.insert(starts.size(),s);
        ends.insert(ends.size(),e);
    }
    List ans=a.merge(starts, ends);
    ans.traverse(print_interval);
    return 0;
}
