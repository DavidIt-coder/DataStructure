#include <iostream>
#include <queue>
#include <list>
using namespace std;

typedef int Vertex;

template <int max_size>
class Digraph 
{
private:
    int count;
    list<Vertex> neighbors[max_size];
public:
    Digraph(int n):count(n) {}
    void add_edge(int s,int e);
    void sort_neighbors(int v);
    void traverse(Vertex& v,bool visited[],void (*visit)(Vertex&)) const;
    void depth_first(void (*visit)(Vertex&)) const;
    void breadth_first(void (*visit)(Vertex&)) const;
};

template <int max_size>
void Digraph<max_size>::add_edge(int s,int e) 
{
    if(s>=count||e>=count||s<0||e<0) 
        return;
    neighbors[s].push_back(e);
    neighbors[e].push_back(s);
}

template <int max_size>
void Digraph<max_size>::sort_neighbors(int v) 
{
    neighbors[v].sort(); 
}

template <int max_size>
void Digraph<max_size>::traverse(Vertex& v,bool visited[],void (*visit)(Vertex&)) const 
{
    visited[v]=true;
    (*visit)(v);
    for(Vertex w: neighbors[v]) 
        if(!visited[w]) 
            traverse(w,visited,visit);
}

template <int max_size>
void Digraph<max_size>::depth_first(void (*visit)(Vertex&)) const 
{
    bool visited[max_size]={false};
    for(int v=0;v<count;v++)
        if(!visited[v])
            traverse(v,visited,visit);
}

template <int max_size>
void Digraph<max_size>::breadth_first(void (*visit)(Vertex&)) const 
{
    queue<Vertex> q;
    bool visited[max_size]={false};

    for(int v=0;v<count;v++) 
    {
        if(visited[v]) 
            continue;
        q.push(v);
        visited[v]=true;
        while(!q.empty()) 
        {
            Vertex w=q.front();
            q.pop();
            (*visit)(w);
            for(Vertex x:neighbors[w]) 
            {
                if(visited[x]) 
                    continue;
                q.push(x);
                visited[x]=true;
            }
        }
    }
}


void print(Vertex& x) 
{
    cout<<x<<" ";
}

int main() 
{
    int n,m;
    cin>>n>>m;
    Digraph<500> g(n);
    for(int i=0;i<m;i++) 
    {
        int s,e;
        cin>>s>>e;
        g.add_edge(s,e);
    }
    for(int i=0;i<n;i++)
        g.sort_neighbors(i);
    g.depth_first(print);
    cout<<endl;
    g.breadth_first(print);
    cout<<endl;
    return 0;
}