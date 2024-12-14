#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class node{
public:
    int priority;
    node *parent;
    node *left;
    node *right;
    int color;
    int subtreeSize;
    node()
    {
        this->parent=NULL;
        this->color=2;
        this->subtreeSize=1;
    }
    node(int x)
    {
        this->priority=x;
        this->parent=NULL;
        this->color=2;
        this->subtreeSize=1;
    }
};

class redblackTree
{
    node* root;
    node* TNIL;
    void leftRotate(node* x);
    void rightRotate(node* x);
    void insertFix(node* x);
    node* searchNodeHelp(node* x,int y);
    node* successor(node* x);
    void deletionFix(node* x);
    int countNodes(node* x, int priority);
    void rbTransplant(node* x, node* y);
public:
    redblackTree()
    {
        TNIL=new node();
        TNIL->color=1;
        TNIL->left=NULL;
        TNIL->right=NULL;
        TNIL->subtreeSize=0;
        root=TNIL;
    }
    int insert(int priority);
    int searchNode(int priority);
    int deletion(int priority);
    int lesser(int priority);
};

void redblackTree::leftRotate(node* x)
{
    node* y=x->right;
    x->right=y->left;

    if(y->left!=TNIL)
        y->left->parent=x;
    y->parent=x->parent;

    if(x->parent==TNIL)
        root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->left=x;
    x->parent=y;

    x->subtreeSize=1+x->left->subtreeSize+x->right->subtreeSize;
    y->subtreeSize=1+y->left->subtreeSize+y->right->subtreeSize;
}

void redblackTree::rightRotate(node* x)
{
    node* y=x->left;
    x->left=y->right;

    if(y->right!=TNIL)
        y->right->parent=x;
    y->parent=x->parent;
    if(x->parent==TNIL)
        root=y;
    else if(x==x->parent->right)
        x->parent->right=y;
    else
        x->parent->left=y;
    y->right=x;
    x->parent=y;

    x->subtreeSize=1+x->left->subtreeSize+x->right->subtreeSize;
    y->subtreeSize=1+y->left->subtreeSize+y->right->subtreeSize;
}

void redblackTree::insertFix(node* x)
{
    node* y;//uncle node
    while(x->parent->color==2)
    {
        if(x->parent==x->parent->parent->left)//parent of x is a left child
        {
            y=x->parent->parent->right;//find uncle
            if(y->color==2)
            {
                y->color=1;
                x->parent->color=1;
                x->parent->parent->color=2;
                x=x->parent->parent;
            }
            else
            {
                if(x==x->parent->right)
                {
                    x=x->parent;
                    leftRotate(x);
                }
                x->parent->color=1;
                x->parent->parent->color=2;
                rightRotate(x->parent->parent);
            }
        }
        else
        {
            y=x->parent->parent->left;
            if(y->color==2)
            {
                y->color=1;
                x->parent->color=1;
                x->parent->parent->color=2;
                x=x->parent->parent;
            }
            else
            {
                if(x==x->parent->left)
                {
                    x=x->parent;
                    rightRotate(x);
                }
                x->parent->color=1;
                x->parent->parent->color=2;
                leftRotate(x->parent->parent);
            }
        }
        if(x==root)
            break;
    }
    root->color=1;
}

node* redblackTree::searchNodeHelp(node* x,int y)
{
    while(x!=TNIL)
    {
        if(x->priority==y)
            return x;
        else if(x->priority<y)
            x=x->right;
        else
            x=x->left;
    }
    return x;

}

int redblackTree::insert(int priority)
{
    node* findN=searchNodeHelp(root, priority);
    if(findN!=TNIL)
        return 0;

    node* newNode=new node(priority);
    newNode->left=TNIL;
    newNode->right=TNIL;
    node* x=root;
    node* y=TNIL;

    while(x!=TNIL)
    {
        y=x;
        if(newNode->priority<x->priority)
            x=x->left;
        else
            x=x->right;
    }

    newNode->parent=y;
    if(y==TNIL){
        newNode->color=1;
        root=newNode;
    }

    else if(newNode->priority<y->priority)
        y->left=newNode;
    else
        y->right=newNode;

    node* fix=newNode->parent;
    while(fix!=TNIL)
    {
        fix->subtreeSize++;
        fix=fix->parent;
    }

    insertFix(newNode);
    return 1;
}

