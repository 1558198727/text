#include <iostream>
#include <stdio.h>
#include <queue>
#include <minHeap.h>
using namespace std;

template<class EdgeType>
class Edge
{
public:
    int start,end;//边的起始节点，终止节点
    EdgeType weight;//边的权重（应该可以定义为int）
    Edge()
    {
       start=0;
        end=0;
        weight=0;
    }
    Edge(int st,int en,int w)
    {
        start=st;
        end=en;
        weight=w;
    }
    bool operator > (Edge oneEdge)
    {
        if(weight>oneEdge.weight)
            return true;
        else
            return false;
    }
    bool operator < (Edge oneEdge)
    {
        if(weight<oneEdge.weight)
            return true;
        else
            return false;
    }
};

template<class EdgeType>
class Graph
{
    public:
    int vertexNum; //图中节点个数
    int edgeNum;   //图中边的个数
    int * Mark;    //标记某节点是否被访问
    Graph(int verNum)
    {
        this->vertexNum=verNum;
        edgeNum=0;
        Mark=new int[vertexNum];
        for(int i=0;i<vertexNum;i++)
        {
            Mark[i]=0; //都没有被访问过
        }
    }
    ~Graph()
    {
        delete [] Mark;
    }
    //virtual Edge<EdgeType> FirstEdge(int oneVertex)=0;
    //virtual Edge<EdgeType> NextEdge(Edge<EdgeType> oneEdge)=0;
    int verticesNum()
    {
        return vertexNum;
    }
    int EdgesNum()
    {
        return edgeNum;
    }
    bool isEdge(Edge<EdgeType> oneEdge)
    {
        if(oneEdge.end>=0 && oneEdge.start>=0 && oneEdge.weight>0)//判断条件还不清楚
        {
            return true;
        }
        else
        {
          return false;
        }
    }
    int startOfVertex(Edge<EdgeType> oneEdge)
    {
        return oneEdge.start;
    }
    int endOfVertex(Edge<EdgeType> oneEdge)
    {
        return oneEdge.end;
    }
    EdgeType weight(Edge<EdgeType> oneEdge) //返回oneEdge的权重
    {
        return oneEdge.weight;
    }
    //virtual void setEdge(int start,int end,int weight)=0;
    //virtual void deleteEdge(int start,int end)=0;
};

template<class EdgeType>
class AdjGraph : public Graph<EdgeType >
{
 private:
    int ** matrix;
 public:
    AdjGraph(int verNum):Graph<EdgeType>(verNum)
    {
        matrix =new int * [verNum];
        for(int i=0;i<verNum;i++)
        {
            matrix[i]=new int [verNum];
        }
        for(int i=0;i<verNum;i++)
          for(int j=0;j<verNum;j++)
        {
            matrix[i][j]=0;
        }
    }

    AdjGraph(int verNum,int **  a):Graph<EdgeType>(verNum)
    {
        matrix =new int * [verNum];
        for(int i=0;i<verNum;i++)
        {
            matrix[i]=new int [verNum];
        }
        for(int i=0;i<verNum;i++)
          for(int j=0;j<verNum;j++)
          {

            matrix[i][j]=a[i][j];
          }
    }
    void disp()
    {
        cout<<endl;
        cout<<"此图的领接矩阵为"<<endl;
        for(int i=0;i<this->vertexNum;i++)
        {
           for(int j=0;j<this->vertexNum;j++)
           {
             cout<<matrix[i][j]<<" ";
           }
            cout<<endl;
         }
    }
    ~AdjGraph()
    {
        for(int i=0;i<this->vertexNum;i++)
        {
            matrix[i]=new int [this->vertexNum];
        }
        delete [] matrix;
    }
    Edge<EdgeType> FirstEdge(int oneVer) //返回顶点的第一条边
    {
        Edge<EdgeType> tem;
        tem.start=oneVer;
        for(int i=0;i<this->vertexNum;i++)
        {
            if(matrix[oneVer][i]!=0)
            {
                tem.end=i;
                tem.weight=matrix[oneVer][i];
                return tem;
                //break;
            }
        }
        //cout<<"没有符合条件的边"<<endl;
        //return;
    }
    Edge<EdgeType> NextEdge(Edge<EdgeType> oneEdge)//返回与oneEdg有相同起点的下一条边
    {
        Edge<EdgeType> tem;
        tem.start=oneEdge.start;
        for(int i=oneEdge.end+1;i<this->vertexNum;i++)
        {
              if(matrix[oneEdge.start][i]!=0)
              {
                 tem.end=i;
                 tem.weight=matrix[oneEdge.start][i];
                 return tem;
              }
        }
        //cout<<"没有符合条件的边"<<endl;
        //return;
    }
    void visit(int i)
    {
        cout<<i+1<<" ";
    }

