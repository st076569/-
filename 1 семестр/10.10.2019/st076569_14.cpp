/*
На окружности заданы N точек, надо найти три точки такие, что площадь натянутого на них треугольника 
максимальна. Программа должна работать за время не большее O(N) 
*/

#include <iostream>
#include <cmath>
using namespace std;

void In_array(double* a, int n)			//Ввод упорядоченных точек
{
    cout << "Write down dots (radian) : ";
    for (int i = 0; i < n; cin >> a[i++]);
}

double Square(double a, double b, double c)	//Поиск площади треугольника
{
    double s1 = 0, s2 = 0, s3 = 0;
    s1 = 0.5 * (sin(a) + sin(b)) * (cos(b) - cos(a));
    s2 = 0.5 * (sin(b) + sin(c)) * (cos(c) - cos(b));
    s3 = 0.5 * (sin(a) + sin(c)) * (cos(c) - cos(a));
    return abs(s1 + s2 - s3);
}

int main()
{
    int N = 0;
    cout << "Write down number of dots : ";
    cin >> N;
    if (N >= 3)
    {
        int dot_1 = 0, dot_2 = 1, dot_3 = 2;
        int max_1 = 0, max_2 = 1, max_3 = 2;
        double ang[N];
        In_array(ang,N);
        while (dot_1 < N)
        {
            while (Square(ang[dot_1],ang[dot_2],ang[dot_3]) < Square(ang[dot_1],ang[dot_2],ang[(dot_3 + 1) % N]))
            {
                dot_3 = (dot_3 + 1) % N;
                if (Square(ang[dot_1],ang[dot_2],ang[dot_3]) > Square(ang[max_1],ang[max_2],ang[max_3]))
                {
                    max_1 = dot_1;
                    max_2 = dot_2;
                    max_3 = dot_3;
                    while (Square(ang[dot_1],ang[dot_2],ang[dot_3]) < Square(ang[dot_1],ang[(dot_2 + 1) % N],ang[dot_3]))
                    {
                        dot_2 = (dot_2 + 1) % N;
                        if (Square(ang[dot_1],ang[dot_2],ang[dot_3]) > Square(ang[max_1],ang[max_2],ang[max_3]))
                        {
                            max_1 = dot_1;
                            max_2 = dot_2;
                            max_3 = dot_3;
                        }
                    }
                }
            }
            dot_1++;
        }
        cout << "Max Triangle : " << ang[max_1] << "; " << ang[max_2] << "; " << ang[max_3] << endl;
    }
    else
    {
        cout << "Incorrect";
    }
    system("Pause");
    return(0);
}