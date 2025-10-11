/*
Given a string, find the length of the longest substring without repeating characters.

Example 1:
Input: “abcabcbb”
Output: 3
Explanation: The answer is “abc”, with the length of 3.

Example 2:
Input: “bbbbb”
Output: 1
Explanation: The answer is “b”, with the length of 1.

Example 3:
Input: “pwwkew”
Output: 3
Explanation: The answer is “wke”, with the length of 3.
Note that the answer must be a substring, “pwke” is a subsequence and not a substring.
【输入】
第一行，长度为n的字符串，字符串中不包含空格，n小于2000。
【输出】
最大非重复子串的长度；

例如：
【输入】
pwwkew
【输出】
3
【输入】
bbbbb
【输出】
1
*/
#include <iostream>
using namespace std;
enum Error_code {not_present,overflow,duplicate_error,success};
const int Hash_size=1997;
int hash_size=256;

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
    return x.the_key() == y.the_key();
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
        Record tmp;
        table[i]=tmp;
    }
}

Error_code Hash_table::insert(const Record& new_entry)
{
    Error_code result=success;
    int probe_count,
        increment,
        probe;
    probe=myhash(new_entry);
    probe_count=0;
    increment=1;
    while(table[probe]!=0  
        &&table[probe]!=-1   
        &&table[probe]!=new_entry
        &&probe_count<(hash_size+1)/2) 
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
        probe=(probe+increment)%hash_size;
        increment+=2;
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

int lswrc(string s) 
{
    Hash_table charMap;
    int maxLen=0;
    int start=0;
    for(int end=0;end<s.size();end++) 
    {
        Record found;
        if(charMap.retrieve(Key(s[end]),found)==success&&found.the_other()>=start)
            start=found.the_other()+1;
        charMap.remove(Key(s[end]),found);
        charMap.insert(Record(s[end],end));
        maxLen=max(maxLen,end-start+1);
    }
    return maxLen;
}

int main()
{
    string s;
    cin>>s;
    cout<<lswrc(s);
    return 0;
}