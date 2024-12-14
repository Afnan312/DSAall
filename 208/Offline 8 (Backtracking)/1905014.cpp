#include<bits/stdc++.h>
#include<algorithm>
#include<fstream>
using namespace std;

class branching
{
public:
    vector<vector<char>> matrix;
    int bound;
    int level;
    int order;
    int fixed_r;
    int fixed_c;

    branching(int n, vector<vector<char>>& temp, int bound, int level, int order, int fixed_r, int fixed_c)
    {
        matrix.resize(n, vector<char>(n));
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                matrix[i][j]=temp[i][j];
        }
        this->bound=bound;
        this->level=level;
        this->order=order;
        this->fixed_r=fixed_r;
        this->fixed_c=fixed_c;
    }

    vector<vector<char>> find_mat()
    {
        return this->matrix;
    }
};

int find_bound(vector<vector<char>> x, int fix_r, int fix_c, int n)
{
    vector<int> unfixed;
    vector<int> fixed;
    int cnt1, cnt2, val;
    int a=0, b=0;

    //for unfixed portion
    for(int i=fix_r; i<n; i++)//find row-wise count
    {
        cnt1=0;
        for(int j=fix_c; j<n; j++){
            if(x[i][j]=='X')
                cnt1++;
        }
        val=(cnt1+1)/2;
        unfixed.push_back(val);
    }

    for(int j=fix_c; j<n; j++)//find column-wise count
    {
        cnt1=0;
        for(int i=fix_r; i<n; i++){
            if(x[i][j]=='X')
                cnt1++;
        }
        val=(cnt1+1)/2;
        unfixed.push_back(val);
    }

    if(unfixed.size()!=0){
        vector<int>::iterator it1;
        it1=max_element(unfixed.begin(),unfixed.end());
        a=*it1;
    }


    //for fixed portion
    for(int i=0; i<fix_r; i++)//along row count
    {
        cnt1=0;
        cnt2=0;
        for(int j=i; j<fix_c; j++)//forward count
        {
            if(x[i][j]=='X')
                cnt1++;//total non-zero value in fixed part of column
        }
        for(int j=fix_c; j<n; j++)//value of fix_c is always 1 more or equal to fix_r
        {
            if(x[i][j]=='X')
                cnt2++;
        }
        if(cnt2>0 && cnt1<fix_c-i)
            fixed.push_back(fix_c-i+cnt2);
        else
            fixed.push_back(cnt1+cnt2);

        cnt1=0;
        for(int j=i-1; j>=0; j--)//backward count is always fixed
        {
            if(x[i][j]=='X')
                cnt1++;
        }
        fixed.push_back(cnt1+1);

    }

    for(int j=0; j<fix_c; j++)//along column count
    {
        cnt1=0;
        cnt2=0;
        for(int i=j; i<fix_r; i++)//down count
        {
            if(x[i][j]=='X')
                cnt1++;//total non-zero value in fixed part of row
        }

        for(int i=fix_r; i<n; i++)//value of fix_r is always one less or equal to fix_c
        {
            if(x[i][j]=='X')
                cnt2++;
        }
        if(cnt2>0 && cnt1<fix_r-j)
            fixed.push_back(fix_r-j+cnt2);
        else
            fixed.push_back(cnt1+cnt2);

        cnt1=0;
        for(int i=j-1; i>=0; i--){//up count is always in fixed portion
            if(x[i][j]=='X')
                cnt1++;
        }
        fixed.push_back(cnt1+1);
    }


    if(fixed.size()!=0){
        vector<int>::iterator it2;
        it2=max_element(fixed.begin(),fixed.end());
        b=*it2;
    }
    return max(a, b);
}

struct compare
{
public:
    bool operator()(const branching& a, const branching& b)
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
    int n;
    vector<vector<char>> matrix;
    vector<vector<char>> temp1;
    ifstream in;
    ofstream out;
    in.open("input.txt");
    in>>n;

    matrix.resize(n, vector<char>(n));
    temp1.resize(n, vector<char>(n));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            in>>matrix[i][j];
        }
    }
    in.close();

    int level=0;


    priority_queue<branching, vector<branching>, compare> pq;
    int bound=find_bound(matrix, 0, 0, n);
    branching x(n, matrix, bound, level, 0, 0, 0);
    pq.push(x);

    while(!pq.empty())
    {
        branching finding=pq.top();
        pq.pop();

        int rows=finding.fixed_r;
        int cols=finding.fixed_c;
        bool changed=false;

        vector<vector<char>> temp2=finding.find_mat();


        if(rows==n-1 && cols==n-1){
            temp1=finding.find_mat();
            break;
        }

        else if(rows==cols && !changed)
        {
            int offset=0;
            while((offset+cols)!=n){
                for(int it=0; it<n; it++)
                    temp1[it][cols]=temp2[it][cols+offset];
                for(int i=0; i<n; i++)
                {
                    int k=0;
                    for(int j=0; j<n; j++){
                        if(k==cols+offset)
                            k++;

                        if(j==cols)
                            continue;

                        temp1[i][j]=temp2[i][k];
                        k++;
                    }

                }

                bound=find_bound(temp1, rows, cols+1, n);
                branching x(n, temp1, bound, level, offset+1, rows, cols+1);
                pq.push(x);

                offset++;
            }
            changed=true;
        }

        else if(rows!=cols && !changed)
        {
            int offset=0;
            while((offset+rows)!=n){
                for(int it=0; it<n; it++)
                    temp1[rows][it]=temp2[rows+offset][it];
                for(int j=0; j<n; j++)
                {
                    int k=0;
                    for(int i=0; i<n; i++){
                        if(k==rows+offset)
                            k++;

                        if(i==rows)
                            continue;

                        temp1[i][j]=temp2[k][j];
                        k++;
                    }

                }

                bound=find_bound(temp1, rows+1, cols, n);
                branching x(n, temp1, bound, level, offset+1, rows+1, cols);
                pq.push(x);

                offset++;
            }
        }
        level++;
    }

    out.open("output.txt");
    bound=find_bound(temp1, n-1, n-1, n);
    out<<bound<<endl;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            out<<temp1[i][j];
        }
        out<<endl;
    }

    out.close();
    return 0;
}
