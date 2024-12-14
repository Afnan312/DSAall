#include<bits/stdc++.h>
#include<time.h>

using namespace std;

class hashElement
{
    string word;
    int order;
public:
    hashElement()
    {
        word="";
    }
    hashElement(string val1, int val2)
    {
        word=val1;
        order=val2;
    }
    string getWord()
    {
        return this->word;
    }
};

class hashNode
{
    public:
    hashElement element;
    hashNode *next;
    hashNode(hashElement val, hashNode* another=nullptr)
    {
        element=val;
        next=another;
    }
    hashNode(hashNode* another=nullptr)
    {
        next=another;
    }
};

class hashLList
{
public:
    hashNode* head;
    hashNode* tail;
    hashNode* curr;
    int total;


    hashLList()
    {
        curr=tail=head=new hashNode();
        total=0;
    }

    ~hashLList()
    {
        while(head!=nullptr)
        {
            curr=head;
            head=head->next;
            delete curr;
        }
    }

    void append(hashElement val)
    {
        hashNode* toAdd=new hashNode(val, nullptr);
        hashNode* last=tail;
        tail=toAdd;
        if(last==nullptr)
            curr->next=head->next=toAdd;
        else
            last->next=tail;
        total++;
    }

    void remove(int pos)
    {
        moveToPos(pos);
        hashNode* temp=curr->next;
        if(tail==curr->next)
            tail=curr;
        curr->next=curr->next->next;
        delete temp;
        total--;
    }

    int length() const
    {
        return total;
    }

    void moveToStart()
    {
        curr=head;
    }

    void moveToPos(int pos)
    {
        if(pos==-1)
            return;
        curr=head;
        for(int i=0; i<pos;i++)
            curr=curr->next;
    }

    int search(string val)
    {
        int pos=-1;
        hashNode* temp=head;
        for(int i=0; temp->next!=nullptr; i++)
        {
            temp=temp->next;
            hashElement check=temp->element;
            if(check.getWord()==val){
                pos=i;
                break;
            }
        }
        return pos;
    }
};

int prime(int n)
{
    int prime;
    bool isPrime[n+1];
    for(int i=0; i<=n; i++)
        isPrime[i]=true;
    for(int i=2; i*i<=n; i++)
    {
        if(isPrime[i])
        {
            for(int j=i*i; j<=n; j+=i)
                isPrime[j]=false;
        }
    }
    prime=n-1;
    while(isPrime[prime])
        prime--;
    return prime;
}

class hashTable
{
    hashLList** tableSC;
    hashElement** tableOA;
    hashElement* del;
    int maxSize;
    int size;
    int type;
    int primeN;//prime number less than given size

    unsigned long hashFunction1(string word)
    {
        unsigned long h=0;
        for(int i=0; i<word.length(); i++)
        {
            h=(h<<5)|(h>>27);
            h+=(int)word[i];
        }
        return h;
    }

    int hashFunction2(int index)
    {
        return primeN-(index%primeN);//always less than maxsize
    }

public:
    hashTable(int n, int type)
    {
        this->type=type;
        if(type==1){
            tableSC=new hashLList*[n];
            for(int i=0; i<n; i++)
                tableSC[i]=nullptr;
        }
        else if(type==2){
            tableOA=new hashElement*[n];
            for(int i=0; i<n; i++)
                tableOA[i]=nullptr;
        }
        size=0;
        maxSize=n;
        this->primeN=prime(n);
        del=new hashElement();
    }

    void insertSC(string word)
    {
        unsigned long h;
        int index;
        h=hashFunction1(word);
        index=h%maxSize;

        hashLList* temp;
        if(tableSC[index]==nullptr)
            temp=new hashLList();
        else
            temp=tableSC[index];
        size++;
        hashElement toInsert(word, size);
        temp->append(toInsert);
        tableSC[index]=temp;
    }

    void deleteSC(string word)
    {
        unsigned long h;
        int index;
        h=hashFunction1(word);
        index=h%maxSize;

        if(tableSC[index]==nullptr)
            return;
        hashLList* temp=tableSC[index];
        int pos=temp->search(word);
        temp->remove(pos);
        tableSC[index]=temp;
    }

    void searchSC(string word)
    {
        unsigned long h;
        int index;
        h=hashFunction1(word);
        index=h%maxSize;

        if(tableSC[index]==nullptr)
            return;
        hashLList* temp=tableSC[index];
        int x=temp->search(word);

    }

