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
    //vector<vector<pair<int, int>>> adjList;
    vector<vector<int>> adjMat;
    //vector<edge> edgeList;
    vector<vector<int>> extend_sp(vector<vector<int>> l_1, vector<vector<int>> l_2);
    void printMat(vector<vector<int>> mat);
    int nodes;
public:
    Graph(int n);
    void addEdge(int first, int second, int weight);
    void floydWarsh(vector<int> path);
    void matMultiply();
};

Graph::Graph(int n)
{
    nodes=n;
    //adjList.resize(n);
    adjMat.resize(n+1, vector<int>(n+1, INT_MAX));
    for(int i=0; i<nodes+1; i++)
    {
        adjMat[i][i]=0;
    }
}

void Graph::addEdge(int first, int second, int weight)
{
    //adjList[first].push_back(make_pair(second, weight));
    //edgeList.push_back({first, second, weight});
    adjMat[first][second]=weight;
}

void Graph::printMat(vector<vector<int>> mat)
{
    cout<<"Shortest distance matrix: "<<endl;
    for(int i=0; i<mat.size(); i++)
    {
        for(int j=0; j<mat.size(); j++)
        {
            if(mat[i][j]==INT_MAX)
                cout<<"INF ";
            else
                cout<<mat[i][j]<<" ";
        }
        cout<<endl;
    }
}

void printPath(vector<vector<int>> parent, vector<int> n_path)
{
    //cout<<"here 1"<<endl;
    int source=n_path[0];
    int dest=n_path[(n_path.size()-1)];
    vector<int> path;
    if(parent[source-1][dest-1]==-1){
        cout<<"no path";
        return;
    }
    //cout<<"here 2"<<endl;
    int x=source;

    while(true)
    {
        cout<<source<<endl;
        path.push_back(source);
        source=parent[source-1][dest-1];
        if(x==source)
            break;
        else
            x=source;
    }
    path.push_back(dest);
    //reverse(path.begin(), path.end());
    if(path.size()!=n_path.size())
    {
        cout<<"No match";
        return;
    }

    for(int i=0; i<path.size(); i++)
    {
        if(path[i]!=n_path[i])
        {
            cout<<"No match";
            return;
        }
    }
    cout<<"Matched";
}

void Graph::floydWarsh(vector<int> path)
{
    vector<vector<int>> dist;
    vector<vector<int>> parent;
    parent.resize(nodes, vector<int>(nodes, -1));
    dist.resize(nodes, vector<int>(nodes));
    for(int i=0;i<nodes; i++){
        for(int j=0; j<nodes; j++){
            dist[i][j]=adjMat[i+1][j+1];
            if(adjMat[i+1][j+1]!=INT_MAX && i!=j)
                parent[i][j]=i+1;
        }
    }
    //printMat(dist);
    //printMat(parent);

    for(int k=0; k<nodes; k++){
        for(int i=0; i<nodes; i++)
        {
            for(int j=0; j<nodes; j++)
            {
                if(dist[i][k]!=INT_MAX && dist[k][j]!=INT_MAX && (dist[i][k]+dist[k][j])<dist[i][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                    parent[i][j]=k+1;
                }
            }
        }
    }
    printMat(dist);
    printPath(parent, path);
}

vector<vector<int>> Graph::extend_sp(vector<vector<int>> l_1, vector<vector<int>> l_2)
{
    vector<vector<int>> l(nodes, vector<int>(nodes));

    for(int i=0; i<nodes; i++)
    {
        for(int j=0; j<nodes; j++)
        {
            l[i][j]=INT_MAX;
            for(int k=0; k<nodes; k++)
            {
                if(l_1[i][k]!=INT_MAX && l_2[k][j]!=INT_MAX && l_1[i][k]+l_2[k][j]<l[i][j])
                    l[i][j]=l_1[i][k]+l_2[k][j];
            }
        }
    }
    return l;
}

void Graph::matMultiply()
{
    int m=1;
    vector<vector<int>> dist;
    dist.resize(nodes, vector<int>(nodes));
    for(int i=0; i<nodes; i++)
        for(int j=0; j<nodes; j++)
            dist[i][j]=adjMat[i+1][j+1];

    while(m<nodes-1)
    {
        dist=extend_sp(dist, dist);
        m*=2;
    }
    printMat(dist);
}

int main()
{
    int n, e;
    int x, y, w;
    int j, k;
    vector<int> n_path;
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
    cout<<"Enter path length:";
    cin>>j;
    for(int i=0; i<j; i++)
    {
        cin>>k;
        n_path.push_back(k);
    }

    g.floydWarsh(n_path);
    //g.matMultiply();


    return 0;
}