node* redblackTree::successor(node* x)
{
    x=x->right;
    while(x->left!=TNIL)
        x=x->left;

    return x;
}

void redblackTree::rbTransplant(node* x, node* y){
    if (x->parent==TNIL)
        root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->parent=x->parent;
}

void redblackTree::deletionFix(node* x)
{
    node* y;
    while(x!=root && x->color==1)
    {
        if(x==x->parent->left)
        {
            y=x->parent->right;
            if(y->color==2)//case 1
            {
                y->color=1;
                x->parent->color=2;
                leftRotate(x->parent);
                y=x->parent->right;
            }

            if(y->left->color==1 && y->right->color==1)//case 2
            {
                y->color=2;
                x=x->parent;
            }
            else
            {
                if(y->right->color==1)//case 3
                {
                    y->left->color=1;
                    y->color=2;
                    rightRotate(y);
                    y=x->parent->right;
                }
                y->color=x->parent->color;//case 4
                x->parent->color=1;
                y->right->color=1;
                leftRotate(x->parent);
                x=root;
            }
        }
        else
        {
            y=x->parent->left;
            if(y->color==2)
            {
                y->color=1;
                x->parent->color=2;
                rightRotate(x->parent);
                y=x->parent->left;
            }

            if(y->right->color==1 && y->left->color==1)
            {
                y->color=2;
                x=x->parent;
            }
            else
            {
                if(y->left->color==1)
                {
                    y->right->color=1;
                    y->color=2;
                    leftRotate(y);
                    y=x->parent->left;
                }
                y->color=x->parent->color;
                x->parent->color=1;
                y->left->color=1;
                rightRotate(x->parent);
                x=root;
            }
        }
    }
    x->color=1;
}

int redblackTree::deletion(int priority)
{
    node* findN=searchNodeHelp(root, priority);
    if(findN==TNIL)
        return 0;

    node *x, *y;
    y = findN;
    int y_prev_color=y->color;
    if(findN->left==TNIL)
    {
        x=findN->right;
        rbTransplant(findN, findN->right);
    }
    else if (findN->right==TNIL)
    {
        x=findN->left;
        rbTransplant(findN, findN->left);
    }
    else
    {
        y=successor(findN);
        y_prev_color = y->color;
        x=y->right;
        if (y->parent==findN)
            x->parent=y;

        else
        {
            node* fix2=y->parent;
            while(fix2!=findN){
                fix2->subtreeSize--;
                fix2=fix2->parent;
            }
            rbTransplant(y, y->right);
            y->right=findN->right;
            y->right->parent=y;
        }

        rbTransplant(findN, y);
        y->left=findN->left;
        y->left->parent=y;
        y->color=findN->color;
        y->subtreeSize=findN->subtreeSize-1;
    }
    node* fix=y->parent;
    while(fix!=TNIL)
    {
        fix->subtreeSize--;
        fix=fix->parent;
    }
    if (y_prev_color==1){
        deletionFix(x);
    }

    return 1;
}

int redblackTree::countNodes(node* x, int priority)
{
    if(x==TNIL)
        return 0;

    if(x->priority < priority)
        return (1 + x->left->subtreeSize + countNodes(x->right, priority));

    else if(x->priority==priority)
        return x->left->subtreeSize;

    else
        return countNodes(x->left, priority);
}

int redblackTree::searchNode(int priority)
{
    node* x;
    x=searchNodeHelp(root, priority);
    if(x==TNIL)
        return 0;
    return 1;
}

int redblackTree::lesser(int priority)
{
    int total=0;
    total=countNodes(root, priority);
    return total;
}

int main()
{
    int t, op, val;
    redblackTree rbt;
    ifstream in;
    in.open("input.txt");
    in>>t;
    cout<<t<<endl;
    for(int i=0; i<t; i++)
    {
        in>>op;
        in>>val;
        if(op==0)
            cout<<op<<" "<<val<<" "<<rbt.deletion(val)<<endl;

        else if(op==1)
            cout<<op<<" "<<val<<" "<<rbt.insert(val)<<endl;

        else if(op==2)
            cout<<op<<" "<<val<<" "<<rbt.searchNode(val)<<endl;
        else if(op==3)
            cout<<op<<" "<<val<<" "<<rbt.lesser(val)<<endl;
        else
            cout<<"Wrong operation"<<endl;
    }

    in.close();
    return 0;
}