    int searchLP(string word)
    {
        unsigned long h;
        int index, probe=0;
        h=hashFunction1(word);
        index=h%maxSize;

        int pos=index;
        do
        {
            if(tableOA[index]==nullptr)
                break;
            else if(tableOA[index]->getWord()==word){
                return probe;
            }
            probe++;
            index=(index+1)%maxSize;
        }while(index!=pos);
        return probe;
    }

    void insertLP(string word)
    {
        unsigned long h;
        int index;
        h=hashFunction1(word);
        index=h%maxSize;
        //cout<<word<<" "<<index<<endl;

        if(tableOA[index]!=nullptr)
        {
            for(int i=0; i<maxSize; i++){
                index=(index+1)%maxSize;
                if(tableOA[index]==nullptr || tableOA[index]->getWord().empty())
                    break;
            }
        }

        size++;
        hashElement* toInsert=new hashElement(word, size);
        tableOA[index]=toInsert;
    }

    void deleteLP(string word)
    {
        unsigned long h;
        int index;
        h=hashFunction1(word);
        index=h%maxSize;

        int pos=index;
        bool found=false;
        do
        {
            if(tableOA[index]==nullptr){
                break;
            }
            else if(tableOA[index]->getWord()==word){
                found=true;
                break;
            }
            index=(index+1)%maxSize;
        }while(index!=pos);

        if(!found)
            return;
        tableOA[index]=del;
        size--;
    }

    void insertQP(string word)
    {
        unsigned long h, h1;
        int index, probe=0, c1=104729, c2=89989;
        h1=h=hashFunction1(word);
        index=h%maxSize;
        //cout<<word<<" "<<index<<endl;

        if(tableOA[index]!=nullptr)
        {
            for(int i=0; i<maxSize; i++){
                probe++;
                h=h1+c1*probe+c2*probe*probe;
                index=h%maxSize;
                if(tableOA[index]==nullptr || tableOA[index]->getWord().empty())
                    break;
            }
        }

        size++;
        hashElement* toInsert=new hashElement(word, size);
        tableOA[index]=toInsert;
    }

    void deleteQP(string word)
    {
        unsigned long h, h1;
        int index, probe=0, c1=191747, c2=89989;
        h1=h=hashFunction1(word);
        index=h%maxSize;

        int pos=index;
        bool found=false;
        do
        {
            if(tableOA[index]==nullptr){
                break;
            }
            else if(tableOA[index]->getWord()==word){
                found=true;
                break;
            }
            probe++;
            h=h1+c1*probe+c2*probe*probe;
            index=h%maxSize;
        }while(index!=pos);

        if(!found)
            return;
        tableOA[index]=del;
        size--;
    }

    int searchQP(string word)
    {
        unsigned long h, h1;
        int index, probe=0, c1=191747, c2=89989;
        h1=h=hashFunction1(word);
        index=h%maxSize;

        int pos=index;
        do
        {
            if(tableOA[index]==nullptr)
                break;
            else if(tableOA[index]->getWord()==word){
                return probe;
            }
            probe++;
            h=h+c1*probe+c2*probe*probe;
            index=h%maxSize;
        }while(index!=pos);
        return probe;
    }

    void insertDH(string word)
    {
        unsigned long h1, h;
        int index, probe=0, h2;
        h1=h=hashFunction1(word);
        index=h%maxSize;
        //cout<<word<<" "<<index<<endl;

        if(tableOA[index]!=nullptr)
        {
            for(int i=0; i<maxSize; i++){
                probe++;
                h2=hashFunction2(index);
                h=h1+probe*h2;
                index=h%maxSize;
                if(tableOA[index]==nullptr || tableOA[index]->getWord().empty())
                    break;
            }
        }

        size++;
        hashElement* toInsert=new hashElement(word, size);
        tableOA[index]=toInsert;
    }

    void deleteDH(string word)
    {
        unsigned long h, h1;
        int index, probe=0, h2;
        h1=h=hashFunction1(word);
        index=h%maxSize;

        int pos=index;
        bool found=false;
        do
        {
            if(tableOA[index]==nullptr){
                break;
            }
            else if(tableOA[index]->getWord()==word){
                found=true;
                break;
            }
            probe++;
            h2=hashFunction2(index);
            h=h1+probe*h2;
            index=h%maxSize;
        }while(index!=pos);

        if(!found)
            return;
        tableOA[index]=del;
        size--;
    }

