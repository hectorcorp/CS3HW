#include <iostream>
#include <queue>
#include "Q2.h"
using namespace std;


void levelOrderTraversal(node * r)
{
    queue<node*> nodeQue;
    nodeQue.push(r);
    while(!nodeQue.empty())
    {
        r = nodeQue.front();
        cout << r->data << " ";
        nodeQue.pop();
        if(r->left != nullptr)
            nodeQue.push(r->left);
        if(r->right != nullptr)
            nodeQue.push(r->right);
    }
}

void levelOrderRecursiveTraversal(node* r,queue<node*>& q) 
{
    if(q.empty())
        return;
    cout << r->data << " ";
    q.pop();
    if(r->left != nullptr)
        q.push(r->left);
    if(r->right != nullptr)
        q.push(r->right);
    levelOrderRecursiveTraversal(q.front(), q);
}


int main()
{
    vector<double> A = {1, 2, 3, 4, 5, 6, 7};
    node n;
    node* root = n.buildTree(A, 0, A.size() - 1);
    node* temp = root;

    //levelOrderTraversal(temp);
    queue<node*> que;
    que.push(temp);
    levelOrderRecursiveTraversal(que.front(), que);

    return 0;
}