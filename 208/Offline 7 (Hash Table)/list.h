#include<cstdio>

class hashNode
{
    string word;
    int order;
    node *next;
    node(const E& val, node* another=NULL)
    {
        element=val;
        next=another;
    }
    node(node* another=NULL)
    {
        next=another;
    }
};

template <typename E> class llist
{
private:
    node<E>* head;
    node<E>* tail;
    node<E>* curr;
    int total;

public:
    llist(int size)
    {
        curr=tail=head=new node<E>;
        total=0;
    }

    ~llist()
    {
        while(head!=NULL)
        {
            curr=head;
            head=head->next;
            delete curr;
        }
    }

    void append(const E& val)
    {
        node* toAdd=new node<E>(val, NULL);
        node* last=tail;
        tail=toAdd;
        if(last==NULL)
            curr->next=head->next=toAdd;
        else
            last->next=tail;
        total++;
    }

    void remove(int pos)
    {
        moveToPos(pos);
        node<E>* temp=curr->next;
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
        node<E>* temp=head;
        for(int i=0; i<total-1; i++)
        {
            pos++;
            temp=temp->next;
            if(temp->element==val)
                break;
        }
        return pos;
    }
};
