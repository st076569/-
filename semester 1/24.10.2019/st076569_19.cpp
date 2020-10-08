/*
Провести эксперимент, для сортировки выбором. Экспериментально определить отношение 
между сравнением и swap, при котором сравнения малы по сравнению с перестановкой?
*/

#include <iostream>
#include <ctime>
using namespace std;

void InArray(int* a, int* b, int* c, int n)	//Заполнение массива случайными числами
{
    for (int i = 0; i < n; i++)
    {
        a[i] = 1 + rand() % 100;
        c[i] = a[i];
        b[i] = a[i];
    }
}

void OutArray(int* a, int n)			//Вывод массива на экран
{
    cout << "Array : ";
    for (int i = 0; i < n; cout << a[i++] << " ");
    cout << endl;
}

void MergeArray(int* a1, int* a2, int* b1, int* b2, int& swap, int& comp)	//Процедура слияния двух подмассивов
{
    int temp = 0;
    do
    {
        comp++;
        if (*a1 > *b1)
        {
            swap++;
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

void MergeSort(int* a, int n, int& swap, int& comp)	//MergeSort (сортировка по возрастанию)
{
    if (n > 1)
    {
        int n1, n2;
        n1 = n / 2;
        n2 = n - n1;
        MergeSort(a,n1,swap,comp);
        MergeSort(a + n1,n2,swap,comp);
        MergeArray(a,a + n1 - 1,a + n1,a + n - 1,swap,comp);
    }
}

void SelectionSort(int* a, int n, int& swap, int& comp)	//Сортировка выбором
{
    int min = 0, min_num = 0, temp = 0;
    for (int i = 0; i < n; i++)
    {
        min = a[i];
        min_num = i;
        for (int j = i + 1; j < n; j++)
        {
            comp++;
            if (a[j] < min)
            {
                min = a[j];
                min_num = j;
            }
        }
        if (min_num != i)
        {
            swap++;
            temp = a[min_num];
            a[min_num] = a[i];
            a[i] = temp;
        }
    }
}

int DivideArray(int* a, int beg, int end, int& swap, int& comp)	//Возвращает индекс опорного элемента
{
    int base = a[end];
    int temp = 0, left = beg, right = end;
    bool have_left = false, have_right = false;
    while (left != right)
    {
        if (!have_left)
        {
            comp++;
            if (a[left] >= base) 
            {
                have_left = true;
            }
        }
        if (!have_right)
        {
            comp++;
            if (a[right] < base) 
            {
                have_right = true;
            }
        }
        if (have_right && have_left)
        {
            have_right = false;
            have_left = false;
            swap++;
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
        swap++;
        a[end] = a[left + 1];
        a[left + 1] = base;
        return left + 1;
    }
    else
    if (end != left)
    {
        swap++;
        a[end] = a[left];
        a[left] = base;
        return left;
    }
    else
    {
        return end;
    }
}

void QuickSort(int* a, int n, int& swap, int& comp)
{
    if (n > 1)
    {
        int base = DivideArray(a,0,n - 1,swap,comp);
        QuickSort(a,base,swap,comp);
        QuickSort(a + base + 1,n - 1 - base,swap,comp);
    }
}

int main()
{
    int n = 1500, swap1 = 0, comp1 = 0, swap2 = 0, comp2 = 0, swap3 = 0, comp3 = 0;
    double k = 0;
    int a[n],b[n],c[n];
    srand(time(0));
    InArray(a,b,c,n);	
    MergeSort(a,n,swap1,comp1);
    SelectionSort(b,n,swap2,comp2);
    QuickSort(c,n,swap3,comp3);

    cout << "Number of elements : " << n << endl;
    cout << "MergeSort" << endl;
    cout << "Number 'swap'       : " << swap1 << endl;	//Кол-во операций swap
    cout << "Number 'comparison' : " << comp1 << endl;  //Кол-во сравнений
    cout << "SelectionSort" << endl;
    cout << "Number 'swap'       : " << swap2 << endl;
    cout << "Number 'comparison' : " << comp2 << endl;
    cout << "QuickSort" << endl;
    cout << "Number 'swap'       : " << swap3 << endl;
    cout << "Number 'comparison' : " << comp3 << endl;

    for (int i = 1; i <= 200; i++)			//Сравнение с быстрой сортировкой
    {
        swap3 = 0; comp3 = 0; swap2 = 0; comp2 = 0;
        InArray(a,b,c,n);
        SelectionSort(b,n,swap2,comp2);
        QuickSort(c,n,swap3,comp3);
        k += (comp2 - comp3)/(swap3 - swap2);		//Сумма всех коэффициентов (для среднего значения)
    }
    cout << "(For QuickSort) swap_time / copmarison_time >= " << k / 200 << endl;
    k = 0;
    for (int i = 1; i <= 200; i++)			//Сравнение с MergeSort
    {
        swap3 = 0; comp3 = 0; swap2 = 0; comp2 = 0;
        InArray(a,b,c,n);
        SelectionSort(b,n,swap2,comp2);
        MergeSort(c,n,swap3,comp3);
        k += (comp2 - comp3)/(swap3 - swap2);		//Сумма всех коэффициентов (для среднего значения)
    }
    cout << "(For MergeSort) swap_time / copmarison_time >= " << k / 200 << endl;
    system("Pause");
    return 0;
}