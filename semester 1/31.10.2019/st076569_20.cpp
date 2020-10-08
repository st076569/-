// Решить непрерывную задачу о рюкзаке и доказать через матроиды корректность алгоритма.

#include <iostream>
using namespace std;

struct Thing		// Структура "Вещь"
{
    int size;		// Объем или вес
    double unit;	// Удельная стоимость
};

void InArray(Thing* a, int n)
{
    int cost = 0;
    cout << "Size, Cost" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ") ";
        cin >> a[i].size >> cost;
        a[i].unit = (double) cost / a[i].size;
    }
}

void SortArray(Thing* a, int n)
{
    bool haveSwap = false;
    Thing temp;
    do
    {
        haveSwap = false;
        for (int i = 0; i < n - 1; i++)
        {
            if (a[i].unit < a[i + 1].unit)
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

void MaxCost(Thing* a, int n, int bagSize)	// Поиск комбинации с максимальной стоимостью
{
    int sizeNow = bagSize, i = 0;
    double maxCost = 0;
    cout << "Sequence :" << endl;
    do
    {
        if (sizeNow >= a[i].size)
        {
            sizeNow -= a[i].size;
            maxCost += a[i].unit * a[i].size;
            cout << i + 1 << ") " << a[i].size << "; " << a[i].size * a[i].unit << endl;
        }
        else
        {
            maxCost += a[i].unit * sizeNow;
            cout << i + 1 << ") " << a[i].size << "; " << a[i].size * a[i].unit;
            cout << " (" << sizeNow << "; " << sizeNow * a[i].unit << ")" << endl;
            sizeNow = 0;
        }
        i++;
    }
    while (sizeNow != 0 && i < n);
    cout << "Max Cost : " << maxCost << endl;
}

int main()
{
    int n = 0, w = 0;
    cout << "Write down size of bag : ";
    cin >> w;
    cout << "Write number of things : ";
    cin >> n;
    Thing* array = new Thing[n];
    InArray(array,n);
    SortArray(array,n);
    MaxCost(array,n,w); 
    delete[] array;
    system("Pause");
    return 0;
}