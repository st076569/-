// Напишите эффективную программу, находящую все числа длины n являющиеся палиндромами.
// В комментариях напишите, почему перебор - эффективный.

// Данный алгоритм эффективный, потому что количество обрабатываемых значений 
// ассимптотически равняется размеру ответа.

#include <iostream>
#include <cmath>
using namespace std;

void out_turn (int a)		// Процедура вывода перевернутого числа "а"
{
  int b = 0;
    while (a > 0)
    {
      cout << a % 10;
      a /= 10;
    }
    cout << "; ";
}

void palindrome (int n)		// Процедура вывода всех палиндромов длины "n"
{
  int min = 1, max = 0;
    for (int i = 1; i <= n / 2 - 1; i++)
    {
      min *= 10; 
    }    
    max = min * 10 - 1;
    if (n % 2 == 0 && n > 1)
    {
      for (int i = min; i <= max; i++)
      {
        cout << i; 
        out_turn(i);
        if ((i - min + 1) % 10 == 0) cout << endl;
      }
    } else
    if (n > 1)
    {
      for (int i = min; i <= max; i++)
      {
        for (int j = 0; j <= 9; j++)
        {
          cout << i << j;
          out_turn(i);
        }
        cout << endl;
      }
    } else
    {
      for (int j = 0; j <= 9; j++)
        {
          cout << j << "; ";
        }
    }
}

int main ()
{
  int n;
    cout << "Write 'n' :" << endl;
    cin >> n; 
    n = abs(n);
    palindrome(n);
    return 0;
}