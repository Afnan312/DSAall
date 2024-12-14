#include<bits/stdc++.h>
using namespace std;

struct edge
{
    int from;
    int to;
    int weight;
};

class Graph
{
    vector<vector<pair<int, int>>> adjList;
    vector<edge> edgeList;
    int nodes;
public:
    Graph(int n);
    void addEdge(int first, int second, int weight);
    void bellFord(int source, int dest);
    void dijkstra(int source, int dest);
};

Graph::Graph(int n)
{
    nodes=n;
    adjList.resize(n);
}

void Graph::addEdge(int first, int second, int weight)
{
    adjList[first].push_back(make_pair(second, weight));
    edgeList.push_back({first, second, weight});
}

void printPath(int dist[], int parent[], int source, int dest)
{
    vector<int> path;

    if(dist[dest]==INT_MAX)
    {
        cout<<"The destination is unreachable"<<endl;
        return;
    }

    cout<<"Shortest path cost: "<<dist[dest]<<endl;
    int x=dest;
    while(x!=source)
    {
        path.push_back(x);
        x=parent[x];
    }
    path.push_back(source);
    for(int i=path.size()-1; i>=0;i--)
    {
        cout<<path[i]<<"->";
    }
    cout<<"\b\b  \b\b";
}

void Graph::dijkstra(int source, int dest)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int parent[nodes];
    bool taken[nodes];
    int dist[nodes];

    for(int i=0; i<nodes; i++){
        dist[i]=INT_MAX;
        parent[i]=-1;
        taken[i]=false;
    }

    dist[source]=0;
    pq.push(make_pair(0, source));

    while(!pq.empty())
    {
        int x=pq.top().second;
        pq.pop();

        if(taken[x]==true)
            continue;

        taken[x]=true;

        for(int i=0; i<adjList[x].size();i++)
        {
            int y=adjList[x][i].first;
            int weight=adjList[x][i].second;

            if(taken[y]==false && dist[x]!=INT_MAX && dist[x]<(INT_MAX-100000) &&  dist[y]>dist[x]+weight)
            {
                dist[y]=dist[x]+weight;
                pq.push(make_pair(dist[y], y));
                parent[y]=x;
            }
        }
    }

    printPath(dist, parent, source, dest);
}

void Graph::bellFord(int source, int dest)
{
    int parent[nodes];
    int dist[nodes];

    for(int i=0; i<nodes; i++){
        dist[i]=INT_MAX;
        parent[i]=-1;
    }
    dist[source]=0;

    for(int i=0; i<nodes-1; i++)
    {
        for(int j=0; j<edgeList.size(); j++)
        {
            int x=edgeList[j].from;
            int y=edgeList[j].to;
            int weight=edgeList[j].weight;

            if(dist[x]!=INT_MAX && dist[x]<(INT_MAX-100000) && dist[y]>dist[x]+weight)
            {
                dist[y]=dist[x]+weight;
                parent[y]=x;
            }
        }
    }
    for(int i=0; i<edgeList.size();i++)
    {
        int x=edgeList[i].from;
        int y=edgeList[i].to;
        int weight=edgeList[i].weight;

        if(dist[x]!=INT_MAX && dist[y]>dist[x]+weight)
        {
            cout<<"The graph contains a negative cycle."<<endl;
            return;
        }
    }

    cout<<"The graph does not contain a negative cycle"<<endl;
    printPath(dist, parent, source, dest);
}

int main()
{
    int n, e;
    int x, y, w;
    int s, d;
    cin>>n;
    cin>>e;
    Graph g(n);
    for(int i=0; i<e; i++)
    {
        cin>>x;
        cin>>y;
        cin>>w;
        g.addEdge(x, y, w);
    }
    cin>>s;
    cin>>d;

    g.dijkstra(s, d);
    //g.bellFord(s, d);

    return 0;
}
