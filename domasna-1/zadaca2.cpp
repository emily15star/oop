#include <iostream>
using namespace std;

int main()
{
    int var = 55;
    
    int *ptr = &var;
    int &refvar = var;
    cout << *ptr << " " << refvar << endl;
    
    *ptr = 7;
    cout << *ptr << " " << refvar << endl;
    
    refvar = 33;
    cout << *ptr << " " << refvar << endl;

     


    return 0;
}
