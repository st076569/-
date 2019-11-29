/*
Задача о расписании(“о графике” о_О)
Есть k задач. Каждая задача приходит в момент t_i и требует tau_i времени на решение.
Нужно написать программу обеспечивающую оптимальное расписание (по числу решенных задач)
на время [t_start, t_end] (t_start<t_i<t_end; t_i+tau_i<t_end)
*/

#include <iostream>
using namespace std;

enum direction {Left, Up};

struct Task
{
    int t_start, t_end;
};

struct Element
{
    direction way;
    int count, t_end;
    bool haveTask;
};

void Example()
{
    cout << " +-----------------------------------------------+" << endl;
    cout << " | Example :                                     |" << endl;
    cout << " | > Write down the number of tasks  : 3         |" << endl;
    cout << " | > Write down the total start time : 0         |" << endl;
    cout << " | > Write down the total end time   : 9         |" << endl;
    cout << " | > Write down all tasks (time_start, time_end) |" << endl;
    cout << " |   1) 1 5                                      |" << endl;
    cout << " |   2) 3 7                                      |" << endl;
    cout << " |   3) 6 8                                      |" << endl;
    cout << " | <<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>> |" << endl;
    cout << " | > Maximum profit (tasks count) : 2            |" << endl;
    cout << " | > Tasks                                       |" << endl;
    cout << " |   1) 1 5                                      |" << endl;
    cout << " |   2) 6 8                                      |" << endl;
    cout << " +-----------------------------------------------+" << endl;
    cout << " <<<<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>>>" << endl;
}

void InArray(Task *array, int number)
{
    cout << " > Write down all tasks (time_start, time_end) :" << endl;
    for (int i = 0; i < number; i++)
    {
        cout << "   " << i + 1 << ") ";
        cin >> array[i].t_start >> array[i].t_end;
    }
}

void SortArray (Task *array, int number)
{
    bool haveSwap = false;
    Task temp;
    do 
    {
        haveSwap = false;
        for (int i = 0; i < number - 1; i++)
        {
            if (array[i].t_end > array[i + 1].t_end)
            {
                haveSwap = true;
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
    while (haveSwap);
}

void OptimalTimeTable(Task *array, int num, int start, int end)
{
    int width = end - start + 1, height = num + 1;
    Element table[height][width];
  // Заполняем массив
    for (int i = 0; i < width; i++)
    {
        table[0][i].count = 0;
        table[0][i].haveTask = false;
        table[0][i].t_end = start;
        table[0][i].way = Left;
    }
    for (int i = 0; i < height; i++)
    {
        table[i][0].count = 0;
        table[i][0].haveTask = false;
        table[i][0].t_end = start;
        table[i][0].way = Up;
    }
    for (int i = 1; i < height; i++)
    {
        for (int j = 1; j < width; j++)
        {
            table[i][j].count = table[i - 1][j].count;
            table[i][j].way = Up;
            table[i][j].haveTask = false;
            table[i][j].t_end = table[i - 1][j].t_end;
            if (array[i - 1].t_start > table[i - 1][j].t_end && array[i - 1].t_end < j + start)
            {
                table[i][j].count++;
                table[i][j].t_end = array[i - 1].t_end;
                table[i][j].haveTask = true;
            }
            if (table[i][j].count < table[i][j - 1].count)
            {
                table[i][j].count = table[i][j - 1].count;
                table[i][j].haveTask = false;
                table[i][j].way = Left;
                table[i][j].t_end = table[i][j - 1].t_end;
            }
        }
    }
    cout << " <<<<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << " > Maximum profit (tasks count) : " << table[height - 1][width - 1].count << endl;
    cout << " > Tasks" << endl;
  // Обратный ход
    int a[num];
    int i = height - 1, j = width - 1, k = 0;
    while (i != 0 && j != 0)
    {
        switch (table[i][j].way)
        {
            case Left:
                j--;
                break;
            case Up:
                if (table[i][j].haveTask)
                {
                    a[k] = i - 1;
                    k++;
                }
                i--;
                break;
        }
    }
    for (int p = k - 1; p >= 0; p--)
    {
        cout << "   " << k - p << ") " << array[a[p]].t_start << " " << array[a[p]].t_end << endl;
    }
}

int main()
{
    int number = 0, time_start = 0, time_end = 0;
    Example();
    cout << " > Write down the number of tasks  : ";
    cin >> number;
    cout << " > Write down the total start time : ";
    cin >> time_start;
    cout << " > Write down the total end time   : ";
    cin >> time_end;
    Task array[number];
    InArray(array,number);
    SortArray(array,number);
    OptimalTimeTable(array,number,time_start,time_end);
    system("Pause");
    return 0;
}