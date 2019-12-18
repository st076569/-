/*
Реализовать универсальный поиск глобального максимума методом имитации отжига.
*/

#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

const int D = 1;                // Размерность пространства
const int repeat_num = 5;       // Число повторений алгоритма
const double T_end = 1;         // Конечная температура
const double T_start = 20;      // Начальная температура
const double Pi = 3.14159265;

struct PartialArgument
{
    double val;     // Аргумент в данном измерении
    double A, B;    // Начало и конец области поиска
};

struct Argument
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

int sign(double x)
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

double DecreaseTemp(int step)   // Ф-ия изменения температуры
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

bool HaveEvent(double chance)       // Выдает true с вероятностью chance
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
    bool havechange = false;
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

int main()
{
    Argument v_start, v, v_max;
    int step = 0;
    double T = 0;
    double max_value = 0;
    
    srand(time(0));
    
    // -- Инициализация -- //
    cout << " > Write down left and right border of searching area : " << endl;
    for (int i = 0; i < D; i++)
    {
        cout << i + 1 << ") Coordinate : ";
        cin >> v_start.coord[i].A >> v_start.coord[i].B;
        v_start.coord[i].val = v_start.coord[i].A + ((double)(rand()) / RAND_MAX) * (v_start.coord[i].B - v_start.coord[i].A);
    }
    max_value = Function3(v_start);
    
    // -- Повышение точности результата -- //
    for (int i = 0; i < repeat_num; i++)
    {
        v = v_start;
        T = T_start;
        step = 0;
        
        // -- Имитация отжига -- //
        while (T > T_end)
        {
            step++;
            T = DecreaseTemp(step);
            v = NewPosition(Function3, v, T);
            if (max_value < Function3(v))
            {
                max_value = Function3(v);
                v_max = v;
            }
        }
    }
    
    cout << " > Maximum point : " << v_max << endl;
    cout << " > Maximum value : " << max_value << endl;
    
    system("Pause");
    return 0;
}