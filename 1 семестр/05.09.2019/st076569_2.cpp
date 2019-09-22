// реализовать функцию Аккермана
#include <iostream>
using namespace std;

int A (int m, int n)	//Функция Аккермана
{
	if (m==0) 
	{
	  return n+1;
	}  else 
	if (m > 0 && n == 0) 
	{
	  return A(m-1, 1);
	}  else
	if (m > 0 && n > 0) 
	{
	  return A(m-1, A(m, n-1));
	} else 
	{ 
	  return 0;
	}
}

int main () 
{
	int m,n;
	cin>>m>>n;	//Вводим числа "m" и "n"
	cout<<A(m, n);	//Выводим значение функции
	return 0;
}