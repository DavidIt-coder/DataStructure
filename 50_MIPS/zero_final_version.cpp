#include<iostream>
#include<cstdio>
#include<cmath>
#include<chrono>
using namespace std;

const int MAX_N=10000;          //最多10000个文档
const int MAX_D=2000;           //每个文档最多2000个维度
const int MAX_K=50;             //最多查询top-k=50个
const int MAX_POSTINGS=200000;  //倒排链表总空间

struct PostingNode          //倒排表节点（单向链表）
{
    int vec_id;             //文档编号
    float val;              //当前维度的权重
    PostingNode* next;      //链表指针
};

class LinkedList 
{
private:
    PostingNode* head;
public:
    LinkedList()
    {
        head=nullptr;
    }

//插入节点到链表头部（倒排索引链表从前插入）
    void push_front(PostingNode* node) 
    {
        node->next=head;
        head=node;
    }

//获取链表首节点
    PostingNode* begin()const 
    {
        return head;
    }
};

struct Result       //查询结果
{
    int id;         //文档编号
    float score;    //得分
};


class MinHeap       //Top-k小根堆（用于保留当前得分最高的k个文档）
{
private:
    Result heap[MAX_K+1];       //堆数组heap[1]是堆顶
    int size;                  //当前堆中元素个数
    int k;                     //最大容量（top-k）

//比较函数：分数小的优先出堆，若分数相同则id大的优先出堆
    bool better(int i,int j) 
    {
        if(heap[i].score!=heap[j].score)
            return heap[i].score<heap[j].score;
        return heap[i].id>heap[j].id;
    }

//交换两个堆元素
    void swap(int i,int j) 
    {
        Result tmp=heap[i];
        heap[i]=heap[j];
        heap[j]=tmp;
    }

//上浮维护堆
    void up(int i) 
    {
        while(i>1&&better(i,i/2)) 
        {
            swap(i,i/2);
            i/=2;
        }
    }

//下沉维护堆
    void down(int i) 
    {
        while (2*i<=size) 
        {
            int j=2*i;
            if(j+1<=size &&better(j+1,j))
                j++;
            if(!better(j,i)) 
                break;
            swap(i,j);
            i=j;
        }
    }
public:
    MinHeap(int topk):size(0),k(topk){}

//插入新结果（只保留 top-k）
    void push(int id,float score)
    {
        if(size<k) 
        {
            heap[++size]={id,score};
            up(size);
        } 
        else if(score>heap[1].score||(fabs(score-heap[1].score)<1e-6&&id<heap[1].id)) 
        {
            heap[1]={id,score};
            down(1);
        }
    }

//排序输出结果（按得分从大到小，若相等则按id升序）
    void sort(Result* output) 
    {
        for(int i=1;i<=size;i++)
            output[i-1]=heap[i];
        for(int i=0;i<size;i++) 
        {
            for(int j=i+1;j<size;j++)
            {
                if(output[j].score>output[i].score||(fabs(output[j].score-output[i].score)<1e-6&&output[j].id<output[i].id)) 
                {
                    Result tmp=output[i];
                    output[i]=output[j];
                    output[j]=tmp;
                }
            }
        }
    }

    int get_size() 
    {
        return size;
    }
};

class InvertedIndex        //倒排索引类
{
private:
    LinkedList lists[MAX_D];            //每个维度的倒排链表
    PostingNode pool[MAX_POSTINGS];     //分配节点池
    int pool_ptr=0;                     //节点分配指针
public:
//向维度term_id的倒排链表添加一个文档vec_id的信息
    void add(int term_id,int vec_id,float val) 
    {
        PostingNode* node=&pool[pool_ptr++];
        node->vec_id=vec_id;
        node->val=val;
        node->next=nullptr;
        lists[term_id].push_front(node);
    }

//执行最大内积搜索（MIPS）
    void query(int* qidx,float* qval,int qnnz,int n,int topk) 
    {
        float scores[MAX_N]={0};    //各文档得分累加
        bool used[MAX_N]={false};   //记录哪些访问过的文档
        //遍历查询向量的每一维
        for(int i=0;i<qnnz;i++)
        {
            int term=qidx[i];
            float qv=qval[i];
            //遍历该维度的倒排表，累加内积得分
            for(PostingNode* p=lists[term].begin();p;p=p->next) 
            {
                scores[p->vec_id]+=p->val*qv;
                used[p->vec_id]=true;
            }
        }
        //构建top-k小根堆
        MinHeap heap(topk);
        for(int i=0;i<n;i++) 
            if(used[i]) 
                heap.push(i,scores[i]);
        //输出结果
        Result results[MAX_K];
        heap.sort(results);
        for(int i=0;i<topk;i++)
            printf("%d%c",results[i].id,(i==topk-1?'\n':' '));
    }
};

int main() 
{
    //读取数据
    #ifndef ONLINE_JUDGE
        freopen("80000_rand_query1875times_3.in","r",stdin);
        freopen("80000_rand_query1875times_3.out","w",stdout);
    #endif
    //记录程序开始时间点
    auto start=std::chrono::high_resolution_clock::now();
    int n,d,totalNnz,k;
    scanf("%d %d %d %d",&n,&d,&totalNnz,&k);
    //读取base向量（CSR格式）
    int* indptr=new int[n + 1];
    int* indices=new int[totalNnz];
    float* data=new float[totalNnz];
    for(int i=0;i<=n;i++) 
        scanf("%d",&indptr[i]);
    for(int i=0;i<totalNnz;i++) 
        scanf("%d",&indices[i]);
    for(int i=0;i<totalNnz;i++) 
        scanf("%f",&data[i]);
    //构建倒排索引
    InvertedIndex index;
    for(int i=0;i<n;i++)
        for(int j=indptr[i];j<indptr[i + 1];j++)
            index.add(indices[j],i,data[j]);
    //查询处理
    int nq;
    scanf("%d",&nq);
    for(int q=0;q<nq;q++) 
    {
        int qnnz;
        scanf("%d",&qnnz);
        int qidx[200];
        float qval[200];
        for(int i=0;i<qnnz;i++) 
            scanf("%d",&qidx[i]);
        for(int i=0;i<qnnz;i++) 
            scanf("%f",&qval[i]);
        index.query(qidx,qval,qnnz,n,k);
    }
    //清理动态内存
    delete[] indptr;
    delete[] indices;
    delete[] data;
    //记录程序结束时间点
    auto end=std::chrono::high_resolution_clock::now();
    //计算程序执行时间
    auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout<<"程序执行时间:"<<duration.count()<<" 毫秒"<<std::endl;
    return 0;
}