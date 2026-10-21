
#include <iostream>
using namespace std;

void bubble_sort(int *niza, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int y = 0; y < n - 1 - i; y++)
        {
            if (*(niza + y) > *(niza + y + 1))
            {
                int k = *(niza + y);
                *(niza + y) = *(niza + y + 1);
                *(niza + y + 1) = k;
            }
        }
    }
}

int binary_search_r(int *niza, int start, int end, int key)
{
    if (start > end)
        return -1;

    int mid = (start + end) / 2;

    if (*(niza + mid) == key)
        return mid;

    if (*(niza + mid) > key)
        return binary_search_r(niza, start, mid - 1, key);

    return binary_search_r(niza, mid + 1, end, key);
}

int binary_search_i(int *niza, int n, int key)
{
    int start = 0, end = n - 1;

    while (start <= end)
    {
        int mid = (start + end) / 2;

        if (*(niza + mid) == key)
            return mid;

        if (*(niza + mid) > key)
            end = mid - 1;
        else
            start = mid + 1;
    }

    return -1;
}

int main()
{
    int n, key;
    cin >> n;
    int niza[n];

    int *ptr = niza;

    for (int i = 0; i < n; i++)
    {
        cin >> *(niza + i);
    }

    bubble_sort(niza, n);

    cin >> key;

    return 0;
}
