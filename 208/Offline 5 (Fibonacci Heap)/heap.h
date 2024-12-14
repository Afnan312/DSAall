#include<iostream>
#include<cstdlib>
#include<vector>
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


