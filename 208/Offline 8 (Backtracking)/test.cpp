#include<bits/stdc++.h>
using namespace std;

class jtest
{
public:
    int* xyz;
    int bound;
    int level;
    int order;
    jtest(int* xyz, int bound, int level, int order)
    {
        this->xyz=xyz;
        this->bound=bound;
        this->level=level;
        this->order=order;
    }

    void printing()
    {
        cout<<*(xyz)<<" "<<this->bound<<" "<<this->level<<" "<<this->order<<endl;
    }
};

struct compare
{
public:
    bool operator()(const jtest& a, const jtest& b)
    {
        if(a.bound>b.bound)
            return true;
        else if(a.bound==b.bound && a.level<b.level)
            return true;
        else if(a.bound==b.bound && a.level==b.level && a.order<b.order)
            return true;
        else
            return false;
    }
};

int main()
{
    priority_queue<jtest, vector<jtest>, compare> pq;
    int j=1, k=2, z=4;
    for(int i=0; i<4; i++)
    {
        int* a=new int(z);
        jtest temp(a, i, j, k);
        pq.push(temp);
        j++;
        k++;
        z++;
    }

    while(!pq.empty()){
    jtest x=pq.top();
    x.printing();
    pq.pop();
    }

    return 0;
}
