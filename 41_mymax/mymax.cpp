#include<iostream>
using namespace std;

template<class type>
type mymax(type a,type b)
{
    return a>b?a:b;
}

int main() 
{
    double a=3.5,b=4.2;
    int c=5,d=6;
    char e='a',f='b';
    cout<<mymax(a,b)<<endl;
    cout<<mymax(c,d)<<endl;
    cout<<mymax(e,f)<<endl;
//    cout<<mymax(a,c)<<endl;
    return 0;
}
