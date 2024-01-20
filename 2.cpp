#include <iostream>
#include <sstream>

using namespace std;

class Rational
{
private:
    int b;
public:
    int a;
    Rational(int = 0, int = 1);
    void Set_b(int);
    int Get_b() const;
    void print();
    void Simplify();
    double to_double() const;
    string to_string();
    static bool Is_Equal(Rational, Rational);
    static Rational Sum(Rational, Rational);
    static Rational Sub(Rational, Rational);
    static Rational Mult(Rational, Rational);
    static Rational Divi(Rational, Rational);
};
// to double
double Rational::to_double() const
{
    return (((double)a) / b);
}
// tabe ast na metod
int gcd(int a, int b)
{
    if (0 == b)
        return a;
    return gcd(b, a % b);
}
// sade sazi
void Rational::Simplify()
{
    int g = gcd(this->a, this->b);
    a /= g;
    b /= g;
    if (0 == a)
        b = 1;
    else if (b < 0)
    {
        a = -a;
        b = -b;
    }
}
// Generator
Rational::Rational(int a, int b)
{
    this->a = a; // public
    Set_b(b);    // private
}
// Print
void Rational::print()
{
    cout << to_string();
}
// to_string
string Rational::to_string()
{
    Simplify();
    ostringstream oss;
    if (0 == a)
        oss << 0;
    else if (0 == b)
        oss << a;
    else
        oss << a << "/" << b;
    return oss.str();
}
// set kardan b
void Rational::Set_b(int b)
{
    if (0 == b){
        cout << "invalid for b";
        exit(-1);
    }
    else
        this->b = b;
}
// gereftan b
int Rational::Get_b() const
{
    return b;
}
// Comper
bool Rational::Is_Equal(Rational r1, Rational r2)
{
    r1.Simplify();
    r2.Simplify();
    return r1.a == r2.a && r1.Get_b() == r2.Get_b();
}
// Sum
Rational Rational::Sum(Rational r1, Rational r2)
{
    Rational result;
    result.a = r1.a * r2.Get_b() + r1.Get_b() * r2.a;
    result.b = r1.Get_b() * r2.Get_b();
    result.Simplify();
    return result;
}
// Sub
Rational Rational::Sub(Rational r1, Rational r2)
{
    Rational result;
    result.a = r1.a * r2.Get_b() - r1.Get_b() * r2.a;
    result.b = r1.Get_b() * r2.Get_b();
    result.Simplify();
    return result;
}
// Multiple
Rational Rational::Mult(Rational r1, Rational r2)
{
    Rational result;
    result.a = r1.a * r2.a;
    result.b = r1.Get_b() * r2.Get_b();
    result.Simplify();
    return result;
}
// Divide
Rational Rational::Divi(Rational r1, Rational r2)
{
    Rational result;
    if (r2.a == 0)
    {
        cout << "division by zero!";
        exit(-1);
    }
    result.a = r1.a * r2.Get_b();
    result.b = r1.Get_b() * r2.a;
    result.Simplify();
    return result;
}

///////////////////////////end Rational/////////////////
class Complex
{
public:
    Rational real;
    Rational imag;
    Complex(Rational = Rational(0, 1), Rational = Rational(0, 1));
    void print();
    static bool Is_Equal(Complex, Complex);
    static Complex Sum(Complex, Complex);
    static Complex Sub(Complex, Complex);
    static Complex Multiple(Complex, Complex);
    static Complex Divide(Complex, Complex);
};

// Generator
Complex::Complex(Rational real, Rational imag)
{
    this->real = real;
    this->imag = imag;
}
// Comper
bool Complex::Is_Equal(Complex r1, Complex r2)
{
    return (Rational::Is_Equal(r1.real, r2.real) && Rational::Is_Equal(r1.imag, r2.imag));
}
// Sum
Complex Complex::Sum(Complex r1, Complex r2)
{
    Complex result;
    result.real = Rational::Sum(r1.real, r2.real);
    result.imag = Rational::Sum(r1.imag, r2.imag);
    return result;
}
// Sub
Complex Complex::Sub(Complex r1, Complex r2)
{
    Complex result;
    result.real = Rational::Sub(r1.real, r2.real);
    result.imag = Rational::Sub(r1.imag, r2.imag);
    return result;
}
// Multiple
Complex Complex::Multiple(Complex r1, Complex r2)
{
    Complex result;
    result.real = Rational::Sub((Rational::Mult(r1.real, r2.real)), (Rational::Mult(r1.imag, r2.imag)));
    result.imag = Rational::Sum((Rational::Mult(r1.real, r2.imag)), (Rational::Mult(r1.imag, r2.real)));
    return result;
}
// Divide
Complex Complex::Divide(Complex r1, Complex r2)
{
    Complex result;
    result.real = Rational::Divi((Rational::Sum(Rational::Mult(r1.real, r2.real), Rational::Mult(r1.imag, r2.imag))),
                                 (Rational::Sum(Rational::Mult(r2.real, r2.real), Rational::Mult(r2.imag, r2.imag))));
    result.imag = Rational::Divi((Rational::Sub(Rational::Mult(r1.imag, r2.real), Rational::Mult(r1.real, r2.imag))),
                                 (Rational::Sum(Rational::Mult(r2.real, r2.real), Rational::Mult(r2.imag, r2.imag))));
    return result;
}
// Print
void Complex::print()
{
    if (real.to_double() == 0 && imag.to_double() == 0)
        cout << 0;
    else if (real.to_double() == 0)
    {
        imag.print();
        cout << "i" ;
    }
    else if (imag.to_double() == 0)
        real.print();
    else
    {
        cout << "(";
        real.print();
        cout << ")+(";
        imag.print();
        cout << ")i";
        cout << endl;
    }
}

int main()
{
    Complex c1(Rational(2, 3), Rational(6, 1)), c2(Rational(-4, -1), Rational(6, 7));
    
    cout<<"*******************************************************";
    cout << "\nComplex Number1:";
    c1.print();
    cout << "Complex Number2:";
    c2.print();
    //////////////////Sum////////////////////
    cout<<"*******************************************************";
    cout << "\nThe Sum Of Complex Number:";
    Complex c3 = Complex::Sum(c1, c2);
    c3.print();
    /////////////////Sub////////////////////
    cout<<"*******************************************************";
    cout << "\nSubtraction Of Complex Number:";
    Complex c4 = Complex::Sub(c2, c2);
    c4.print();
    //////////////Multiple///////////////
    cout<<"*******************************************************";
    cout << "\nMultiplication Of Complex Number:";
    Complex c5 = Complex::Multiple(c1, c2);
    c5.print();
    ////////////Divide///////////////////
    cout<<"*******************************************************";
    cout << "\nDivision Of Complex Number:";
    Complex c6 = Complex::Divide(c1, c1);
    c6.print();
    cout<<"*******************************************************";
    cout << "\nComper: ";
    cout << Complex::Is_Equal(c1, c2) << endl;
    cout<<"*******************************************************";
}