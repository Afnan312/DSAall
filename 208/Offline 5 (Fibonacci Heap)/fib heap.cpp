#include<bits/stdc++.h>
#include<fstream>
#include<ctime>

using namespace std;

class Heap
{
private:
    vector<pair<int, int>> heap_arr;
    vector<int> index;
    int n;

    int parent(int i)
    {
        return i/2;
    }
    int left(int i)
    {
        return 2*i;
    }
    int right(int i)
    {
        return 2*i+1;
    }

    void min_heapify(int i, int length)
    {
        int l=left(i);
        int r=right(i);
        int smallest;
        if(l<=length && heap_arr[l].first<heap_arr[i].first)
            smallest=l;
        else
            smallest=i;
        if(r<=length && heap_arr[r].first<heap_arr[smallest].first)
            smallest=r;
        if(smallest!=i)
        {
            pair<int, int> temp1=heap_arr[i];
            heap_arr[i]=heap_arr[smallest];
            heap_arr[smallest]=temp1;
            index[heap_arr[i].second]=i;
            index[heap_arr[smallest].second]=smallest;
            min_heapify(smallest, length);
        }
    }

public:
    Heap(int nodes)
    {
        heap_arr.resize(nodes);
        index.resize(nodes);
        n=0;
    }


    void insert(pair<int, int> x)
    {
        n++;
        heap_arr[n]=x;
        index[x.second]=n;
        int pos=n;

        while(pos>1 && heap_arr[parent(pos)].first>heap_arr[pos].first)
        {
            int par=parent(pos);
            pair<int, int> temp1=heap_arr[pos];
            heap_arr[pos]=heap_arr[par];
            heap_arr[par]=temp1;
            index[heap_arr[pos].second]=pos;
            index[heap_arr[par].second]=par;
            pos=par;
        }
    }

    int size()
    {
        return n;
    }

    int getMin()
    {
        return heap_arr[1].second;
    }

    void deleteKey()
    {
        heap_arr[1]=heap_arr[n];
        n--;
        min_heapify(1, n);
    }

    void decreaseKey(pair<int, int> n_value)
    {
        int pos=index[n_value.second];
        //int pos=0;
        heap_arr[pos]=n_value;
        while(pos>1 && heap_arr[parent(pos)].first>heap_arr[pos].first)
        {
            int par=parent(pos);
            pair<int, int> temp1=heap_arr[pos];
            heap_arr[pos]=heap_arr[par];
            heap_arr[par]=temp1;
            index[heap_arr[pos].second]=pos;
            index[heap_arr[par].second]=par;
            pos=par;
        }
    }
    bool empty()
    {
        return (n==0);
    }

    ~Heap()
    {
        heap_arr.clear();
        index.clear();
    }
};

struct node {
    int dist;
    int vertex;
    int degree;
    node *parent;
    node *child;
    node *left;
    node *right;
    bool mark;
    char C;//find node flag

};

class FibonacciHeap
{
    int total;
    node* minNode;
    vector<node*> find_node;
public:
    FibonacciHeap(int nodes)
    {
        total=0;
        minNode=NULL;
        find_node.resize(nodes, NULL);
    }

    void insert(pair<int, int> x)
    {
        node* newNode=new node();
        newNode->dist=x.first;
        newNode->vertex=x.second;
        newNode->degree=0;
        newNode->parent=NULL;
        newNode->child=NULL;
        newNode->left=newNode;
        newNode->right=newNode;
        newNode->mark=false;
        newNode->C='N';
        if(minNode!=NULL){
            (minNode->left)->right=newNode;
            newNode->right=minNode;
            newNode->left=minNode->left;
            minNode->left=newNode;
            if(newNode->dist<minNode->dist)
                minNode=newNode;
        }
        else
            minNode=newNode;
        if(find_node[x.second]!=NULL)
            find_node[x.second]=NULL;
        find_node[x.second]=newNode;
        total++;
    }

    void link(node* heap1, node* heap2)
    {
        (heap2->left)->right = heap2->right;
        (heap2->right)->left = heap2->left;
        heap2->left = heap2;
        heap2->right = heap2;

        heap2->parent = heap1;
        if (heap1->child == NULL)
            heap1->child = heap2;
        ((heap1->child)->left)->right = heap2;
        heap2->right = heap1->child;
        heap2->left = (heap1->child)->left;
        (heap1->child)->left = heap2;
        if (heap2->dist < (heap1->child)->dist)
            heap1->child=heap2;
        heap1->degree++;
        heap2->mark=false;
    }

