#include <vector>
using namespace std;

class node{
    public:
    int data;
    node* left;
    node* right;

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





};