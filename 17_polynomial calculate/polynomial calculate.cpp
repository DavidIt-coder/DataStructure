/*
（多项式的运算）请编写程序实现多项式的加法、减法、乘法（选做）的运算。
【输入】第一行运算符c（c可能为+，-， *）
第二行，运算符c的第一个多项式。多项式每一项的系数和指数，且按照指数的降序排列，输入0 0表示结束。
第三行，运算符c的第二个多项式。多项式每一项的系数和指数，且按照指数的降序排列，输入0 0表示结束。
其中，输入多项式每一项的系数与指数均为整数，指数非负且系数不为0。
【输出】多项式运算后的结果。用^表示指数项，例如5X2的正确输出为5X^2。
例如：
【输入】
+
3 5 6 2 12 0 0 0 //表示：3X^5+6X^2+12
7 2 1 1 0 0 //表示：7X^2+X
【输出】
3X^5+13X^2+X+12

【输入】
+
7 14 2 8 -10 6 1 0 0 0 //表示：7X^14+2X^8-10X^6+1
4 18 8 14 -3 10 10 6 -1 4 0 0 //表示：4X^18+8X^14-3X^10+10X^6-X^4
【输出】
4X^18+15X^14-3X^10+2X^8-X^4+1

注意：乘法运算为选做功能，测试用例中包含有1/3的乘法运算符，
若不支持乘法运算则将会有6个用例不能通过测试。
*/
#include<iostream>
#include<cmath>
#include<string>
#include<cstdio>
using namespace std;

enum Error_code{underflow,overflow,success};

struct term{
    int degree;//指数
    int coefficient;//系数
    term(int de = 0, int co = 0);//构造函数
};

term::term(int de, int co){
    degree=de;
    coefficient=co;
}

struct node {
    term entry; 
    node *next;
    node ();
    node (term item, node *add = NULL);
};

node::node(){
    next=NULL;
}

node::node(term item, node *add){
    entry=item;
    next=add;
}

class poly{
protected:
    node *front,*rear;
private:
    int degree();
public:
    poly();
    void clear();
    bool empty();
    Error_code append(term &item);
    Error_code serve();
    Error_code retrieve(term &item);
    Error_code serve_and_retrieve(term &item);
    ~poly();
    poly(poly &original);
    void operator = (const poly &original);
//poly:
    void read();
    void print();//打印
    void add(poly p,poly q);//加法
    void mul(poly p,poly q);//乘法
    void sub(poly p,poly q);//减法
};

poly r;

int main()
{
    poly p,q;
    char ch=getchar();
    p.read();
    q.read();
    r.clear();
    switch(ch)
    {
    case '+':
        r.add(p,q);
        break;
    case '-':
        r.sub(p,q);
        break;
    case '*':
        r.mul(p,q);
        break;
    default:
        break;
    }
    r.print();
    return 0;
}

//poly
void poly::read(){
    while(1){   
        int de, co;
        term* item;
        term item2;
        scanf("%d %d",&co,&de);
        if(co==0&&de==0) break;
        item=new term(de,co);
        item2=*item;
        append(item2);
    }
}

int poly::degree(){
    if(empty())
        return -1;
    term lead;
    retrieve(lead);//最高次项
    return lead.degree;//返回最高次项的指数
}

/*降低了复杂度的简化print函数
void poly::print() {
    node *printnode = front;
    bool firstterm = true;
    while (printnode != NULL) {
        term &t = printnode->entry;
        int r = abs(t.coefficient);
        if (!firstterm || t.coefficient < 0) 
            cout << (t.coefficient < 0 ? "-" : "+");
        firstterm = false;
        if (r != 1 || t.degree == 0) 
            cout << r;
        if (t.degree > 1) 
            cout << "X^" << t.degree;
        else if (t.degree == 1) 
            cout << "X";
        printnode = printnode->next;
    }
    if (firstterm)
        cout << "0";
    cout << endl;
}
*/

void poly::print(){
    node *printnode=front;
    bool firstterm=true;//是否是第一个项
    while(printnode!=NULL){
        term &t=printnode->entry;
        if(firstterm){
            firstterm=false;
            if(t.coefficient<0)
                cout<<"-";
        }
        else if(t.coefficient<0)
            cout<<"-";
        else cout<<"+";
        int r=abs(t.coefficient);
        if(r!=1)
            cout<<r;
        if(t.degree>1)
            cout<<"X^"<<t.degree;
        else if(t.degree==1)
            cout<<"X";
        if(r==1&&t.degree==0)
            cout<<"1";
        printnode=printnode->next;
    }
    if(firstterm)
        cout<<"0";
    cout<<endl;
}

