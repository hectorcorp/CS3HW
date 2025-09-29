#include <iostream>
using namespace std;

int binarySearch(int arr[], int L, int R, int key)
{
    //base case if right and left point intersect
    if (L > R)
        return -1;
    //find the center of the array
    int M = L + (R - L) / 2;
    //checks if point in center of left and right point is key
    if (arr[M] == key)
        return M;
    //if key is less then the middle, then changes search range to be to left side
    if (arr[M] > key)
        return binarySearch(arr, L, M - 1, key);
    //else changes range to right side
    return binarySearch(arr, M + 1, R, key);
}

int main() {
    int array[] = {1, 4, 8, 10, 20};
    cout << binarySearch(array, 0, 4, 10) << endl;
    return 0;
}