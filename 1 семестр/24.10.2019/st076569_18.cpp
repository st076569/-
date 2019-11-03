// Написать программу поиска k-ой порядковой статистики, основанной на Qsort

#include <iostream>
using namespace std;

int Fixed_Element(int* a, int beg, int end)	//Возвращает индекс опорного элемента
{
    int base = a[end];
    int temp = 0, left = beg, right = end;
    bool have_left = false, have_right = false;
    while (left != right)
    {
        if (!have_left && a[left] >= base) 
        {
            have_left = true;
        }
        if (!have_right && a[right] < base) 
        {
            have_right = true;
        }
        if (have_right && have_left)
        {
            have_right = false;
            have_left = false;
            temp = a[right];
            a[right] = a[left];
            a[left] = temp;
            if (abs(left - right) == 1)
            {
                left++;
            }
            else
            {
                left++;
                right--;
            }
        }
        else
        if (have_right && !have_left)
        {
            left++;
        }
        else
        if (!have_right && have_left)
        {
            right--;
        }
        else
        if (abs(left - right) == 1)
        {
            left++;
        }
        else
        {
            left++;
            right--;
        }
    }
    if (a[left] < base)
    {
        a[end] = a[left + 1];
        a[left + 1] = base;
        return left + 1;
    }
    else
    {
        a[end] = a[left];
        a[left] = base;
        return left;
    }
}

void In_Array(int* a, int n)
{
    cout << "Write down elements : ";
    for (int i = 0; i < n; cin >> a[i++]);
}

int Ordinal_Stat(int* a, int n, int k)		// Поиск к-ой статистики
{
    int pos = 0, beg = 0, end = n - 1;
    do
    {
        pos = Fixed_Element(a,beg,end);
        if (k < pos)
        {
            end = pos - 1;
        }
        if (k > pos)
        {
            beg = pos + 1;
        }
    }
    while (pos != k);
    return a[k];
}

int main()
{
    int n = 0, k = 0;
    cout << "Write number of elements : ";
    cin >> n;
    int* a = new int[n];
    In_Array(a,n);
    cout << "Write down statistic number 'k' (1.." << n << ") : ";
    cin >> k;
    k--;
    if (k >= 0 && k < n)
    {
        cout << "Ordinal statistic : " << Ordinal_Stat(a,n,k) << endl;
    }
    delete[] a;
    system("Pause");
    return 0;
}