// написать функцию, которая удаляет из целочисленного массива все четные элементы 
#include <iostream>
#include <ctime>
using namespace std;

void Del_odd (int*& a0, int& n)		// удаление всех четных элементов массива
{
  int n1 = 0, j = 0;
  for (int i = 0; i <= n; i++)
  {
    if (a0[i] % 2 != 0) n1++;
  }
  int* a1 = new int [n1];
  for (int i = 0; i <= n; i++)
  {
    if (a0[i] % 2 != 0)
    {
      a1[j] = a0[i];
      j++;
    } 
  }
  delete[] a0;
  n = n1-1;
  a0 = a1;
}

void In_array (int* a0, int n)        // заполнение массива случайными числами
{
  srand (time (0));
  for (int i = 0; i <= n; i++)
  {
    a0[i] = 1 + rand() % 100;
  }
}

void Out_array (int* a0, int n)       // вывод массива на экран
{
  for (int i = 0; i <= n; i++)
  {
    cout << a0[i] << " ";  
  }
  cout << endl;
}

int main ()
{
  int m = 19;
  int* a = new int[m+1];  
   In_array(a,m);
   Out_array(a,m);
   Del_odd(a,m);
   Out_array(a,m);
  delete[] a;
  return 0;
}