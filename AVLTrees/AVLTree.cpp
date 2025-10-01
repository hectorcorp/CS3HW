#include "AVLTree.h"
#include <algorithm>
using namespace std;

int height(node* p)
{
    if(p == nullptr)
        return 0;
    else
        return p -> height;
}

void fixHeight(node* p)
{
    p -> height = 1 + max(height(p->left), height(p->right));
}