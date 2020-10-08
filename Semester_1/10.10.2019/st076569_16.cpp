// Реализовать timsort без использования дополнительной памяти

#include <iostream>
using namespace std;

void MergeSort(int* a1, int* a2, int* b1, int* b2)	// Процедура слияния двух подмассивов внутри основного массива
{
    int temp = 0;
    do
    {
        if (*a1 > *b1)
        {
            temp = *b1;
            for (int* p = b1; p != a1; p--)
            {
                *p = *(p - 1);
            }
            *a1 = temp;
            a1 += 1;
            a2 += 1;
            b1 += 1;
        }
        else
        {
            a1 +=1;
        }
        
    }
    while (a2 != b2 && a1 != b1);
}

int GetMin(int n)			// Поиск критической длины подмассива
{
    int r = 0;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

void InsertionSort(int* a, int n)	// Сортировка вставками
{
    int base = 0, temp = 0, k = 0;
    while (base < n - 1)
    {
        temp = a[base + 1];
        k = 0;
        while (temp > a[k])
        {
            k += 1;
        }
        for (int i = base + 1; i > k; i--)
        {
            a[i] = a[i - 1];
        }
        a[k] = temp;
        base += 1;
    }
}

void TimSort(int* a1, int n, int min)	// TimSort (сортировка по возрастанию)
{
    if (n > min)
    {
        int n1, n2;
        if (n % 2 == 0)
        {
            n1 = n / 2;
            n2 = n1;
        }
        else
        {
            n1 = n / 2;
            n2 = n1 + 1;
        }
        TimSort(a1,n1,min);
        TimSort(a1 + n1,n2,min);
        MergeSort(a1,a1 + n1 - 1,a1 + n1,a1 + n - 1);
    }
    else
    {
        InsertionSort(a1,n);
    }
}

void In_array(int* a, int n)	// Ввод массива		
{
    cout << "(Write down elements)" << endl;
    cout << "Array before : ";
    for (int i = 0; i < n; cin >> a[i++]);
}

void Out_array(int* a, int n)	// Вывод массива
{
    cout << "Array after  : ";
    for (int i = 0; i < n; cout << a[i++] << " ");
    cout << endl;
}

int main()
{
    int n = 0;
    cout << "Write the number of elements : ";
    cin >> n;
    if (n > 0)
    {
        int* mas = new int[n];
        In_array(mas,n);
        TimSort(mas,n,GetMin(n)); 
        Out_array(mas,n);
        delete[] mas;
    }
    else
    {
        cout << "Incorrect" << endl;
    }
    system("Pause");
    return 0;
}