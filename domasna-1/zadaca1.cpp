#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int niza[n];
    
    int *nptr = NULL;
    nptr = niza;
    
    for (int i=0; i<n; i++)
    {
        cin >> niza[i];
    }
    
    for(int i=0; i<n; i++)
    {
        cout << *nptr << endl;
        nptr++;
    }

    return 0;
}
