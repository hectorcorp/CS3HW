#include <iostream>
using namespace std;

int binarySearch(int arr[], int L, int R, int x)
{
    if (L > R)
        return -1;
    int M = L + (R - L) / 2;
    if (arr[M] == x)
        return M;
    if (arr[M] > x)
        return binarySearch(arr, L, M - 1, x);
    return binarySearch(arr, M + 1, R, x);
}

int main() {
    int array[] = {1, 4, 8, 10, 20};
    cout << binarySearch(array, 0, 4, 10) << endl;
    return 0;
}