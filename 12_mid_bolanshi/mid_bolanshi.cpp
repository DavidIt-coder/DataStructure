/*
(中序波兰式求解) 请编写程序求解中序波兰式的值。表达式中可能的运算符有+，-，*，/，（）。
【输入】中序波兰式
【输出】波兰式的值 //输出的数据类型符合C/C++对表达式求值的定义，
        即表达式的输出类型由高精度的运算数来决定。
        浮点型保留小数点后的3位小数
例如：
【输入】2*(4+5)-12
【输出】6
【输入】2*2.5
【输出】5.000
备注：
（1）对于80%的测试数据运算数中仅仅包含正整数；
（2）对于10%的测试数据运算数中包含有浮点数；
（3）对于10%的测试数据运算数中包含有负数；
*/
#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>
using namespace std;

#define maxstack 1000

enum outcome{overflow,underflow,success,failure};
typedef double T;

template<typename type>
class stack
{
private:
    int count;
    type arr[maxstack+1];
public:
    stack()
    {
        count=0;
    }
    outcome push(const type &item)
    {
        if(count<maxstack)
        {
            count++;
            arr[count]=item;
            return success;
        }
        return overflow;
    }
    outcome pop()
    {
        if(count>0)
        {
            count--;
            return success;
        }
        return underflow;
    } 
    outcome top(type &now_top)const
    {
        if(count==0)
            return underflow;
        type &t=now_top;
        t = arr[count];
        return success;
    }
    bool empty()const
    {
        return count==0;
    }
    bool full()const
    {
        return count==maxstack;
    }
    void clear()
    {
        count=0;
    }
};

class expression
{
private:
    stack<double> num;
    stack<char> op;
public:
    string s;
    string Type;
    expression();
    outcome judgement();
    T calculate(char op);
    int iswhat(char c);
    outcome digit(string s,int &i);
    outcome operators(string s,int &i);
    outcome right(string s,int i);
    T answer();
};

outcome expression::judgement()
{
    for(int i=0; i < s.length(); i++) 
    {
        if (iswhat(s[i]) == 1 || iswhat(s[i]) == 5)
            digit(s, i);
        else if ((s[i] == '-' || s[i] == '+') && (i == 0 || (i > 0 && (s[i-1] == '(' || iswhat(s[i-1]) == 2)))) 
        {
            num.push(0);
            op.push(s[i]);
        } 
        else if (iswhat(s[i]) == 2)
            operators(s, i);
        else if (iswhat(s[i]) == 3)
            op.push(s[i]);
        else if (iswhat(s[i]) == 4)
            right(s, i);
        else
            return failure;
    }
    return success;
}

expression::expression() {}

int expression::iswhat(char c)
{
    if(c>='0'&&c<='9')
        return 1;
    else if(c=='+'||c=='-'||c=='*'||c=='/')
        return 2;
    else if(c=='(')
        return 3;
    else if(c==')')
        return 4;
    else if(c=='.')
        return 5;
    return 0;
}

T expression::calculate(char op)
{
    T x,y;
    num.top(y);
    num.pop();
    num.top(x);
    num.pop();
    switch(op)
    {
    case '+':
        return x+y;
    case '-':
        return x-y;
    case '*':
        return x*y;
    case '/':
        if(Type!="double"&&(int)x%(int)y!=0)
            Type="double";
        return x/y;
    default:
        return 0;
    }
}

T expression::answer()
{
    judgement();
    while(!op.empty()) 
    {
        char c;
        op.top(c);
        T x = calculate(c);
        num.push(x);
        op.pop();
    }
    T ans;
    num.top(ans);
    return ans;
}

outcome expression::digit(string s, int &i) 
{
    
    T sum = 0.0;
    bool has_dot = false;
    T t = 0.1;
    while (i < s.length()) 
    {
        char c = s[i];
        if (iswhat(c) == 1) 
        {
            if (has_dot==false) 
                sum = sum * 10 + (c - '0');
            else 
            {
                sum += (c - '0')*t;
                t*= 0.1;
            }
            i++;
        } 
        else if (c == '.')
        {
            has_dot = true;
            Type = "double";
            i++;
        } 
        else
            break;
    }
    i--;
    num.push(sum);
    return success;
}

outcome expression::operators(string s, int &i)
{
    char current_op = s[i];
    while (!op.empty()) 
    {
        char top_op;
        op.top(top_op);
        if (top_op == '(') 
            break;
        if ((current_op == '+' || current_op == '-') && (top_op == '*' || top_op == '/')) 
        {
            T result = calculate(top_op);
            num.push(result);
            op.pop();
        } 
        else if ((current_op == '*' || current_op == '/') && (top_op == '+' || top_op == '-')) 
            break;
        else 
        {
            T result = calculate(top_op);
            num.push(result);
            op.pop();
        }
    }
    op.push(current_op);
    return success;
}

outcome expression::right(string s, int i)
{
    char c;
    while (op.top(c) == success && c != '(') 
    {
        T x = calculate(c);
        num.push(x);
        op.pop();
    }
    op.pop();
    return success;
}

int main()
{
    string s;
    cin >> s;
    expression e;
    e.s = s;
    T ans = e.answer();
    if (e.Type == "double") 
        printf("%.3lf", ans);
    else 
        printf("%d", (int)ans);
    return 0;
}