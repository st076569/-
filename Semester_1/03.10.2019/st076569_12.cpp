//Реализовать решето эратосфена
#include <iostream>
using namespace std;

void choose_prime (bool* a, int k)	//Решето Эратосфена
{
    for (int i = 0; i <= k; a[i++] = 1);
    for (int i = 2; i <= k; i++)
    {
        if (a[i])
        {
            for (int j = 2*i; j <= k; j += i)
            {
                a[j] = 0;
            }
        }
    }
}

void out_mas (bool* a, int k)		//Вывод на экран всех простых чисел от 2 до k
{
    for (int i = 2; i <= k; i++)
    {
         if (a[i]) cout << i << " ";
    }
    cout << endl;
}

int main()
{
  int n = 0;
    cout << "Write max number" << endl;
    cin >> n;
  bool* simple_mas = new bool[n+1];
    choose_prime(simple_mas, n);
    out_mas(simple_mas, n);
    delete[] simple_mas;
    system("Pause");
    return 0;
}