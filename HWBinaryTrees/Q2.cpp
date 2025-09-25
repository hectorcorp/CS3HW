#include "binaryTreeNode.h"
#include <iostream>
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


void inOrder(node* root)
{
    if (root == nullptr)
        return;

       
    inOrder(root -> left);
    cout << root -> data << " ";
    inOrder(root -> right);
}

int main()
{
    vector<double> A = {1,2,3,4,5,6,7};
    node* root = buildTree(A, 0, A.size() - 1);

    inOrder(root);
   

    return 0;
}
