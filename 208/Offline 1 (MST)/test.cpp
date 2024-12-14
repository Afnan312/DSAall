#include<iostream>
#include<queue>
#include<list>
#include<algorithm>
using namespace std;

bool compare(const pair<int, int> &a, pair<int, int> &b)
{
    return a.second<b.second;
}

int main()
{
    vector<pair<int, int>> adjList;
    //adjList.resize(5);
    cout<<adjList.size()<<endl;
    adjList.push_back(make_pair(2,5));
    adjList.push_back(make_pair(4,9));
    adjList.push_back(make_pair(7,3));
    adjList.push_back(make_pair(8, 33));
    adjList.push_back(make_pair(7, 8));
    cout<<adjList.size()<<endl;

    vector<pair<int, int>>::iterator i;
    i=adjList.begin()+2;
    adjList.erase(i);
    cout<<adjList.size()<<endl;

   // sort(adjList.begin(), adjList.end(), compare);
   cout<<"{";
    for(int j=0; j<adjList.size(); j++)
        cout<<j<<" "<<adjList[j].first<<" "<<adjList[j].second<<endl;
}
