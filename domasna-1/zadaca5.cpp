#include <iostream>
using namespace std;

struct rodenden
{
    unsigned short den;
    unsigned short mesec;
    unsigned short god;
};

struct Futbaler
{
    char ime [20];
    char prezime [30];
    char klub [20];
    rodenden r;
};

void strcpy( char *mesto, char  *zbor)
{
    while( *zbor != '\0')
    {
        *mesto = *zbor;
        mesto ++;
        zbor ++;
    }

    *mesto = '\0';
}

int main()
{
    Futbaler f;
    strcpy(f.ime, "Davor");
    strcpy(f.prezime, "Jordanov");
    strcpy(f.klub, "Vardar");

    f.r.den = 30;
    f.r.mesec = 4;
    f.r.god = 2009;

    cout << f.ime << " " << f.prezime << endl;
    cout << f.r.den << "." << f.r.mesec << "."<< f.r.god << endl;
    cout << f.klub;

    return 0;
}