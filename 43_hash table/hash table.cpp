/*
请实现顺序存储的Hash Table。Hash函数用取余法（Modular Arithmetic，除数为小于Hash表大小），
冲突检测算法为平方探测，考虑overflow的情况。
【输入】
第一行，整数n和m，n表示hash表的大小，m代表插入hash表的元素个数。n为小于2000的素数，m小于n。
第二行，m对的值
第三行，任意查询的key1
第四行，任意查询的key2
【输出】
第一行，探测到key1的过程及key1对应的value；
第二行，探测到key2的过程及key2对应的value；
注意若key在hash表中不存在，则输出NULL。
例如：
【输入】
13 6//hash函数为 key%13
16 16 3 3 29 29 26 26 39 39 52 52//6对的值
52
20
【输出】
0 1 4 9 52 52//先后探测了0，1，4，9等位置，且探测成功；
7 8 NULL//先后探测了位置7和8，探测失败；
*/
#include <iostream>
using namespace std;
enum Error_code {not_present,overflow,duplicate_error,success};
const int Hash_size=2013;
int hash_size;

class Key
{
private:
    int key;
public:
    Key(int x=0);
    int the_key()const;
};

Key::Key(int x)
{
    key = x;
}

int Key::the_key()const
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
    Record(int x = 0, int y = 0);
    int the_key()const;
    int the_other()const;
private:
    int key;
    int other;
};

Record::operator Key()
{
    Key tmp(key);
    return tmp;
}
Record::Record(int x, int y)
{
    key = x;
    other = y;
}
int Record::the_key()const
{
    return key;
}
int Record::the_other()const
{
    return other;
}

bool operator!=(const Record& x, const Record& y)
{
    return x.the_other() != y.the_other();
}

bool operator==(const Record& x, const Record& y)
{
    return x.the_key() == y.the_other();
}


class Hash_table
{
public:
    void clear();
    Error_code insert(const Record& new_entry);
    Error_code retrieve(const Key& target, Record& found)const;
    Error_code remove(const Key& target, Record& found);
private:
    Record table[Hash_size];
};

int myhash(const Record& new_entry)
{
    return new_entry.the_key()%hash_size;
}

int myhash(const Key& new_entry)
{
    return new_entry.the_key()%hash_size;
}

void Hash_table::clear()
{
    for(int i=0;i<hash_size;i++) 
    {
        Record tmp;//已经初始为0
        table[i]=tmp;
    }
}

//平方探测
Error_code Hash_table::insert(const Record& new_entry)
{
    Error_code result=success;
    int probe_count,//探测次数
        increment,//增量
        probe;//现在的位置码
    probe=myhash(new_entry);
    probe_count=0;
    increment=1;
    while(table[probe]!=0              //不是空
        &&table[probe]!=-1             //是空的但是已经删除了
        &&table[probe]!=new_entry
        &&probe_count<(hash_size+1)/2) //没到最多次数
    {
        probe_count++;
        probe=(probe+increment)%hash_size;
        increment+=2;
    }
    if(table[probe]==0) 
        table[probe]=new_entry;
    else if(table[probe]==-1) 
        table[probe]=new_entry;
    else if(table[probe]==new_entry) 
        return duplicate_error;
    else result=overflow;
    return result;
}

Error_code Hash_table::retrieve(const Key& target, Record& found)const
{
    int probe_count,increment,probe;
    probe=myhash(target);
    probe_count=0;
    increment=1;
    while(table[probe]!=0&&table[probe].the_key()!=target.the_key()&&probe_count<(hash_size+1)/2) 
    {
        probe_count++;
        cout<<probe<<' ';
        probe=(probe+increment)%hash_size;
        increment+=2;
    }
    if (probe_count<(hash_size+1)/2)//判断是否出界，没出界就输出
    {
        cout<<probe<<' ';//找到了之后就出循环了,所以还要输出一遍
    }
    if(table[probe].the_key()==target.the_key()) 
    {
        found=table[probe];
        return success;
    }
    return not_present;
}

Error_code Hash_table::remove(const Key& target,Record& found)
{
    int probe_count,increment,probe;
    probe=myhash(target);
    probe_count=0;
    increment=1;
    while(table[probe]!=0&&table[probe].the_key()!=target.the_key()&&probe_count<(hash_size+1)/2) 
    {
        probe_count++;
        probe=(probe+increment)%hash_size;
        increment+=2;
    }
    if(table[probe].the_key()==target.the_key()) 
    {
        found=table[probe];
        table[probe]=-1;
        return success;
    }
    return not_present;
}

int main()
{
    Hash_table a;
    int m,key,value;
    cin>>hash_size>>m;
    while(m--)   //for(int i=0;i<m;i++)
    {
        cin>>key>>value;
        a.insert(Record(key,value));
    }
    m=2;
    while(m--) //查询key1，key2
    {
        cin>>key;
        Record temp;
        Error_code outcome;
        outcome=a.retrieve(Key(key),temp);
        if (outcome==success) 
            cout<<key<<' '<<temp.the_other()<<endl;
        else cout<<"NULL"<<endl;
    }
    return 0;
}