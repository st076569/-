// Реализовать структуру данных (с примером использования), для хранения рациональных чисел в виде несократимых дробей.
// Перегрузить арифметику, сравнения, сделать конструкторы и оператор присвоения(=) от рациональных чисел,
// пар целых и просто целых чисел.

#include <iostream>
#include <cmath>
using namespace std;

int gcd (int a, int b)		// НОД(a, b)
{
  int r = 0;
    do
    {
      r = abs(a % b);
      if (r != 0)
      {
        a = b;
        b = r;
      }
    }
    while (r != 0);
    return b;
}

int lcm (int a, int b)		// НОК(a, b)
{
    return abs(a*b/gcd(a,b));
}

struct Fraction				// структура, хранящая несократимые дроби
{
  int numerator,denominator;		// числитель и знаменатель соответственно    
    Fraction (int num, int den)		// конструктор от пары целых чисел
     {
       numerator = num;
       denominator = den;
       reduce();
     }
    Fraction (int a)			// конструктор от целого числа
     {
       numerator = a;
       denominator = 1;
     }
    Fraction (const Fraction& f)	// конструктор от рационального числа
     {
       numerator = f.numerator;
       denominator = f.denominator;
       reduce();
     }
    Fraction ()				// конструктор по умолчанию
     {
       numerator = 0;
       denominator = 1;
     }
    void reduce ();			// сокращение дроби
    Fraction operator= (Fraction f)
     {
       numerator = f.numerator;
       denominator = f.denominator;
       reduce();
       return *this;
     }
    Fraction operator+= (Fraction f)
     {
       int l = lcm(denominator, f.denominator);
       numerator = numerator*l/denominator + f.numerator*l/f.denominator;
       denominator = l;
       reduce();
       return *this;
     }
    Fraction operator*= (Fraction f)
     {
       numerator *= f.numerator;
       denominator *= f.denominator;
       reduce();
       return *this;
     }
    Fraction operator-= (Fraction f)
     {
       int l = lcm(denominator, f.denominator);
       numerator = numerator*l/denominator - f.numerator*l/f.denominator;
       denominator = l;
       reduce();
       return *this;
     }
    Fraction operator/= (Fraction f)
     {
       numerator *= f.denominator;
       denominator *= f.numerator;
       reduce();
       return *this;
     }
};

void Fraction::reduce ()	// сократить дробь
{
  int n = gcd(numerator, denominator);
    numerator /= n;
    denominator /= n;
    if (denominator < 0)
    {
      numerator *= -1;
      denominator *= -1;
    }
}

Fraction operator* (Fraction f1, Fraction f2)
{
    f1 *= f2; 
    return f1;
}

Fraction operator/ (Fraction f1, Fraction f2)
{
    f1 /= f2;
    return f1;
}

Fraction operator+ (Fraction f1, Fraction f2)
{
    f1 += f2;
    return f1;
}

Fraction operator- (Fraction f1, Fraction f2)
{
    f1 -= f2;
    return f1;
}

bool operator> (Fraction f1, Fraction f2)
{
  int l = lcm(f1.denominator, f2.denominator);
  bool b = f1.numerator*l/f1.denominator > f2.numerator*l/f2.denominator;
    return b; 
}

bool operator< (Fraction f1, Fraction f2)
{
  int l = lcm(f1.denominator, f2.denominator);
  bool b = f1.numerator*l/f1.denominator < f2.numerator*l/f2.denominator;
    return b; 
}

bool operator== (Fraction f1, Fraction f2)
{
  int l = lcm(f1.denominator, f2.denominator);
  bool b = f1.numerator*l/f1.denominator == f2.numerator*l/f2.denominator;
    return b; 
}

bool operator>= (Fraction f1, Fraction f2)
{
  return !(f1 < f2);
}

bool operator<= (Fraction f1, Fraction f2)
{
  return !(f1 > f2);
}

bool operator!= (Fraction f1, Fraction f2)
{
  return !(f1 == f2);
}

std::ostream& operator<< (std::ostream &out, Fraction f)
{
    out << f.numerator << "/" << f.denominator;
    return out;
}

std::istream& operator>> (std::istream &in, Fraction &f)
{
    char c;
    in >> f.numerator >> c >> f.denominator; 
    return in;
}

int main ()
{
  Fraction a (-22, 18);		// использование конструкторов
  Fraction c (10);
  Fraction b (a + c);

    cout << " a = " << a << "; b = " << b << ";" << endl;	// примеры арифметич. операций
    cout << " *) " << a << " * " << b << " = " << a * b << endl;
    cout << " /) " << a << " / " << b << " = " << a / b << endl;
    cout << " -) " << a << " - " << b << " = " << a - b << endl;
    cout << " +) " << a << " + " << b << " = " << a + b << endl;
    a += b;
    cout << " +=) a += b" << " : a = " << a << endl;
    a -= b;
    cout << " -=) a -= b" << " : a = " << a << endl;
    a *= b;
    cout << " *=) a *= b" << " : a = " << a << endl;
    a /= b;
    cout << " /=) a /= b" << " : a = " << a << endl;

    if (a != b)		// примеры сравнений
    { 
      cout << a << " != " << b << endl;
    } else
    {
      cout << a << " = " << b << endl;
    }
    return 0;
}