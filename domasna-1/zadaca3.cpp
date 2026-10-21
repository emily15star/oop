
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int niza[n];
    int k;

    for (int i = 0; i < n; i++)
    {
        cin >> *(niza + i);
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int y = 0; y < n - 1 - i; y++)
        {
            if (*(niza + y) > *(niza + y + 1))
            {
                k = *(niza + y);
                *(niza + y) = *(niza + y + 1);
                *(niza + y + 1) = k;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << *(niza + i) << endl;
    }

    return 0;
}
