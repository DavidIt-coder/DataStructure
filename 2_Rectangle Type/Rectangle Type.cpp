#include <iostream>

using namespace std;

class RectangleType
{
private:
    int length;
    int width;

public:
    int area();
    int perimeter();
    void print();

    RectangleType();
    RectangleType(int, int);
};

int RectangleType::area()
{
    return width*length;
}

int RectangleType::perimeter()
{
    return 2*(width+length);
}

void RectangleType::print()
{
    cout<<"Width:"<<width<<endl;
    cout<<"Length:"<<length<<endl;
    cout<<"Area:"<<area()<<endl;
    cout<<"perimeter:"<<perimeter()<<endl;

    cout<<endl;
}

RectangleType::RectangleType()
{
    width = 0;
    length = 0;
}

RectangleType::RectangleType(int w, int l)
{
    width = w;
    length =l;
}



int main()
{
    RectangleType rt1(20,35);
    RectangleType rt2(12,25);

    rt1.print();
    rt2.print();
    return 0;
}
