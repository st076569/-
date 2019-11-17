// Реализовать универсальный градиентный спуск.

#include <iostream>
#include <cmath>
using namespace std;

const double dx = 0.0001;		// Приращение аргумента
const double step = 0.1;		// Коэффициент перед градиентом
const double err = 0.001;		// Погрешность

double Function1(double* x, int n)	// (-0.5,-1) - старт; step = 0.1; min = (0.99,0.99); f(min) = -4;
{
    double f = 0;
    f = pow(x[0],3) + 2 * pow(x[1],2) - 3 * x[0] - 4 * x[1];
    return f;
}

double Function2(double* x, int n)	// (0,0) - старт; step = 0.1; min = (-0.29,-0.16); f(min) = 0.77;
{
    double f = 0;
    f = pow(x[0],2) + 2 * pow(x[1],2) + exp(x[0] + x[1]);
    return f;
}

double Function3(double* x, int n)	// (-0.3,0.3) - старт; step = 0.1; min = (0.34,0.82); f(min) = -0.2;
{
    double f = 0;
    f = -sin(0.5 * pow(x[0],2) - 0.25 * pow(x[1],2) + 3) * cos(2 * x[0] + 1 - exp(x[1]));
    return f;
}

double Function4(double* x, int n)	// (1.1,1.1) - старт; step = 0.001; min = (1.057,1.118); f(min) = 0.0033;
{
    double f = 0;
    f = pow(1 - x[0],2) + 100 * pow(x[1] - x[0] * x[0],2);
    return f;
}

double Function5(double* x, int n)	// (4) - старт; step = 0.1; min = (0.0039); f(min) = 0.00;
{
    double f = 0;
    f = pow(x[0],2);
    return f;
}

void InputDot(double* x, int n)		// Ввод стартовой точки
{
    cout << "Write down start point coordinates" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ") ";
        cin >> x[i];
    }
}

void OutputDot(double* x, int n)	// Вывод точки х на экран
{
    cout << "Point coordinates : {";
    for (int i = 0; i < n; i++)
    {
        cout << x[i];
        if (i != n - 1)
        {
            cout << ", ";
        }
    }
    cout << "}" << endl;
}

void Gradient(double (*f)(double*, int), double* g, double* x, int n)	// Градиент "g" функции "f" в точке "х"
{
    double y[n];
    for (int i = 0; i < n; i++)
    {
        y[i] = x[i];
    }
    for (int i = 0; i < n; i++)
    {
        y[i] += dx;
        if (i > 0)
        {
            y[i - 1] = x[i - 1];
        }
        g[i] = (f(y,n) - f(x,n)) / dx;
    }
}

double Distance(double* x, double* y, int n)	// Расстояние между точками x, y
{
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += pow(x[i] - y[i],2);
    }
    return sqrt(sum);
}

void LocMin(double (*f)(double*, int), double* x, double& fmin, int n)	// Поиск локального минимума
{
    double grad[n];
    double xl[n];
    do
    {
        for (int i = 0; i < n; i++)
        {
            xl[i] = x[i];
        }
        Gradient(f,grad,x,n);
        for (int i = 0; i < n; i++)
        {
            x[i] -= step * grad[i];
        }
    }
    while (Distance(x,xl,n) > err);
    fmin = f(x,n);
}

int main()
{
    int dim = 0;
    double min = 0;
    cout << "Write down dimension : ";
    cin >> dim;
    if (dim > 0)
    {
        double* x = new double[dim];
        InputDot(x,dim);
        LocMin(Function3,x,min,dim);
        cout << "Loc Minimum : " << min << endl;
        OutputDot(x,dim);
        delete[] x;
    }
    system("Pause");
    return 0;
}