void poly::add(poly p,poly q){
    clear();
    while(!p.empty()||!q.empty())
    {
        term p1,q1;
        if(p.degree()>q.degree()){
            p.serve_and_retrieve(p1);
            append(p1);
        }
        else if(p.degree()<q.degree()){
            q.serve_and_retrieve(q1);
            append(q1);
        }
        else{
            p.serve_and_retrieve(p1);
            q.serve_and_retrieve(q1);
            if(p1.coefficient+q1.coefficient!=0){
                term t(p1.degree,p1.coefficient+q1.coefficient);
                append(t);
            }
        }
    }
}

void poly::sub(poly p,poly q){
    clear();
    while(!p.empty()||!q.empty()){
        term p1,q1;
        if(p.degree()>q.degree()){
            p.serve_and_retrieve(p1);
            append(p1);
        }
        else if(p.degree()<q.degree()){
            q.serve_and_retrieve(q1);
            term t(q1.degree,-q1.coefficient);
            append(t);
        }
        else{
            p.serve_and_retrieve(p1);
            q.serve_and_retrieve(q1);
            if(p1.coefficient-q1.coefficient!=0){
                term t(p1.degree,p1.coefficient-q1.coefficient);
                append(t);
            }
        }
    }
}

void poly::mul(poly p,poly q){
    poly cur,ans;
    ans.clear();
    while(!p.empty()){
        cur.clear();
        poly qq=q;
        term p1,q1;
        p.serve_and_retrieve(p1);
        if(p1.coefficient==0)
            continue;//忽略系数为0的项
        while(!qq.empty()){
            qq.serve_and_retrieve(q1);
            if(q1.coefficient==0)
                continue;
            term t(p1.degree+q1.degree,p1.coefficient*q1.coefficient);
            cur.append(t);
        }
        add(ans,cur);
        ans=r;
    }
}

poly::poly(){
    front = rear = NULL;
}

void poly::clear(){
    front=rear=NULL;
}

bool poly::empty(){
    if(front==NULL)
        return true;
    return false;
}

Error_code poly::append(term &item){
    node *newptr=new node(item);
    if(newptr==NULL)
        return overflow;
    if(rear==NULL)
        front=rear=newptr;//队列为空，则头尾指针都指向新节点
    else{
        rear->next=newptr;
        rear=newptr;
    }
    return success;
}

Error_code poly::serve(){
    if(empty())
        return underflow;
    node* oldptr=front;
    front=front->next;
    if(front==NULL)
        rear=NULL;//front和rear都指向 NULL，避免出现悬挂指针的情况
    delete oldptr;
    return success;
}

Error_code poly::retrieve(term &item){
    term &t=item;
    if(empty()){
        t.degree=-1;
        return underflow;
    }
    t=front->entry;
    return success;
}

Error_code poly::serve_and_retrieve(term &item){
    if(empty())
        return underflow;
    term &t=item;
    t=front->entry;
    node* oldptr=front;
    front=front->next;
    if(front==NULL)
        rear=NULL;
    delete oldptr;
    return success;
}

poly::~poly(){
    while(!empty()){
        serve();
    }
}

poly::poly(poly &original){//拷贝构造函数,就是复制一份
    node *newfront,*newrear,*newcopy,*originalfront=original.front;
    if(originalfront==NULL)
        newfront=newrear=NULL;
    else{
        newcopy=newfront=new node(originalfront->entry);
        while(originalfront->next!=NULL){
            originalfront=originalfront->next;
            newcopy->next=new node(originalfront->entry);
            newcopy=newcopy->next;
        }
        newrear=newcopy;//rear指针指向最后一个节点
    }
    front=newfront;
    rear=newrear;
}

void poly::operator = (const poly &original){//操作符重载
    node *newfront,*newrear,*newcopy,*originalfront=original.front;
    if(originalfront==NULL)
        newfront=newrear=NULL;
    else{
        newcopy=newfront=new node(originalfront->entry);
        while(originalfront->next!=NULL){
            originalfront=originalfront->next;
            newcopy->next=new node(originalfront->entry);
            newcopy=newcopy->next;
        }
        newrear=newcopy;
    }
    while(!empty())
        serve();
    front=newfront;
    rear=newrear;
}