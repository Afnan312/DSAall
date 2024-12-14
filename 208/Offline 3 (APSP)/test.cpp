#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> change(vector<vector<int>> v)
{
    vector<vector<int>> new_v(5, vector<int>(5));
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
            new_v[i][j]=(v[i][j])*2;
    }
    return new_v;
}

int main()
{
    vector<vector<int>> heap_arr;
    heap_arr.resize(3, vector<int>(3));
//    heap_arr.push_back(make_pair(2, 1));
//    cout<<heap_arr[0].first;
//    cout<<heap_arr[0].second;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            heap_arr[i][j]=i+j;
    }
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            cout<<heap_arr[i][j]<<" ";
        cout<<endl;
    }
}
