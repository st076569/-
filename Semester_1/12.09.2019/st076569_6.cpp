// провести эксперимент, по сравнению эффективности суммирования элементов массива через индексы и указательную арифметику
#include <iostream>
#include <ctime>
using namespace std;

void In_array (short int* a, int k)        // заполнение массива случайными числами
{
  for (int i = 0; i <= k; i++)
  {
    a[i] = 1 + i % 500;
  }
}

double Time_1 (short int* a, int k)
{
  unsigned int s = 0;
  int beg, end; 
  beg = clock();
   for (int i = 0; i <= k; i++)
   {
     s+=a[i];
   }
  end = clock();
  return (double) (end-beg) / CLOCKS_PER_SEC;
}

double Time_2 (short int* a, int k)
{
  unsigned int s = 0;
  int beg, end; 
  short int* q = a + k;
  beg = clock();
   for (short int* p = a; p != q; p++)
   {
     s+=*p;
   }
  end = clock();
  return (double) (end-beg) / CLOCKS_PER_SEC;
}

int main ()
{
  int n = 0;
  cin >> n;
  short int* A = new short int[n];
  In_array(A, n-1);
  for (int i = 0; i <= 5; i++)
  {
    cout << "<-------------------->" << endl;
    cout << "First time  : " << Time_1(A, n) << endl;
    cout << "Second time : " << Time_2(A, n) << endl;
  }
  delete[] A;
  return 0;
}