    //深度优先搜索
    void DFS(int i)//从i号节点开始深度优先搜索
    {
        this->Mark[i]=1;
        visit(i);
        for(Edge<EdgeType> e=FirstEdge(i);this->isEdge(e);e=NextEdge(e))
        {
             if(this->Mark[e.end]==0)
             {
               DFS(e.end);
             }
        }

    }
    void DFSGraph()//对图进行深度优先搜索
    {
        for(int i=0;i<this->vertexNum;i++)
        this->Mark[i]=0;  //标记都未访问
        for(int i=0;i<this->vertexNum;i++)
        {
            if(this->Mark[i]==0)
            {
                DFS(i);
            }
        }

    }
    //广度优先搜索
    void BFS(int i)//从i号节点开始广度优先搜索
    {
        queue<int> que;
        que.push(i);
        visit(i);
        this->Mark[i]=1;
        int p;
        while(!que.empty())
        {
            p=que.front();
            que.pop();
            this->Mark[p]=1;
            for(Edge<EdgeType> e=FirstEdge(p);this->isEdge(e);e=NextEdge(e))
            {
                if(this->Mark[e.end]==0)
                {//此处要注意，在节点入队时候就要将Mark置为已访问，否则可能会导致同一节点多次入队
                  visit(e.end);
                  this->Mark[e.end]=1;
                  que.push(e.end);
                }
            }
        }
    }

    void BFSGraph()//对图进行广度优先搜索
    {
        for(int i=0;i<this->vertexNum;i++)
        this->Mark[i]=0;  //标记都未访问
        for(int i=0;i<this->vertexNum;i++)
        {
            if(this->Mark[i]==0)
            {
                BFS(i);
            }
        }

    }

};
//Prim算法
template<class EdgeType>
Edge<EdgeType> * Prim(AdjGraph<EdgeType>& G,int s){
        int i,j;
        Edge<EdgeType> *MST;   //存储最小生成树的边
        EdgeType *nearest;     //nearest[i]表示生成树中点到i点的最小边权值
        int *neighbour;  //neighbour[i]生成树中与i点最近的点编号
        int n = G.verticesNum();

        nearest = new EdgeType[n];
        neighbour = new int[n];
        MST = new Edge<EdgeType>[n-1];
        for(i = 0; i<n; i++){
            neighbour[i] = s;
     //       cout<<neighbour[i]<<" ";////
            nearest[i] = 9999;
        }
     //   cout<<endl;//////
        for(Edge<EdgeType> e = G.FirstEdge(s); G.isEdge(e); e = G.NextEdge(e)){
            i = G.endOfVertex(e);
            nearest[i] = e.weight;
      //      cout<<nearest[i]<<" ";///
        }
      //  cout<<endl; ////

        neighbour[s] = -1;
        for(i = 0; i<n-1; i++)
        {
//            for(int k=0; k<n;k++){
//                cout<<nearest[k];
//                cout<<endl;
//            }
            EdgeType min = 9999;
            int v = -1;
            for( j = 0; j < n; j++){
                if(nearest[j] < min && neighbour[j] > -1){
                    min = nearest[j];
                    v = j;
                }
            }

            if(v >= 0){
                Edge<EdgeType> tempEdge(neighbour[v], v, nearest[v]);
                neighbour[v] = -1;
              //  cout<<v;
                MST[i] = tempEdge;
              //  cout<<MST[i].weight;
                for (Edge<EdgeType> e = G.FirstEdge(v); G.isEdge(e); e=G.NextEdge(e))
                {
                    int u = e.end;
                    if(neighbour[u] != -1 && nearest[u] > e.weight)
                    {
                        neighbour[u] = v;
                       // cout<<u;
                        nearest[u] = e.weight;
                    }
                }
            }
        }
        delete []neighbour;
        delete []nearest;
        return MST;
    }



