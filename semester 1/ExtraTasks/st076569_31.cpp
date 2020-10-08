/*
Реализовать универсальный поиск глобального максимума методом имитации отжига.
*/

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

const int D = 1;                // Размерность пространства
const int Repeat_num = 5;       // Число повторений алгоритма
const double T_end = 1;         // Конечная температура
const double T_start = 20;      // Начальная температура
const double Pi = 3.14159265;   // Число Пи

struct PartialArgument
{
    double val;                 // Аргумент в данном измерении
    double A, B;                // Начало и конец области поиска
};

struct Argument                 // Вектор
{
    PartialArgument coord[D];
};

double Function2(Argument v)    // Периодическая
{
    return 100 * cos(v.coord[0].val - 3) / (1 + abs(v.coord[0].val - 3));
}

double Function3(Argument v)    // Имитация голоса 1
{
    double ampl1 = (abs(sin(v.coord[0].val / 8)) + 1);
    double ampl2 = (abs(cos(v.coord[0].val + Pi * (abs(cos(v.coord[0].val)) + 1))) + 1) * 0.5;
    
    return ampl1 * (3 * sin(v.coord[0].val * (abs(cos(v.coord[0].val + Pi / 3) / 5 + 1))) + ampl2 * cos(v.coord[0].val * 20));
}

double Function4(Argument v)    // Имитация голоса 2
{
    return abs(8 * sin(v.coord[0].val / 2) + 2 * cos(2 * v.coord[0].val) + (1 + abs(cos(2 * v.coord[0].val))) * sin(20 * v.coord[0].val));
}

int sign(double x)              // Знак числа
{
    if (x > 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
    
    return 0;
}

double DecreaseTemp(int step)   // Функция изменения температуры
{
    return T_start * pow(0.95, step);
}

Argument GenerateRandomPos(Argument v, double T)  // Генерация случайной позиции
{
    double a_i = 0;
    double z_i = 0;
    double x_i_new = 0;
    Argument temp;
    
    for (int i = 0; i < D; i++)
    {
        do
        {
            a_i = (double)(rand()) / RAND_MAX;
            z_i = sign(a_i - 0.5) * T * (pow(1 + 1 / T, abs(2 * a_i - 1)) - 1);
            x_i_new = v.coord[i].val + z_i * (v.coord[i].B - v.coord[i].A);
        }
        while (x_i_new < v.coord[i].A || x_i_new > v.coord[i].B);
        temp.coord[i].val = x_i_new;
        temp.coord[i].A = v.coord[i].A;
        temp.coord[i].B = v.coord[i].B;
    }
    
    return temp;
}

bool HaveEvent(double chance)   // Выдает true с вероятностью chance
{
    double event = (double)(rand()) / RAND_MAX;
    
    if (event < chance)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double TransitionChance(double dE, double temp) // Вероятность перехода
{
    return exp(-dE / temp);
}

Argument NewPosition(double (*f)(Argument), Argument v_old, double T)
{
    double dE = 0, E_old = f(v_old);
    Argument v_new;
    
    do
    {
        v_new = GenerateRandomPos(v_old, T);
        dE = E_old - f(v_new);
    }
    while (!HaveEvent(TransitionChance(dE, T)));
    
    return v_new;
}

std::ostream& operator<< (std::ostream &out, Argument x)
{
    out << "{";
    for (int i = 0; i < D; i++)
    {
        out << x.coord[i].val;
        if (i < D - 1)
        {
            out << ", ";
        }
    }
    out << "}";
    
    return out;
}

void Initialisation(Argument &v_start)
{
    cout << " > Write down left and right border of searching area : " << endl;
    for (int i = 0; i < D; i++)
    {
        cout << i + 1 << ") Coordinate : ";
        cin >> v_start.coord[i].A >> v_start.coord[i].B;
        v_start.coord[i].val = v_start.coord[i].A + ((double)(rand()) / RAND_MAX) * (v_start.coord[i].B - v_start.coord[i].A);
    }
}

double GlobalMax(double (*f)(Argument), Argument start, Argument &v_max)
{
    Argument v;
    int step = 0;
    double max = 0, f_val = 0, T = T_start;
    
    // -- Метод имитации отжига -- //
    max = f(start);
    v = start;
    while (T > T_end)
    {
        step++;
        T = DecreaseTemp(step);
        v = NewPosition(f, v, T);
        f_val = f(v);
        if (max < f_val)
        {
            max = f_val;
            v_max = v;
        }
    }
    // -- //
    
    return max;
}

int main()
{
    Argument v_start, v_max, precise_v_max;
    double precise_max_value = 0, max_value = 0;
    
    // -- Инициализируем генератор случайных чисел -- //
    srand(time(0));
    // -- //
    
    // -- Инициализация начальной позиции и границ -- //
    Initialisation(v_start);
    max_value = Function3(v_start);
    // -- //
    
    // -- Повышение точности результата -- //
    for (int i = 0; i < Repeat_num; i++)
    {
        max_value = GlobalMax(Function3, v_start, v_max);
        if (max_value > precise_max_value || i == 0)
        {
            precise_max_value = max_value;
            precise_v_max = v_max;
        }
    }
    // -- //
    
    cout << " > Maximum point : " << precise_v_max << endl;
    cout << " > Maximum value : " << precise_max_value << endl;
    
    system("Pause");
    return 0;
}