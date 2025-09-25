#include <iostream>
#include <queue>
#include "binaryTreeNode.h"
using namespace std;


node* buildTree(vector<double> & A, int start, int end)
{
    if (end < start)
        return nullptr;
    int mid = (start + end) / 2;
    node * no = new node;
    no -> data = A[mid];
    no -> left = buildTree(A, start, mid - 1);
    no -> right = buildTree(A, mid + 1, end);
    return no;
}


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
    node* root = buildTree(A, 0, A.size() - 1);
    queue<node*> que;
    que.push(root);

    //levelOrderTraversal(root);
    levelOrderRecursiveTraversal(que.front(), que);

    return 0;
}