template<class EdgeType>
Edge<EdgeType>* myPrim(AdjGraph<EdgeType>& G, int s)//从S出发生成最小生成树
{
        //minHeap<Edge<EdgeType> > H;
        int i,j;
        Edge<EdgeType>* MST;
        Edge<EdgeType> e;
        EdgeType *nearest;//nearest[i]表示生成树中的点到i点的最小边权值
        int * neighbor;   //neighbor[i]表示生成树中与i点最近的点的编号，-1表示i已经在生成树集合中
        int n=G.verticesNum();
        nearest=new EdgeType [n];
        neighbor=new int [n];
        MST=new Edge<EdgeType> [n-1];
        for(i=0;i<n;i++)
        {
            neighbor[i]=s;
            nearest[i]=9999;
        }
        for(e=G.FirstEdge(s);G.isEdge(e);e=G.NextEdge(e))
        {
            nearest[e.end]=e.weight;
        }
        neighbor[s]=-1;

        for(i=0;i<n;i++)
        {
            EdgeType min=9999;
            int v=-1;
            for(j=0;j<n;j++)
            {
                if(nearest[j]<min && neighbor[j]>-1)
                {
                    min=nearest[j];
                    v=j;
                }
            }
            if(v>=0)
            {

                Edge<EdgeType> tempEdge(neighbor[v],v,nearest[v]);
                neighbor[v]=-1;
                cout<<"v"<<v<<endl;
                MST[i]=tempEdge;
                for(e=G.FirstEdge(v);G.isEdge(e);e=G.NextEdge(e))
                {
                    int u=e.end;
                    if(neighbor[u]!=-1 && nearest[u]>e.weight)
                    {
                        neighbor[u]=v;
                        nearest[u]=e.weight;
                    }
                }
            }
        }

        delete [] neighbor;
        delete [] nearest;
        return MST;
}


int main()
{
    //课本p163页的图
    /*
    int tem[6][6]={
        {0,6,1,5,0,0},
        {6,0,5,0,3,0},
        {1,5,0,5,6,4},
        {5,0,5,0,0,2},
        {0,3,6,0,0,6},
        {0,0,4,2,6,0},
    };
    int ** a=new int *[6];
    for(int i=0;i<6;i++)
    {
        a[i]=new int [6];
    }
    for(int i=0;i<6;i++)
      for(int j=0;j<6;j++)
    {
        a[i][j]=tem[i][j];
    }

    AdjGraph<int> p(6,a);
    p.disp();
    //cout<<"深度优先搜索"<<endl;
    //p.DFSGraph();
    //cout<<endl;
    //cout<<"广度优先搜索"<<endl;
    //p.BFSGraph();
    Edge<int>*prim;
    /*
    prim=Prim(p,0);
    for(int i=0;i<p.verticesNum()-1;i++)
    {
        cout<<"start"<<" "<<prim[i].start<<endl;
        cout<<"end"<<" "<<prim[i].end<<endl;
        cout<<"weight"<<" "<<prim[i].weight<<endl;
        cout<<endl<<endl;
    }
    prim=myPrim(p,0);
    char v;
    for(int i=0;i<p.verticesNum()-1;i++)
    {
        cout<<"start"<<" "<<prim[i].start<<endl;
        cout<<"end"<<" "<<prim[i].end<<endl;
        cout<<"weight"<<" "<<prim[i].weight<<endl;
        cout<<endl<<endl;
    }
    cout<<endl;
    */
    minHeap<int> a;
    for(int i=10;i>0;i--)
    a.insert(i);
    a.insert(11);
    a.insert(12);
    a.insert(-1);
    a.insert(-5);
    a.disp();
    for(int i=0;i<12;i++)
    cout<<a.removeMin()<<endl;

    return 0;
}