    void consolidate()
    {
        int deg;
        float f_degree=(log(total))/(log(2));
        int m_degree=f_degree;
        node* arr[m_degree+1];

        for(int i=0; i<=m_degree; i++)
            arr[i]=NULL;
        node* x=minNode;
        node* y;

        do{
            deg=x->degree;
            while(arr[deg]!=NULL)
            {
                y=arr[deg];
                if(x->dist > y->dist)
                {

                    node* temp=x;
                    x=y;
                    y=temp;
                }
                if(y==minNode)
                {
                    minNode=x;
                }

                link(x, y);//linking here
                if(x->right==x)
                    minNode=x;
                arr[deg]=NULL;
                deg++;
            }
            arr[deg]=x;
            x=x->right;

        }while(x!=minNode);

        minNode=NULL;
        for(int i=0; i<=m_degree; i++)
        {
            if(arr[i]!=NULL)
            {
                arr[i]->left=arr[i];
                arr[i]->right=arr[i];
                if(minNode==NULL)
                {
                    minNode=arr[i];
                }
                else{
                    (minNode->left)->right=arr[i];
                    arr[i]->right=minNode;
                    arr[i]->left=minNode->left;
                    minNode->left=arr[i];
                    if(arr[i]->dist < minNode->dist)
                        minNode=arr[i];
                }
            }
        }
    }

    int extractMin()
    {
        int val=minNode->vertex;
        node* z=minNode;
        node* p1;
        node* p2;
        node* x=NULL;//for children of minnode
        if(z->child!=NULL)
        {
            x=z->child;
            p2=x;
            do{
                p1=x->right;
                (minNode->left)->right=x;//add children to root
                x->right=minNode;
                x->left=minNode->left;
                minNode->left=x;
                if(x->dist < minNode->dist)
                    minNode=x;
                x->parent=NULL;
                x=p1;
            }while(p1!=p2);
        }
        (z->left)->right=z->right;//remove prev min from root
        (z->right)->left=z->left;

        if(z==z->right)
            minNode=NULL;
        else{
            minNode=z->right;
            consolidate();
        }

        total--;

        return val;
    }

    void cut(node* found, node* par)
    {
        if(found==found->right)
            par->child=NULL;
        if(found == par->child)
            par->child=found->right;
        //remove from siblings
        (found->left)->right=found->right;
        (found->right)->left=found->left;


        par->degree=par->degree-1;
        //complete remove
        found->right=found;
        found->left=found;
        //add to root list
        (minNode->left)->right=found;
        found->right=minNode;
        found->left=minNode->left;
        minNode->left=found;

        found->parent=NULL;
        found->mark=false;
    }

    void cascadeCut(node* par)
    {
        node* pntr=par->parent;
        if(pntr!=NULL)//to check if the node is in root list
        {
            if(par->mark==false)
                par->mark=true;//only one child is cut
            else{//second child is cut
                cut(par, pntr);
                cascadeCut(pntr);
            }
        }
    }

    void decreaseKey(pair<int, int> new_v)
    {
        node* toDecrease=find_node[new_v.second];
        toDecrease->dist=new_v.first;
        node* par=toDecrease->parent;
        if(par!=NULL && toDecrease->dist < par->dist)//if not in root list and violates heap properties
        {
            cut(toDecrease, par);
            cascadeCut(par);
        }
        if(toDecrease->dist<minNode->dist)
            minNode=toDecrease;
    }

    /*void find_vertex(struct node* minN, pair<int,int> new_v)
    {
        struct node* found=NULL;
        node* temp=minN;
        temp->C='Y';
        node* pntr=NULL;
        int x=new_v.second;
        if(temp->vertex == x)
        {
            pntr=temp;
            temp->C='N';
            found=pntr;
            decreaseKey(found, new_v);
        }
        if(pntr==NULL)
        {
            if(temp->child != NULL)
                find_vertex(temp->child, new_v);
            if((temp->right)->C != 'Y')
                find_vertex(temp->right, new_v);
        }
        temp->C='N';
        found=pntr;
    }*/
    node* getMin()
    {
        return minNode;
    }
    bool empty()
    {
        return (minNode==NULL);
    }
    ~FibonacciHeap()
    {
        find_node.clear();
        minNode=NULL;
    }
};

class Graph
{
    vector<vector<pair<int, int>>> adjList;

    int nodes;
public:
    Graph(int n);
    void addEdge(int first, int second, int weight);
    void dijkstra_binary_heap(int source, int dest);
    void dijkstra_fib_heap(int source, int dest);
};

Graph::Graph(int n)
{
    nodes=n;
    adjList.resize(n);
}

