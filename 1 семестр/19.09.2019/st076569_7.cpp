// Реализовать структуру данных (с примером использования), для хранения рациональных чисел в виде несократимых дробей.
// Перегрузить арифметику, сравнения, сделать конструкторы и оператор присвоения(=) от рациональных чисел,
// пар целых и просто целых чисел.

#include <iostream>
#include <cmath>
using namespace std;

struct Fraction				// структура, хранящая несократимые дроби
{
  int numerator,denominator;		// числитель и знаменатель соответственно    
    Fraction (int num, int den)		// конструктор от пары целых чисел
     {
       numerator = num;
       denominator = den;
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
     }
    Fraction ()				// конструктор по умолчанию
     {
       numerator = 0;
       denominator = 1;
     }
    Fraction operator= (Fraction f);
};

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

Fraction reduce (Fraction f)	// сократить дробь
{
  int n = gcd(f.numerator, f.denominator);
    f.numerator /= n;
    f.denominator /= n;
    if (f.denominator < 0)
    {
      f.numerator *= -1;
      f.denominator *= -1;
    }
    return f;
}

Fraction operator* (Fraction f1, Fraction f2)
{
  Fraction f3;
    f3.numerator = f1.numerator * f2.numerator;
    f3.denominator = f1.denominator * f2.denominator;
    return reduce(f3);
}

Fraction operator/ (Fraction f1, Fraction f2)
{
  Fraction f3;
    f3.numerator = f1.numerator * f2.denominator;
    f3.denominator = f1.denominator * f2.numerator;
    return reduce(f3);
}

Fraction operator+ (Fraction f1, Fraction f2)
{
  Fraction f3;
  int l = lcm(f1.denominator, f2.denominator);  
    f3.denominator = l;
    f3.numerator = f1.numerator*l/f1.denominator + f2.numerator*l/f2.denominator;
    return reduce(f3);
}

Fraction operator- (Fraction f1, Fraction f2)
{
  Fraction f3;
  int l = lcm(f1.denominator, f2.denominator);  
    f3.denominator = l;
    f3.numerator = f1.numerator*l/f1.denominator - f2.numerator*l/f2.denominator;
    return reduce(f3);
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

Fraction Fraction::operator= (Fraction f)
{
    numerator = f.numerator;
    denominator = f.denominator;
    return *this;
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
  Fraction a (11, 9);		// использование конструкторов
  Fraction c (10);
  Fraction b (a + c);

    /* cin >> a >> b; */	// возможен ввод с клавиатуры

    cout << " a = " << a << "; b = " << b << ";" << endl;	// примеры арифметич. операций
    cout << "1) " << a << " * " << b << " = " << a * b << endl;
    cout << "2) " << a << " / " << b << " = " << a / b << endl;
    cout << "3) " << a << " - " << b << " = " << a - b << endl;
    cout << "4) " << a << " + " << b << " = " << a + b << endl;
    
    if (a <= b)		// примеры сравнений
    { 
      cout << a << " <= " << b << endl;
    } else
    {
      cout << a << " > " << b << endl;
    }

    for (int i = 0; i <= 3; i++)
    {
      if (b > a / c)
      {
        cout << b << "; ";
      }
      b = b / c;
    }
    return 0;
}