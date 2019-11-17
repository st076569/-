/*
Дана карта города, в котором улицы перпендикулярны. На карте отмечены дома и скверы.
Каждый дом и сквер имеет некоторую культурную ценность (целое число). Человек может
идти на север, на восток, и срезать на северо восток через сквер. Найти маршрут из
точки (a,b) в точку (c,d) c наибольшей культурной ценностью в формате набора направлений
движения “N”,”E”,”NE” и ценность этого маршрута. Можно считать, что такой маршрут существует.
Если таких маршрутов несколько - вывести любой из них.
*/

#include <iostream>
using namespace std;

struct Area
{
    bool isExist, haveNE;	// Существование области, наличие прохода по диагонали
    int cost;			// Культурная ценность области
};

struct Intersection
{
    Area W, S, SW;		// Три прилегающие к перекрестку области
    int side;			// (0,1,2) Запад, Юго-запад, Юг соответственно
    int cost;			// Ценность на данном перекрестке
};

void InputDots(bool& err, int& x1, int& y1, int& x2, int& y2, int size)
{
   cout << "Write down start - end point coordinates" << endl;
   cout << "1) Start (x,y) : ";
   cin >> x1 >> y1;
   cout << "2) End   (x,y) : ";
   cin >> x2 >> y2;
   bool errx = x1 > x2 || x1 < 0 || x1 > size - 1 || x2 > size - 1 || x2 < 0;
   bool erry = y1 < y2 || y1 < 0 || y1 > size - 1 || y2 > size - 1 || y2 < 0;
   err = errx || erry;
}

void FillArray(Intersection** a, int size)
{
    int areaCost = 0, haveNE = 0;
    cout << "Write down information about areas (quadrate " << size - 1 << "x" << size - 1 << ")" << endl;
    cout << "Write areas cost" << endl;
    for (int i = 0; i < size - 1; i++)
    {
        cout << "string " << i + 1 << " : ";
        for (int j = 0; j < size - 1; j++)
        {
            cin >> areaCost;
            a[i][j].S.isExist = true;
            a[i][j].S.cost = areaCost;
            a[i][j + 1].SW.isExist = true;
            a[i][j + 1].SW.cost = areaCost;
            a[i + 1][j + 1].W.isExist = true;
            a[i + 1][j + 1].W.cost = areaCost;
        }
    }
    cout << "Write : '1' - if area is square, '0' - if area is building" << endl;
    for (int i = 0; i < size - 1; i++)
    {
        cout << "string " << i + 1 << " : ";
        for (int j = 0; j < size - 1; j++)
        {
            cin >> haveNE;
            a[i][j].S.haveNE = haveNE != 0;
            a[i][j + 1].SW.haveNE = haveNE != 0;
            a[i + 1][j + 1].W.haveNE = haveNE != 0;
        }
    }
}

void FindBestWay(Intersection** a, int x1, int y1, int x2, int y2)
{
    int max = 0, num = 0;
    int Wcost = 0, Scost = 0, SWcost = 0;
    bool hasW, hasS, hasSW;
    for (int y = y1; y >= y2; y--)
    {
        for (int x = x1; x <= x2; x++)
        {
            max = 0;
            num = 0;
            Wcost = 0;
            Scost = 0;
            SWcost = 0;
            hasW = false;
            hasS = false;
            hasSW = false;
            if (x - 1 >= x1)
            {
                hasW = true;
                Wcost = a[y][x - 1].cost;
                if (a[y][x].W.isExist)
                {
                    Wcost += a[y][x].W.cost;
                }
                if (a[y][x].SW.isExist)
                {
                    Wcost += a[y][x].SW.cost;
                }
            }
            if (y + 1 <= y1)
            {
                hasS = true;
                Scost = a[y + 1][x].cost;
                if (a[y][x].S.isExist)
                {
                    Scost += a[y][x].S.cost;
                }
                if (a[y][x].SW.isExist)
                {
                    Scost += a[y][x].SW.cost;
                }
            }
            if (x - 1 >= x1 && y + 1 <= y1 && a[y][x].SW.haveNE)
            {
                hasSW = true;
                SWcost = a[y + 1][x - 1].cost + a[y][x].SW.cost;
            }
            if (hasS)
            {
                max = Scost;
                num = 2;
                if (Wcost > max && hasW)
                {
                    max = Wcost;
                    num = 0;
                }
                if (SWcost > max && hasSW)
                {
                    max = SWcost;
                    num = 1;
                }
            } else
            if (hasW)
            {
                max = Wcost;
                num = 0;
                if (Scost > max && hasS)
                {
                    max = Scost;
                    num = 2;
                }
                if (SWcost > max && hasSW)
                {
                    max = SWcost;
                    num = 1;
                }
            } else
            if (hasSW)
            {
                max = SWcost;
                num = 1;
                if (Wcost > max && hasW)
                {
                    max = Wcost;
                    num = 0;
                }
                if (Scost > max && hasS)
                {
                    max = Scost;
                    num = 2;
                }
            }           
            a[y][x].cost = max;
            a[y][x].side = num;
        }
    }
    int x = x2, y = y2, k = 0;
    int way[(x2 - x1)*2];
    while (x != x1 || y != y1)
    {
        way[k] = a[y][x].side;
        switch (a[y][x].side)
        {
            case 0:
                x--;
                break;
            case 1:
                y++;
                x--;
                break;
            case 2:
                y++;
                break;
        }
        k++;
    }
    cout << "Maximum cultural value : " << a[y2][x2].cost << endl;
    cout << "Optimal way : ";
    for (int i = k - 1; i >= 0; i--)
    {
        switch (way[i])
        {
            case 0:
                cout << "E ";
                break;
            case 1:
                cout << "NE ";
                break;
            case 2:
                cout << "N ";
                break;
        }
    }
    cout << endl;
}

int main()
{
    bool haveErr = false;
    int size = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    cout << "Origin of coordinate system in upper left corner." << endl;
    cout << "Coordinate system start from '0'." << endl;
    cout << "Write down city size : ";
    cin >> size;
    cout << "<<<<<<<<<<<<>>>>>>>>>>>>" << endl;
    if (size > 0)
    {
        Intersection** array = new Intersection*[size];
        for (int i = 0; i < size; i++)
        {
            array[i] = new Intersection[size];
            for (int j = 0; j < size; j++)
            {
                array[i][j].W.isExist = false;
                array[i][j].S.isExist = false;
                array[i][j].SW.isExist = false;
                array[i][j].cost = 0;
            }
        }
        FillArray(array,size);
        cout << "<<<<<<<<<<<<>>>>>>>>>>>>" << endl;
        InputDots(haveErr,x1,y1,x2,y2,size);
        if (!haveErr)
        {
            FindBestWay(array,x1,y1,x2,y2);
        }
        for (int i = 0; i < size; i++)
        {
            delete[] array[i];
        }
        delete[] array;
    }
    system("Pause");
    return 0;
}