/*
（团队队列）有t个团队的人正在排一个长队。
每次新来一个人时，如果他有队友在排队，那么这个新人会插队到最后一个队友的身后。
如果没有任何一个队友排队，则他会排到长队的队尾。输入要求支持如下指令：
ENQUEUE x y：   x团队编号为y的人进入长队。
DEQUEUE：       长队的队首出队。
STOP：停止模拟
对于每个DEQUEUE指令，输出出队的人的编号。
【输入】输入数据包含多个测试样例，输入的每个样例第一行为团队数t（1<=t<=10），
       团队编号为1…t，接着的每行输入操作指令。
       当输入指令为STOP时，结束该样例的模拟。
       当输入样例的团队数t为0时，结束输入，无需担心指令出错。
【输出】对于每一个测试样例，输出“Scenario #k”。
       接着，对每一条DEQUEUE指令，输出出队的人的编号。
       每个测试样例以一个空白行隔开（包括最后一个测试样例）
*/
#include<iostream>
#include<string>
using namespace std;

enum outcome{underflow,overflow,success};
typedef int type;
const int maxqueue=101;

class cirqueue{
private:
    type arr[maxqueue];
    int count;
    int front,rear;
public:
    cirqueue();
    void clear();
    int size()const;
    bool empty()const;
    bool full()const;
    outcome append(const type &item);
    outcome serve();
    outcome retrieve(type &item)const;
    outcome serve_and_retrieve(type &item);
};

void operate(cirqueue team[101],cirqueue order)
{
    int x,y;
    char command[10];
    while(cin>>command)
        {
            if(command[0]=='S')
                break;
        else if(command[0]=='E')
        {
            cin>>x>>y;
            if(team[x].empty()){
                team[x].append(y);
                order.append(x);
            }
            else
                team[x].append(y);
        }
        else if(command[0]=='D')
        {
            order.retrieve(x);
            team[x].serve_and_retrieve(y);
            cout<<y<<endl;
            if(team[x].empty())
                order.serve();
        }
        }
}

int main(){
    int t=0;
    int i=0;
    while(cin>>t&&t)
    {
        cirqueue team[t+1];
        cirqueue order;
        cout<<"Scenario #"<<i+1<<endl;
        operate(team,order);
        i++;
        order.clear();
        for(int j=1;j<=t;j++)
            team[j].clear();
    }
    return 0;
}

void cirqueue::clear(){
    count=0;
}

cirqueue::cirqueue(){
    front=count=0;
    rear=maxqueue-1;
}

int cirqueue::size()const{
    return count;
}

bool cirqueue::empty()const{
    return count==0;
}

bool cirqueue::full()const{
    return count==maxqueue;
}

outcome cirqueue::append(const type &item){
    if(count==maxqueue)
        return overflow;
    count++;
    rear=((rear+1)==maxqueue)?0:rear+1;
    arr[rear]=item;
    return success;
}

outcome cirqueue::serve()
{
    if(count<=0)
        return underflow;
    count--;
    front=((front+1)==maxqueue)?0:front+1;
    return success;
}

outcome cirqueue::retrieve(type &item)const
{
    if(count<=0)
        return underflow;
    type &t=item;
    t=arr[front];
    return success;
}

outcome cirqueue::serve_and_retrieve(type &item)
{
    if(count<=0)
        return underflow;
    type& t=item;
    t=arr[front];    
    front=((front+1)==maxqueue)?0:front+1;
    count--;
    return success;
}