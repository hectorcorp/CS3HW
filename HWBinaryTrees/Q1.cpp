#include <iostream>
#include <vector>
using namespace std;


int fastFind(vector<double> &A, double key)
{
    int L = 0;
    int R = A.size() - 1;
    while(L <= R)
    {
        int M = L + (R - L) / 2;
        if (A[M] == key)
            return M;
        else if (A[M] > key)
            R = M - 1;
        else
            L = M + 1;
    }
    return -1;
}

int main() {
    vector<double> list = {1, 4, 8, 10, 20};
    cout << fastFind(list, 5) << endl;
    return 0;
}