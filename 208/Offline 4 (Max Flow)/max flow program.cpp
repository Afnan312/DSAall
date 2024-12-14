#include<bits/stdc++.h>
using namespace std;

class Graph
{
    vector<vector<int>> adjMat;
    int nodes;
    int mod_bfs(vector<int>& parent, vector<vector<int>> cap);
    void dfs(vector<vector<int>> cap, vector<bool>& visited, int source);
    void printMat(vector<vector<int>> mat);
public:
    Graph(int n);
    void findAdjMat(vector<vector<int>> pLeft, vector<int> last, int n);
    pair<bool, vector<int>> edkarp(int n, int pos);
};

Graph::Graph(int n)
{
    nodes=(n*(n+1)/2)+2;
    adjMat.resize(nodes, vector<int>(nodes, 0));
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

int Graph::mod_bfs(vector<int>& parent, vector<vector<int>> cap)
{
    for(int i=0; i<nodes; i++)
        parent[i]=-1;
    queue<pair<int, int>> q;
    q.push({0, INT_MAX});

    while(!q.empty())
    {
        int node=q.front().first;
        int flow=q.front().second;
        q.pop();
        for(int i=0; i<nodes; i++)
        {
            if(parent[i]==-1 && cap[node][i]>0)
            {
                parent[i]=node;
                int n_flow=min(flow, cap[node][i]);
                if(i==nodes-1)
                    return n_flow;
                q.push({i, n_flow});
            }
        }
    }
    return 0;
}

void Graph::dfs(vector<vector<int>> cap, vector<bool>& visited, int source)
{
    visited[source]=true;
    for(int i=0; i<nodes; i++)
    {
        if(cap[source][i]>0 && !visited[i])
            dfs(cap, visited, i);
    }
}

pair<bool, vector<int>> Graph::edkarp(int n, int pos)
{
    vector<vector<int>> cap(nodes, vector<int>(nodes));

    for(int i=0; i<nodes; i++)
        for(int j=0; j<nodes; j++)
            cap[i][j]=adjMat[i][j];
    int exp_flow=0;
    for(int i=0; i<nodes; i++)
        exp_flow+=adjMat[0][i];

    int total_flow=0;
    vector<int> parent(nodes);
    int n_flow;
    int x;

    while(true)
    {
        n_flow=mod_bfs(parent, cap);
        if(n_flow==0)
            break;
        total_flow+=n_flow;
        x=nodes-1;
        while(x!=0)
        {
            int prev=parent[x];
            if(cap[prev][x]!=INT_MAX)
                cap[prev][x]-=n_flow;
            cap[x][prev]+=n_flow;
            x=prev;
        }
    }
    bool sat=(total_flow==exp_flow);
    vector<int> teams;
    if(!sat){
        int tot=0;
        vector<bool> visited(nodes, false);
        x=(n*(n-1)/2)+1;
        dfs(cap, visited, 0);

        for(int i=0; i<nodes; i++)
        {
            if(visited[i]==true){
                tot+=adjMat[0][i];
                if(i>=x){
                    if(i-x<pos)
                        teams.push_back(i-x);
                    else
                        teams.push_back(i-x+1);
                }
            }
        }
        teams.push_back(tot);
    }
    //cout<<"Total flow is "<<total_flow<<" and found is "<<exp_flow<<endl;
    return make_pair(sat, teams);
}

void Graph::findAdjMat(vector<vector<int>> pLeft, vector<int> last, int n)
{
    int x;
    x=n*(n-1)/2;
    int j=0, k=1;
    for(int i=1; i<=x; i++)
    {
        adjMat[0][i]=pLeft[j][k];
        adjMat[i][x+1+j]=INT_MAX;
        adjMat[i][x+1+k]=INT_MAX;
        k++;
        if(k==n){
            j++;
            k=j+1;
        }
    }
    int l=0;
    for(int i=nodes-n-1; i<nodes-1; i++)
    {
        adjMat[i][nodes-1]=last[l];
        l++;
    }
    //printMat(adjMat);
}

int main()
{
    int n;
    vector<string> names;
    vector<int> w, l, r;
    vector<vector<int>> g;
    cin>>n;
    names.resize(n);
    w.resize(n);
    l.resize(n);
    r.resize(n);
    g.resize(n, vector<int>(n));

    for(int i=0; i<n; i++)
    {
        cin>>names[i];
        cin>>w[i];
        cin>>l[i];
        cin>>r[i];
        for(int j=0; j<n; j++)
            cin>>g[i][j];
    }

    for(int i=0; i<n; i++)
    {
        pair<bool, vector<int>> result;
        result.first=true;
        vector<int> last(n-1);
        vector<vector<int>> pLeft(n-1, vector<int>(n-1));
        int peli=i;
        int j=0, k=0;
        for(k=0; k<n-1; k++)
        {
            if(j==peli)
                j++;
            last[k]=w[peli]+r[peli]-w[j];
            if(last[k]<0)
            {
                result.first=false;
                break;
            }
            j++;
        }
        if(!result.first)
        {
            cout<<names[peli]<<" is eliminated"<<endl;
            cout<<"They can win at most "<<w[i]<<"+"<<r[i]<<"="<<w[i]+r[i]<<" games."<<endl;
            cout<<names[j]<<" has won a total of "<<w[j]<<" games."<<endl;
            cout<<"They play each other 0 times."<<endl;
            cout<<"So on average, each of the teams in this group wins "<<w[j]<<"/1="<<w[j]<<" times"<<endl;
        }

        else
        {
            j=k=0;
            for(int l=0; l<n; l++)
            {
                if(l==peli)
                    continue;
                for(int m=0; m<n; m++)
                {
                    if(m!=peli)
                    {
                        pLeft[j][k]=g[l][m];
                        k++;
                        if(k==n-1)
                        {
                            j++;
                            k=0;
                        }
                    }

                }
            }
            Graph g(n-1);
            g.findAdjMat(pLeft, last, n-1);
            result=g.edkarp(n-1, i);
            if(!result.first)
            {
                cout<<names[peli]<<" is eliminated"<<endl;
                int total_w=0, total_r;
                total_r=result.second[result.second.size()-1];

                cout<<"They can win at most "<<w[i]<<"+"<<r[i]<<"="<<w[i]+r[i]<<" games."<<endl;
                for(int l=0; l<(result.second.size()-1); l++)
                {
                    cout<<names[result.second[l]]<<" and ";
                    total_w+=w[result.second[l]];
                }
                cout<<"\b\b\b\b    \b\b\b\b";
                cout<<"have won a total of "<<total_w<<" games."<<endl;
                cout<<"They play each other "<<total_r<<" times."<<endl;
                cout<<"So on average, each of the teams in this group wins "<<total_w+total_r<<"/"<<result.second.size()-1
                <<"="<<float(total_r+total_w)*1.0/(result.second.size()-1)<<" times"<<endl;
                cout<<endl;
            }
        }
    }

    return 0;
}
