/*
Эффективно смоделировать RAID 1, для k буферов размера n кБайт. (?)
Технология использует контрольные суммы для восстановления данных в случае выхода
из строя одного жёсткого диска. Нужно проделать тоже самое, только на буферах (массивах фиксированной длины).
В моделировании нужно заполнить несколько буферов данных, по ним построить буфер контрольных сумм.
Затем выбрать случайным образом один из буферов, как исчезнувший. После восстановить исчезнувшие данные
и сравнить восстановленные данные с настоящими.
*/

#include <iostream>
#include <ctime>
using namespace std;

void PutRandomData(bool** array, int num, int size)	// Заполняем массивы случайным образом
{
    srand(time (0));
    for (int i = 0; i < num; i++) 
    {
        for (int j = 0; j < size; j++)
        {
            array[i][j] = 1 == rand() % 2;
        }
    }
    int k = 0;
    for (int j = 0; j < size; j++) 
    {
        k = 0;
        for (int i = 0; i < num; i++)
        {
            if (array[i][j])
            {
                k++;
            }
        }
        array[num][j] = 1 == k % 2;
    }
}

void CoutItem(int num)
{
    cout << "   " << num << ")";
    if (num > 9)
    {
        cout << " : ";
    }
    else
    {
        cout << "  : ";
    }
}

void CoutBufer(bool** array, int size, int num)
{
    CoutItem(num + 1);
    for (int i = 0; i < size; i++)
    {
        if (array[num][i])
        {
            cout << '1';
        }
        else
        {
            cout << '0';
        }
    }
    cout << endl;
}

void CoutRaid(bool** array, int num, int size)
{
    cout << " > Main buffers" << endl;
    for (int i = 0; i < num; i++)
    {
        CoutBufer(array,size,i);
    }
    cout << " > Control bufer" << endl;
    CoutBufer(array,size,num);
}

void RestoreBufer(bool** array, int num, int size, int del_num)	// Восстановление утерянного буфера
{
    cout << " > Original" << endl;
    CoutBufer(array,size,del_num);
    int k = 0;
    for (int j = 0; j < size; j++) 
    {
        k = 0;
        for (int i = 0; i <= num; i++)
        {
            if (array[i][j] && i != del_num)
            {
                k++;
            }
        }
        array[del_num][j] = 1 == k % 2;
    }
    cout << " > After restoring" << endl;
    CoutBufer(array,size,del_num);
}

int main()
{
    int buf_num = 0, buf_size = 0, buf_del = 0; 
    cout << " > Write down number of bufers : ";
    cin >> buf_num;
    cout << " > Write down bufer size : ";
    cin >> buf_size;
    if (buf_size > 0 && buf_num > 1)
    {
        bool** raid = new bool*[buf_num + 1];	// Последний буфер - буфер контрольных сумм
        for (int i = 0; i <= buf_num; i++)
        {
            raid[i] = new bool[buf_size];
        }
        PutRandomData(raid,buf_num,buf_size);
        CoutRaid(raid,buf_num,buf_size);
        cout << " > Write down destroyed bufer number : ";
        cin >> buf_del;
        if (buf_del > 0 && buf_del <= buf_num)
        {
            RestoreBufer(raid,buf_num,buf_size,buf_del - 1);
        }
        for (int i = 0; i <= buf_num; i++)
        {
            delete[] raid[i];
        }
        delete[] raid;
    }
    system("Pause");
    return 0;
}