/*
Написать программу, находящую разложение натурального числа в
сумму натуральных квадратов, с наименьшим числом слагаемых
*/

#include <iostream>
#include <cmath>
using namespace std;

void FindMinSum(int** a, int n, int div)
{
    int num = 0, min = n + 1, sj = 0;
    a[1][0] = 1;
    a[1][1] = 1;
    for (int i = 2; i <= n; i++)
    {
        min = n + 1;
        for (int j = 1; j <= div; j++)
        {
            if (j*j <= i && a[i - j*j][0] < min)
            {
                min = a[i - j*j][0];
                num = i - j*j;
                sj = j;
            }
        }
        a[i][0] = min + 1;
        for (int j = 1; j <= div; j++)
        {
            a[i][j] = a[num][j];
        }
        a[i][sj]++;
    }
}

void OutNumber(int n, int* a, int k)
{
    bool isFirst = true;
    cout << n << " = ";
    for (int i = 1; i < k; i++)
    {
        if (a[i] > 0)
        {
            for (int j = 0; j < a[i]; j++)
            {
                if (isFirst)
                {
                    isFirst = false;
                } else
                {
                    cout << " + ";
                }
                cout << i*i;
            }
        }
    }
    cout << ";" << endl;
}

int main()
{
    int n = 0;
    cout << "Write down number : ";
    cin >> n;
    if (n > 0)
    {
        int div = sqrt(n);
        int** array = new int*[n + 1];
        for (int i = 0; i <= n; i++)
        {
            array[i] = new int[div + 1];
            for (int j = 0; j <= div; j++)
            {
                array[i][j] = 0;
            }
        }
        FindMinSum(array,n,div);
        OutNumber(n,array[n],div + 1);
        for (int i = 0; i <= n; i++)
        {
            delete[] array[i];
        }
        delete[] array;
    }
    system("Pause");
    return 0;
}