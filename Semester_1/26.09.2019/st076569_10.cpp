// Напишите программу перебирающую все перестановки массива букв в лексикографическом порядке.
// Программа должна работать не более чем за O(n!*n) шагов.

#include <iostream>
using namespace std;

const int count = 4;			// Количество элементов в массиве

bool in_mas (int x, int n, int* a)	// Функция проверки нахождения числа "х" в массиве "а" до позиции "n"
{
  bool isinside = false;
    for (int i = 0; i <= n; i++)
    {
      if (x == a[i]) 
      {
        isinside = true;
      }
    }
    return isinside;
}

void translate (int* a)			// Перевод чисел в буквы по таблице ASCII и вывод массива на экран
{
  int shift = 97;
    cout << "( ";
    for (int i = 0; i <= count - 1; i++)
    {
      cout << char(a[i] + shift) << " ";
    }
    cout << ")" << endl;
}

void F (int num, int pos, int* a)	// Рекурсивная процедура
{
    if (num >= 0) 
    {
      a[pos] = num;
    }
    for (int i = 0; i <= count - 1; i++)
    {
      if (!in_mas(i, pos, a)) 
      {
        F(i,pos+1,a);
      }
    }
    if (pos == count - 1)
    {
      translate(a);
    }
}

int main ()
{
  int mas[count];			// В массиве хранятся числа (0..count-1)
    F(-1,-1,mas);			// Буквы появляются только при выводе на экран
    return 0;
}