/*
Даны К упорядоченных массивов длины N, содержащих целые числа. Написать программу. 
Проверить есть ли число входящее в каждый из массивов. Выписать все такие числа. 
Программа должна работать за время не большее O(NK)
*/

#include <iostream>
using namespace std;

void Read_NK(int& n, int& k)		// Чтение N и K
{
    cout << "Write N (array length) : ";
    cin >> n;
    cout << "Write K (array number) : ";
    cin >> k;
}

void In_array(int n, int k, int** a)	// Ввод массивов (упорядоченных по возрастанию)
{
    cout << "Fill arrays" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << i+1 << ") ";
        for (int j = 0; j < n; cin >> a[i][j++]);
    }
}

void Check_Same(int n1, int* a1, int n2, int* a2, int& n3, int* a3)	// Нахождение одинаковых элементов в
{									// массивах: а1 и а2, и запись их в массив: а3
    int i1 = 0, i2 = 0, i3 = 0;
    while (i1 < n1 && i2 < n2)
    {
        if (a1[i1] < a2[i2])
        {
            i1 += 1;
        }
        else
        if (a2[i2] < a1[i1])
        {
            i2 += 1;
        }
        else
        {
            a3[i3] = a1[i1];
            i3 += 1;
            i1 += 1;
            i2 += 1;
        }
    }
    n3 = i3;
}

void Find_Same(int n, int k, int** a)	// Нахождение совпадающих элементов во всех массивах за О(NK)
{
    int* s1 = new int[n];
    int* s2 = new int[n];
    int n1 = n, n2 = 0;
    for (int i = 0; i < n; i++)
    {
        s1[i] = a[0][i];
        s2[i] = 0;
    }
    for (int i = 1; i < k && n1 != 0; i++)
    {
        Check_Same(n1,s1,n,a[i],n2,s2);
        n1 = n2;
        for (int j = 0; j < n; j++)
        {
            s1[j] = s2[j];
            s2[j] = 0;
            n2 = 0;
        }
    }
    cout << "Same elements : ";
    for (int i = 0; i < n1; cout << s1[i++] << " ");
    if (n1 == 0) 
    {
        cout << "---";
    }
    cout << endl;
    delete[] s1;
    delete[] s2;
}

int main()
{
    int n = 0, k = 0;    
    Read_NK(n,k);
    if (n > 0 && k > 0)
    {
        int** mas = new int*[k];
        for (int i = 0; i < k; i++)
        {
            mas[i] = new int[n];
        }
        In_array(n,k,mas);
        Find_Same(n,k,mas);
        for (int i = 0; i < k; i++)
        {
            delete[] mas[i];
        }
        delete[] mas;
    }
    else
    {
        cout << "Incorrect" << endl;
    }
    system("Pause");
    return 0;
}
