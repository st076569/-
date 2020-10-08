/*
На вещественную ось брошено N отрезков. Найти максимальное по включению множество 
непересекающихся отрезков. Доказать через матроиды корректность алгоритма.
(Если таких множеств несколько, то программа выводит произвольное)
*/

#include <iostream>
using namespace std;

struct Segment		// Отрезок
{
    int number;		// Количество отрезков, непересекающихся с данным
    int min, max;
};

void InArray(Segment* a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ") ";
        cin >> a[i].min >> a[i].max;
    }
}

void SortArray(Segment* a, int n)
{
    bool haveSwap = false;
    Segment temp;
    do
    {
        haveSwap = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i].number < a[i + 1].number)
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
                haveSwap = true;
            }
        }
    }
    while (haveSwap);
}

bool HasCross(Segment a, Segment b)	// Проверка на наличие общих точек
{
    return (a.min <= b.min || a.min <= b.max) && (a.max >= b.min || a.max >= b.max);
}

void SortByCross(Segment* a, int n)	// Сортировка отрезков по убыванию кол-ва непересечений
{
    for (int i = 0; i < n; i++)
    {
        a[i].number = 0;
        for (int j = 0; j < n; j++)
        {
            if (j != i && !HasCross(a[i],a[j]))
            {
                a[i].number++;
            }
        }
    }
    SortArray(a,n);
}

void FindSegments(Segment* a, int n)	// Поиск и вывод наибольшего множества
{
    int b[n];
    int k = 1;
    bool wasCross = false;
    b[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wasCross = false;
        for (int j = 0; j < k; j++)
        {
            wasCross = HasCross(a[b[j]],a[i]) || wasCross;
        }
        if (!wasCross)
        {
            b[k] = i;
            k++;
        }
    }
    cout << "Maximum set" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << i + 1 << ") ";
        cout << a[b[i]].min << " " << a[b[i]].max << endl;
    }
}

int main()
{
    int n = 0;
    cout << "Write down number of segments : ";
    cin >> n;
    cout << "Write down segments (min, max)" << endl;
    Segment* array = new Segment[n];
    InArray(array,n);
    SortByCross(array,n);
    FindSegments(array,n);
    delete[] array;
    system("Pause");
    return 0;
}