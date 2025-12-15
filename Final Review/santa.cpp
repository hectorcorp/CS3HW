#include <vector>
#include <iostream>
#include <iomanip>

using namespace std; 


bool helpSanta(vector<int>& w, int k)
{
    vector<bool> a(k + 1, false);
    a[0] = true;
    for(int wi: w)
        for(int j = k; j >= wi; j--)
            a[j] = a[j] || a[j - wi];

    for(int i = 0; i < k+1; i++)
    {
        cout << a[i] << " ";
    }
    return a[k];
}






int main()
{






    vector<int> weights {3,1};
    cout << helpSanta(weights, 17);

    return 0;
}