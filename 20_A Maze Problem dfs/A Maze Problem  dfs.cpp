/*
A maze is to be represented by a 12*12 array composed of three values: 
Open, Wall, or Exit. 
There is one exit from the maze. 
Write a program to determine whether it is possible to exit the maze 
from the starting point (any open square can be a starting point). 
You may move vertically and horizontally to any adjacent open square(左右上下四个方向). 
You may not move to a square containing a wall. 
The input consists of a series of 12 lines of 12 characters each, 
representing the contents of each square in the maze. 
The characters are O, W, or E.
【输入】 12×12的迷宫方阵，
每个格子的可能取值有：O, W, or E，输入数据能够确保迷宫只有一个出口。
任意3个起点的坐标,格式如下(x,y)。
其中x为纵坐标，y为横坐标，起始坐标从左上角的格子开始，坐标起始值为0.
【输出】
起点到出口的最短路径长度（经过多少个方格），
若起点无法到达出口则输出-1。起始节点和结束节点都算入路径长度的计算。

例如：
【输入】
O W O W O W O O W O W O
O W O W W W W O W O O E
O W W W O O O O O O O O
W W W O O O O W W W O W
O O O O W W W O O O O O
O O W O W O W O W O W W
O W W O O O W W O O O W
O O W O O W W W O O O O
O O O W O O O O W W W W
W W W O O O O W W W O O
O W W W W O O O O O W W
W W W O O O O O W W W W
(0,0) (5,7) (7,8)
【输出】
-1 9 10
【解释】
输出表示第一个点（0，0）无法到达出口；
第二个点（5，7）到达出口的最短路径是9；
第三个点（7，8）到达出口的最短路径是10；
*/
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define maxn 12

class Maze
{
private:
    bool visited[maxn][maxn];
public:
    Maze();
    char maze[maxn][maxn];
    void find(int& x,int& y,string str);
    int path(int x,int y);
};

int main()
{
    Maze m;
    string str[3];
    int ans[3];
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            cin>>m.maze[i][j];
    for(int i=0;i<3;i++)
    {
        int x,y;
        cin>>str[i];
        m.find(x,y,str[i]);
        ans[i]=m.path(x,y);
    }
    for(int i=0;i<3;i++)
        cout<<ans[i]<<" ";
    return 0;
}

Maze::Maze()
{
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            visited[i][j]=false;
}

void Maze::find(int &x1,int &y1,string str)
{
    int &x=x1, &y=y1;
    for(int j=1;j<str.length();j++)
        {
            if(str[j-1]=='('&&str[j+1]==',')
                x=str[j]-'0';
            else if(str[j-1]=='('&&str[j+2]==',')
            {
                x=str[j]-'0';
                x=x*10+(str[j+1]-'0');
                j++;
            }
            else if(str[j-1]==','&&str[j+1]==')')
                y=str[j]-'0';
            else if(str[j-1]==','&&str[j+2]==')')
            {
                y=str[j]-'0';
                y=y*10+(str[j+1]-'0');
                j++;
            }
        }
}


int Maze::path(int x,int y)
{
    if(maze[x][y]=='E')
        return 1;
    else if(maze[x][y]=='O'&&(!visited[x][y]))
    {
        visited[x][y]=true;
        int paths[4]={-1,-1,-1,-1};
        if(x-1>=0&&maze[x-1][y]!='W')
            paths[0]=path(x-1,y);
        if(x+1<maxn&&maze[x+1][y]!='W')
            paths[1]=path(x+1,y);
        if(y-1>=0&&maze[x][y-1]!='W')
            paths[2]=path(x,y-1);
        if(y+1<maxn&&maze[x][y+1]!='W')
            paths[3]=path(x,y+1);
        visited[x][y]=false;
        int length=-1;
        for(int i=0;i<4;i++)
        {
            if(paths[i]!=-1&&(length==-1||paths[i]<length))
                length=paths[i];
        }
        return (length==-1)?-1:length+1;
    }
    return -1;
}

/*
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define maxn 12

class Maze
{
private:
    bool visited[maxn][maxn];
public:
    Maze();
    char maze[maxn][maxn];
    void find(int& x, int& y, string str);
    int path(int x, int y);
    void resetVisited();
};

Maze::Maze()
{
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            visited[i][j]=false;
}

void Maze::find(int &x1, int &y1, string str)
{
    int &x=x1, &y=y1;
    if(str[0]!='('||str[str.length()-1]!=')'||str.find(',')==string::npos)
    {
        cerr<<"Invalid coordinate format: "<<str<<endl;
        x=-1;
        y=-1;
        return;
    }
    size_t commaPos=str.find(',');
    x=stoi(str.substr(1,commaPos-1));
    y=stoi(str.substr(commaPos+1,str.length()-commaPos-2));
}

int Maze::path(int x, int y)
{
    if(x<0||x>=maxn||y<0||y>=maxn)
        return-1;
    if(maze[x][y]=='E')
        return 1;
    else if(maze[x][y]=='O'&& !visited[x][y])
    {
        visited[x][y]=true;
        int paths[4]={-1,-1,-1,-1};
        if(x-1>=0&&maze[x-1][y]!='W')
            paths[0]=path(x-1,y);
        if(x+1<maxn&&maze[x+1][y]!='W')
            paths[1]=path(x+1,y);
        if(y-1>=0&&maze[x][y-1]!='W')
            paths[2]=path(x,y-1);
        if(y+1<maxn&&maze[x][y+1]!='W')
            paths[3]=path(x,y+1);
        visited[x][y]=false;
        int length=-1;
        for(int i=0;i<4;i++)
        {
            if(paths[i]!=-1&&(length==-1||paths[i]<length))
                length=paths[i];
        }
        return(length==-1)?-1:length+1;
    }
    return-1;
}

void Maze::resetVisited()
{
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            visited[i][j]=false;
}

int main()
{
    Maze m;
    string str[3];
    int ans[3];
    for(int i=0;i<maxn;i++)
        for(int j=0;j<maxn;j++)
            cin>>m.maze[i][j];
    for(int i=0;i<3;i++)
    {
        int x,y;
        cin>>str[i];
        m.find(x,y,str[i]);
        if(x<0||y<0)
            ans[i]=-1;
        else
            ans[i]=m.path(x,y);
        m.resetVisited();
    }
    for(int i=0;i<3;i++)
        cout<<ans[i]<<" ";
    return 0;
}

*/