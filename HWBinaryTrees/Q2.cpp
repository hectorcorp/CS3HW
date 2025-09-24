#include "Q2.h"
#include <iostream>
using namespace std;


void levelOrder(node* root)
{
    if (root == nullptr)
        return;

    cout << root -> data << " ";   
    levelOrder(root -> left);
    levelOrder(root -> right);
}

int main()
{
    vector<double> A = {1,2,3,4,5,6,7};
    node n;
    node* root = n.buildTree(A, 0, A.size() - 1);
    node* temp = root;

    levelOrder(temp);
   
    

    return 0;
}