void Graph::addEdge(int first, int second, int weight)
{
    adjList[first].push_back(make_pair(second, weight));
    adjList[second].push_back(make_pair(first, weight));
}

void Graph::dijkstra_binary_heap(int source, int dest)
{
    clock_t bin_start_time=clock();
    Heap pq(nodes);
    int parent[nodes];
    int dist[nodes];
    int minPath[nodes];

    for(int i=0; i<nodes; i++){
        dist[i]=INT_MAX;
        parent[i]=-1;

        minPath[i]=INT_MAX;
    }

    dist[source]=0;
    minPath[source]=0;

    for(int i=0; i<nodes; i++)
    {
        pq.insert(make_pair(dist[i], i));
    }

    while(!pq.empty())
    {
        int x=pq.getMin();
        pq.deleteKey();

        for(int i=0; i<adjList[x].size();i++)
        {
            int y=adjList[x][i].first;
            int weight=adjList[x][i].second;

            if(dist[x]!=INT_MAX && dist[y]>dist[x]+weight)
            {
                dist[y]=dist[x]+weight;
                pq.decreaseKey(make_pair(dist[y], y));
                parent[y]=x;
                minPath[y]=minPath[x]+1;
            }
            else if(dist[x]!=INT_MAX && dist[x]+weight==dist[y] && minPath[x]+1<minPath[y])
            {
                parent[y]=x;
                minPath[y]=minPath[x]+1;
            }
        }
    }
    double bin_time=float(clock()-bin_start_time)/CLOCKS_PER_SEC;
    cout<<minPath[dest]<<" ";
    cout<<dist[dest]<<" ";
    cout<<fixed<<setprecision(2)<<bin_time<<" ";
}
void Graph::dijkstra_fib_heap(int source, int dest)
{
    //cout<<"here"<<endl;
    clock_t fib_start_time=clock();
    FibonacciHeap pq(nodes);

    int parent[nodes];
    int dist[nodes];
    int minPath[nodes];
    bool taken[nodes];

    for(int i=0; i<nodes; i++){
        dist[i]=INT_MAX;
        parent[i]=-1;
        minPath[i]=INT_MAX;
        taken[i]=false;
    }

    dist[source]=0;
    minPath[source]=0;
    //clock_t fib_insert_time=clock();
    //cout<<"INsert started"<<endl;
    for(int i=0; i<nodes; i++)
    {
        pq.insert(make_pair(dist[i], i));
    }
    //cout<<"Insert ended at time: "<<float(clock()-fib_insert_time)/CLOCKS_PER_SEC<<endl;
    //pq.insert(make_pair(dist[source], source));
    while(!pq.empty())
    {
        int x=pq.extractMin();
        //cout<<"extracting "<<x<<endl;
        if(taken[x]==true)
            continue;
        taken[x]=true;
        for(int i=0; i<adjList[x].size();i++)
        {
            int y=adjList[x][i].first;
            int weight=adjList[x][i].second;

            if(taken[y]==false && dist[x]!=INT_MAX &&  dist[y]>dist[x]+weight)
            {
                dist[y]=dist[x]+weight;
                //node* temp=pq.getMin();
                //cout<<"find start"<<endl;
                pq.decreaseKey(make_pair(dist[y], y));
                //pq.insert(make_pair(dist[y], y));
                //cout<<"find end"<<endl;
                parent[y]=x;
                minPath[y]=minPath[x]+1;
            }
            else if(taken[y]==false && dist[x]!=INT_MAX && dist[x]+weight==dist[y] && minPath[x]+1<minPath[y])
            {
                parent[y]=x;
                minPath[y]=minPath[x]+1;
            }
        }
    }

    double fib_time=float(clock()-fib_start_time)/CLOCKS_PER_SEC;

    //cout<<minPath[dest]<<" ";
    //cout<<dist[dest]<<" ";
    cout<<setprecision(2)<<fib_time<<endl;

}

int main()
{
    int n, e, x, y, w;
    int t, source, dest;
    ifstream in1, in2;
    in1.open("test_big_graph.txt");
    freopen("output.txt", "w", stdout);
    in1>>n;
    in1>>e;
    Graph g(n);
    for(int i=0; i<e; i++)
    {
        in1>>x;
        in1>>y;
        in1>>w;
        g.addEdge(x, y, w);
    }

    in1.close();
    in2.open("input2.txt");

    in2>>t;
    for(int i=0; i<t; i++)
    {
        in2>>source;
        in2>>dest;
        g.dijkstra_binary_heap(source, dest);
        g.dijkstra_fib_heap(source, dest);
    }


    in2.close();

    return 0;
}