    int searchDH(string word)
    {
        unsigned long h, h1;
        int index, probe=0, h2;
        h1=h=hashFunction1(word);
        index=h%maxSize;

        int pos=index;
        do
        {
            if(tableOA[index]==nullptr)
                break;
            else if(tableOA[index]->getWord()==word){
                return probe;
            }
            probe++;
            h2=hashFunction2(index);
            h=h1+probe*h2;
            index=h%maxSize;
        }while(index!=pos);
        return probe;
    }

    void showhash(){
        for(int i=0; i<maxSize; i++)
        {
            cout<<i<<" ";
            hashElement* temp=tableOA[i];
            if(temp==nullptr){
                cout<<endl;
                continue;
            }
            cout<<temp->getWord()<<"  n"<<endl;

        }
    }

    void clear()
    {
        if(type==1)
        {
            for(int i=0; i<maxSize; i++){
                if(tableSC!=nullptr){
                    hashLList* temp=tableSC[i];
                    delete temp;
                    tableSC[i]=nullptr;
                }
            }
        }
        else if(type==2)
        {
            for(int i=0; i<maxSize; i++){
//                if(tableOA!=nullptr){
//                    hashElement* temp=tableOA[i];
//                    delete temp;
//                    tableOA[i]=nullptr;
//                }
                tableOA[i]=nullptr;
            }
        }
    }
};



