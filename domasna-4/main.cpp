#include <iostream>
#include <cmath>
using namespace std;


class CPX {
public:
    float re, im;

    CPX(float re = .0f, float im = .0f): re(re), im(im) {}

    ~CPX() {}

    CPX(const CPX &orig): re(orig.re), im(orig.im) {}

    CPX operator+(CPX r) {
        CPX rez(*this);
        rez.re += r.re;
        rez.im += r.im;
        return rez;
    }

    CPX operator*(CPX r) {
        CPX rez;
        rez.re = this->re * r.re - this->im * r.im;
        rez.im = this->re * r.im + this->im * r.re;
        return rez;
    }

    CPX operator/(CPX r) {
        CPX rez;
        float imenitel = r.re * r.re + r.im * r.im;

        rez.re = (this->re * r.re + this->im * r.im) / imenitel;
        rez.im = (this->im * r.re - this->re * r.im) / imenitel;

        return rez;
    }

    float operator~() {
        return sqrt(this->re * this->re + this->im * this->im);
    }

    void print() {
        cout << this->re
             << ((this->im >= 0) ? "+" : "")
             << this->im << "i\n";
    }
};

int main() {
    float a, b, c, d;

    cout << "prviot kompleksen broj (re im): ";
    cin >> a >> b;

    cout << "vtoriot kompleksen broj (re im): ";
    cin >> c >> d;

    CPX z1(a, b);
    CPX z2(c, d);

    cout << endl;

    cout << "Zbir: ";
    (z1 + z2).print();

    cout << "Proizvod: ";
    (z1 * z2).print();

    if (c != 0 || d != 0) {
        cout << "Kolicnik: ";
        (z1 / z2).print();
    } else {
        cout << "Delenje so nula ne e dozvoleno\n";
    }

    cout << "Modul na prviot broj: " << ~z1 << endl;
    cout << "Modul na vtoriot broj: " << ~z2 << endl;

    return 0;
}