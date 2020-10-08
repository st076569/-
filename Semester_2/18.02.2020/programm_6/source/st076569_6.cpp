// написать программу, находящую кол-во делителей натурального числа

#include <iostream>
#include "functions.h"

using namespace std;

int main() 
{
	int x;
    
	cin >> x;		//Вводим число
	if (Simple(x)) 		//Проверяем на простоту
	{
        cout << "Simple" << endl;
        cout << 1 << " " << x << endl;
	} else 
	{ 
        cout << "Compound" << endl;
        Divisors(x);
	}

	return 0;
}
