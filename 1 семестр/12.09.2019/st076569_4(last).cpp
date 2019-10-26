/*
написать функцию сортировки массива, использующую указательную арифметику 
вместо обращения по индексам
*/

#include <iostream>
#include <ctime>
using namespace std;

void Sort_Array (int* a0, int n)       //процедура сортировки массива по возрастанию (пузырек)
{
    bool sign = false;
    int temp = 0;
    do 
    {
        sign = false;
        for (int* p = a0; p < a0 + n; p++)
        {
            if (*p > *(p + 1))
            {
                sign = true;
                temp = *p;
                *p = *(p + 1);
                *(p + 1) = temp;
            }
        }
    }
    while (sign);
}

void In_Array (int* a0, int n)        // заполнение массива случайными числами
{
    srand (time (0));
    for (int* p = a0; p <= a0+n; p++) 
    {
      *p = 1 + rand() % 500;
    }
}

void Out_Array (int* a0, int n)       // вывод массива на экран
{
    for (int* p = a0; p <= a0+n; p++) 
    {
      cout << *p << " ";  
    }
    cout << endl;
}

int main ()
{
    int a[20];
    In_Array(a,19);	// заполняем массив
    Out_Array(a,19);	// выводим неотсортированный массив
    Sort_Array(a,19);	// сортируем
    Out_Array(a,19);	// выводим отсортированный массив
    return 0;
}