int main()
{
    char alphabets[26]={'a', 'b','c','d','e','f','g','h',
                    'i','j','k','l','m','n','o','p','q',
                    'r','s','t','u','v','w','x','y','z'};

    int n;
    cin>>n;

    vector<string> arr(n);
    srand(time(NULL));
    for(int j=0; j<n; j++){
        string random;
        bool dup=false;
        for(int i=0; i<7; i++)
        {
            int temp=rand()%26;
            random.push_back(alphabets[temp]);

        }
        for(int k=0; k<j; k++)
        {
            if(arr[k]==random)
            {
                j--;
                dup=true;
                break;
            }
        }
        if(!dup)
            arr[j]=random;
    }

    hashTable sc(n, 1);
    hashTable lp(n, 2);
    hashTable qp(n, 2);
    hashTable dh(n, 2);

    vector<float> searchSC1(6), searchSC2(6), searchLP1(6), searchLP2(6), searchQP1(6), searchQP2(6), searchDH1(6), searchDH2(6);
    vector<float> probeLP1(6), probeLP2(6), probeQP1(6), probeQP2(6), probeDH1(6), probeDH2(6);

    float load=0.4;
    int index=0;

    while(index<=5)
    {
        int m=load*n;

        int* nums=new int[m];//for random search and deletion
        for(int i=0; i<m; i++)
            nums[i]=i;

        for(int i=0; i<m; i++)
        {
            sc.insertSC(arr[i]);
            lp.insertLP(arr[i]);
            qp.insertQP(arr[i]);
            dh.insertDH(arr[i]);
        }
        int r=m*0.1;//choosing 10%

        //separate chaining
        //search random 10%
        random_shuffle(nums, nums+m);
        clock_t scSearchStart=clock();
        for(int i=0; i<r; i++)
        {
            sc.searchSC(arr[nums[i]]);
        }
        double scSearch1=float(clock()-scSearchStart)/CLOCKS_PER_SEC;
        searchSC1[index]=scSearch1*1.0/r;
        //cout<<searchSC1[index]<<endl;

        //delete random 10%
        random_shuffle(nums, nums+m);
        for(int i=0; i<r; i++)
        {
            sc.deleteSC(arr[nums[i]]);
        }

        //search p/2 deleted and p/2 other elements
        //create array of p/2 deleted elements
        vector<string> arr2(r);
        for(int i=0; i<r/2; i++)
            arr2[i]=arr[nums[i]];
        int last=0;
        for(int i=r/2; i<r; i++)
        {
            bool exist;
            string chose;
            for(int j=last; j<m; j++)
            {
                exist=false;
                for(int k=0; k<r; k++)
                {
                    if(arr[j]==arr[nums[k]]){
                        exist=true;
                        break;
                    }
                }
                if(exist){
                    continue;
                }
                else
                {
                    last=j+1;
                    chose=arr[j];
                    break;
                }
            }
            arr2[i]=chose;
        }

        //search from arr2
        clock_t scSearchStart2=clock();
        for(int i=0; i<r; i++)
        {
            sc.searchSC(arr2[i]);
        }
        double scSearch2=float(clock()-scSearchStart2)/CLOCKS_PER_SEC;
        searchSC2[index]=scSearch2*1.0/r;

        //linear probing
        //search random 10%
        random_shuffle(nums, nums+m);

        int x1=0, x2=0;
        clock_t lpSearchStart=clock();
        for(int i=0; i<r; i++)
        {
            x1+=lp.searchLP(arr[nums[i]]);
        }
        double lpSearch1=float(clock()-lpSearchStart)/CLOCKS_PER_SEC;
        searchLP1[index]=lpSearch1*1.0*1000000000000/r;
        probeLP1[index]=x1*1.0/r;

        //delete random 10%
        random_shuffle(nums, nums+m);
        for(int i=0; i<r; i++)
        {
            lp.deleteLP(arr[nums[i]]);
        }

        //search p/2 deleted and p/2 other elements
        //create array of p/2 deleted elements

        for(int i=0; i<r/2; i++)
            arr2[i]=arr[nums[i]];
        last=0;
        for(int i=r/2; i<r; i++)
        {
            bool exist;
            string chose;
            for(int j=last; j<m; j++)
            {
                exist=false;
                for(int k=0; k<r; k++)
                {
                    if(arr[j]==arr[nums[k]]){
                        exist=true;
                        break;
                    }
                }
                if(exist){
                    continue;
                }
                else
                {
                    last=j+1;
                    chose=arr[j];
                    break;
                }
            }
            arr2[i]=chose;
        }


        //search from arr2
        clock_t lpSearchStart2=clock();
        for(int i=0; i<r; i++)
        {
            x2+=lp.searchLP(arr2[i]);
        }
        double lpSearch2=float(clock()-lpSearchStart2)/CLOCKS_PER_SEC;
        searchLP2[index]=lpSearch2*1.0*1000000000000/r;
        probeLP2[index]=x2*1.0/r;

        //quadratic probing
        //search random 10%
        x1=x2=0;
        random_shuffle(nums, nums+m);
        clock_t qpSearchStart=clock();
        for(int i=0; i<r; i++)
        {
            x1+=qp.searchQP(arr[nums[i]]);
        }
        double qpSearch1=float(clock()-qpSearchStart)/CLOCKS_PER_SEC;
        searchQP1[index]=qpSearch1*1.0*1000000000000/r;
        probeQP1[index]=x1*1.0/r;

        //delete random 10%
        random_shuffle(nums, nums+m);
        for(int i=0; i<r; i++)
        {
            qp.deleteQP(arr[nums[i]]);
        }

        //search p/2 deleted and p/2 other elements
        //create array of p/2 deleted elements

        for(int i=0; i<r/2; i++)
            arr2[i]=arr[nums[i]];
        last=0;
        for(int i=r/2; i<r; i++)
        {
            bool exist;
            string chose;
            for(int j=last; j<m; j++)
            {
                exist=false;
                for(int k=0; k<r; k++)
                {
                    if(arr[j]==arr[nums[k]]){
                        exist=true;
                        break;
                    }
                }
                if(exist){
                    continue;
                }
                else
                {
                    last=j+1;
                    chose=arr[j];
                    break;
                }
            }
            arr2[i]=chose;
        }

        //search from arr2
        clock_t qpSearchStart2=clock();
        for(int i=0; i<r; i++)
        {
            x2+=qp.searchQP(arr2[i]);
        }
        double qpSearch2=float(clock()-qpSearchStart2)/CLOCKS_PER_SEC;
        searchQP2[index]=qpSearch2*1.0*1000000000000/r;
        probeQP2[index]=x2*1.0/r;

        //double hashing
        //search random 10%
        x1=x2=0;
        random_shuffle(nums, nums+m);
        clock_t dhSearchStart=clock();
        for(int i=0; i<r; i++)
        {
            x1+=dh.searchDH(arr[nums[i]]);
        }
        double dhSearch1=float(clock()-dhSearchStart)/CLOCKS_PER_SEC;
        searchDH1[index]=dhSearch1*1.0*1000000000000/r;
        probeDH1[index]=x1*1.0/r;

        //delete random 10%
        random_shuffle(nums, nums+m);
        for(int i=0; i<r; i++)
        {
            dh.deleteDH(arr[nums[i]]);
        }

        //search p/2 deleted and p/2 other elements
        //create array of p/2 deleted elements

        for(int i=0; i<r/2; i++)
            arr2[i]=arr[nums[i]];
        last=0;
        for(int i=r/2; i<r; i++)
        {
            bool exist;
            string chose;
            for(int j=last; j<m; j++)
            {
                exist=false;
                for(int k=0; k<r; k++)
                {
                    if(arr[j]==arr[nums[k]]){
                        exist=true;
                        break;
                    }
                }
                if(exist){
                    continue;
                }
                else
                {
                    last=j+1;
                    chose=arr[j];
                    break;
                }
            }
            arr2[i]=chose;
        }

        //search from arr2
        clock_t dhSearchStart2=clock();
        for(int i=0; i<r; i++)
        {
            x2+=dh.searchDH(arr2[i]);
        }
        double dhSearch2=float(clock()-dhSearchStart2)/CLOCKS_PER_SEC;
        searchDH2[index]=dhSearch2*1.0*1000000000000/r;
        probeDH2[index]=x2*1.0/r;

        load+=0.1;
        index++;
        //lp.showhash();
        sc.clear();
        lp.clear();
        qp.clear();
        dh.clear();
    }

    cout<<"Table 1 (separate chaining)"<<endl;
    cout<<"           "<<"  Before deletion"<<"  "<<"After deletion"<<endl;
    cout<<"load factor"<<"  "<<"Avg search time "<<"Avg search time"<<endl;
    float l=0.4;
    for(int i=0; i<6; i++)
    {
        cout<<l<<"        "<<setprecision(4)<<searchSC1[i]<<"  "<<searchSC2[i]<<endl;
        l+=0.1;
    }
    cout<<endl;

    cout<<"Table 2 (linear probing)"<<endl;
    cout<<"           "<<"  Before deletion"<<"                    "<<"After deletion"<<endl;
    cout<<"load factor"<<"  "<<"Avg search time "<<"Avg probes "<<"Avg search time "<<"Avg probes "<<endl;
    l=0.4;
    for(int i=0; i<6; i++)
    {
        cout<<l<<"        "<<setprecision(4)<<searchLP1[i]<<"  "<<probeLP1[i]<<"  "<<searchLP2[i]<<"  "<<probeLP2[i]<<endl;
        l+=0.1;
    }
    cout<<endl;

    cout<<"Table 3 (quadratic probing)"<<endl;
    cout<<"           "<<"  Before deletion"<<"                    "<<"After deletion"<<endl;
    cout<<"load factor"<<"  "<<"Avg search time "<<"Avg probes "<<"Avg search time "<<"Avg probes "<<endl;
    l=0.4;
    for(int i=0; i<6; i++)
    {
        cout<<l<<"        "<<setprecision(4)<<searchQP1[i]<<"  "<<probeQP1[i]<<"  "<<searchQP2[i]<<"  "<<probeQP2[i]<<endl;
        l+=0.1;
    }
    cout<<endl;

    cout<<"Table 4 (double hashing)"<<endl;
    cout<<"           "<<"  Before deletion"<<"                    "<<"After deletion"<<endl;
    cout<<"load factor"<<"  "<<"Avg search time "<<"Avg probes "<<"Avg search time "<<"Avg probes "<<endl;
    l=0.4;
    for(int i=0; i<6; i++)
    {
        cout<<l<<"        "<<setprecision(4)<<searchDH1[i]<<"  "<<probeDH1[i]<<"  "<<searchDH2[i]<<"  "<<probeDH2[i]<<endl;
        l+=0.1;
    }
    cout<<endl;

    int start=5;
    while(start<=10)
    {
        cout<<"Table for load factor 0."<<start-1<<endl;
        cout<<"                      Before deletion                        After deletion"<<endl;
        cout<<"Method            Avg search time  Avg probes  Avg search time  Avg probes"<<endl;
        cout<<"Separate Chaining       "<<searchSC1[start-5]<<"        "<<"N/A"<<"     "<<searchSC2[start-5]<<"      N/A"<<endl;
        cout<<"Linear Probing          "<<searchLP1[start-5]<<"        "<<probeLP1[start-5]<<"     "<<searchLP2[start-5]<<"      "<<probeLP2[start-5]<<endl;
        cout<<"Quadratic probing       "<<searchQP1[start-5]<<"        "<<probeQP1[start-5]<<"     "<<searchQP2[start-5]<<"      "<<probeQP2[start-5]<<endl;
        cout<<"Double Hashing          "<<searchDH1[start-5]<<"        "<<probeDH1[start-5]<<"     "<<searchDH2[start-5]<<"      "<<probeDH2[start-5]<<endl;
        cout<<endl;

        start++;
    }

    return 0;
}
