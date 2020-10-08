// Решить задачу о селениях и дорогах.

#include <iostream>
using namespace std;

struct Road	// Дорога между городами a и b
{
    int a, b;
    int cost;
};

void InArray(Road* a, int tnum)		// Ввод информации о дорогах
{
    int k = 0;
    cout << "Write down road price" << endl;
    for (int i = 0; i < tnum; i++)
    {
        for (int j = i + 1; j < tnum; j++)
        {
            cout << k + 1 << ") " << "[" << i << "]" << " --- " << "[" << j << "] : ";
            cin >> a[k].cost;
            a[k].a = i;
            a[k].b = j;
            k++;
        }
    }
}

void SortArray(Road* a, int rnum)	// Отсортировать по возрастанию стоимости
{
    bool haveSwap = false;
    Road temp;
    do
    {
        haveSwap = false;
        for (int i = 0; i < rnum - 1; i++)
        {
            if (a[i].cost > a[i + 1].cost)
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

bool HaveCycle(Road* a, int* rnum, int townNow, int townPrev, int* finish)	// Проверка на наличие цикла
{
    bool isCycle = false;
    if (townNow != *finish)
    {
        for (int i = 0; i < *rnum; i++)
        {
            if (townNow == a[i].a && townPrev != a[i].b)
            {
                isCycle = isCycle || HaveCycle(a,rnum,a[i].b,townNow,finish);
            } 
            else
            if (townNow == a[i].b && townPrev != a[i].a)
            {
                isCycle = isCycle || HaveCycle(a,rnum,a[i].a,townNow,finish);
            }
        }
    }
    else
    {
        isCycle = true;
    }
    return isCycle;
}

bool AccessGranted(Road* a, int rnum, Road x)	// Проверка: может ли новая дорога быть добавлена в множество
{
    bool haveCross1 = false, haveCross2 = false;
    bool haveAccess = false;
    for (int i = 0; i < rnum; i++)
    {
        haveCross1 = haveCross1 || a[i].a == x.a || a[i].b == x.a;
        haveCross2 = haveCross2 || a[i].a == x.b || a[i].b == x.b;
    }
    if (haveCross1 && haveCross2)
    {
        haveAccess = !HaveCycle(a,&rnum,x.a,x.b,&x.b);
    }
    else
    {
        haveAccess = true;
    }
    return haveAccess;
}

void FindCheapRoads(Road* a, int rnum)		// Нахождение базы минимального веса
{
    Road b[rnum];
    SortArray(a,rnum);
    int k = 1, minPrice = a[0].cost;
    b[0] = a[0];
    for (int i = 1; i < rnum; i++)
    {
        if (AccessGranted(b,k,a[i]))
        {
            minPrice += a[i].cost;
            b[k] = a[i];
            k++;
        }
    }
    cout << "Cheapest combination" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << i + 1 << ") " << "[" << b[i].a << "]" << " --- " << "[" << b[i].b << "] : " << b[i].cost << endl;
    }
    cout << "Total cost : " << minPrice << endl;
}

int main()
{
    int townNum = 0, roadNum = 0;
    cout << "Write down a number of towns : ";
    cin >> townNum;
    if (townNum > 1)
    {
        roadNum = (townNum * (townNum - 1)) / 2;
        Road* array = new Road[roadNum];
        InArray(array,townNum);
        FindCheapRoads(array, roadNum);
        delete[] array;
    }
    system("Pause");
    return 0;
}