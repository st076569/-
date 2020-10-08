// написать программу, находящую среднее арифметическое факториалов последовательности чисел
#include <iostream>
using namespace std;

int factorial (int x)			//Факториал числа "х"
{
	int i, f = 1;
	for (i = 1; i <= x; i++) 
	{
		f*=i;
	}
	return f;
}

int main () 
{
	int i, n, sum = 0, x;
	cin >> n;			//Вводим количество чисел
	for (i = 1; i <= n; i++) 
	{
		cin >> x;
		sum+=factorial(x);	//Находим сумму факториалов
	}
	cout<<double(sum/n);		//Выводим среднее арифметическое
	return 0;
}