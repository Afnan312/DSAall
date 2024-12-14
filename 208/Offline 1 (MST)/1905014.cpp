#include<iostream>
#include<queue>
#include<list>
#include<algorithm>
#include<climits>
#include<iomanip>
using namespace std;

class Sets
{
    int* parent;
    int* rank;
public:
    Sets(int n)
    {
        parent=new int[n];
        rank=new int[n];

        for(int i=0; i<n; i++)
        {
            parent[i]=-1;
            rank[i]=1;
        }
    }
    int find_set(int u)
    {
        if(parent[u]==-1)
            return u;
        return parent[u]=find_set(parent[u]);
    }
    void union_set(int u, int v)
    {
        u=find_set(u);
        v=find_set(v);
        if(u!=v){
            if(rank[u]<rank[v]){
                parent[u]=v;
                rank[v]+=rank[u];
            }
            else
            {
                parent[v]=u;
                rank[u]+=rank[v];
            }
        }
    }
};

struct edge
{
    int from;
    int to;
    float weight;
};

bool compare(const edge &a,const edge &b)
{
    return a.weight<b.weight;
}

void printEdges(vector<edge> edges)
{
    cout<<"{";
    for(int i=0; i<edges.size(); i++)
    {
        cout<<"("<<edges[i].from<<","<<edges[i].to<<"),";
    }
    cout<<"\b \b";
    cout<<"}"<<endl;
}

class Graph
{
    vector<vector<pair<int, float>>> adjList;
    //int edges;
    vector<edge> edgeList;
    int nodes;
public:
    Graph(int n);
    void addEdge(int first, int second, float weight);
    void kruskal();
    void prim();
};

Graph::Graph(int n)
{
    //edges=m;
    nodes=n;
    adjList.resize(n);
}

void Graph::addEdge(int first, int second, float weight)
{
    adjList[first].push_back(make_pair(second, weight));
    adjList[second].push_back(make_pair(first, weight));
    edgeList.push_back({first, second, weight});
}

void Graph::prim()
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<edge> edges;
    float cost=0;

    float key[nodes];
    int parent[nodes];
    bool taken[nodes];

    for(int i=0; i<nodes; i++){
        key[i]=INT_MAX;
        parent[i]=-1;
        taken[i]=false;
    }
    key[0]=0;
    pq.push(make_pair(0, 0));

    while(!pq.empty())
    {
        int x=pq.top().second;
        pq.pop();

        if(taken[x]==true)
            continue;

        taken[x]=true;
        cost+=key[x];

        if(parent[x]!=-1){
            //cout<<"parent[x] is "<<parent[x]<<" and x is "<<x<<" and edgesize is "<<edgeList.size()<<endl;
            edges.push_back({parent[x], x});
        }

        for(int i=0; i<adjList[x].size();i++)
        {
            int y=adjList[x][i].first;
            float weight=adjList[x][i].second;

            if(taken[y]==false && key[y]>weight)
            {
                key[y]=weight;
                pq.push(make_pair(key[y], y));
                parent[y]=x;
            }
        }
    }
    cout<<"Cost of minimum spanning tree : "<<cost<<endl;
    cout<<"List of edges selected by Prim's:";
    printEdges(edges);
}

void Graph::kruskal()
{
    vector<edge> edges;
    sort(edgeList.begin(), edgeList.end(), compare);
    Sets s(nodes);
    for(int i=0; i<edgeList.size();i++)
    {
        int x=edgeList[i].from;
        int y=edgeList[i].to;

        if(s.find_set(x)!=s.find_set(y))
        {
            s.union_set(x, y);
            edges.push_back({x, y});
        }
    }
    cout<<"List of edges selected by Kruskal's:";
    printEdges(edges);
}

int main()
{
    int n, e;
    int from, to;
    float w;
    cin>>n;
    cin>>e;
    Graph g(n);
    for(int i=0; i<e; i++)
    {
        cin>>from;
        cin>>to;
        cin>>w;
        g.addEdge(from, to, w);
    }

    g.prim();
    g.kruskal();

    return 0;
}
