/*
Написать функции, проверяющие является ли число:
1) Числом Мерсена
2) Числом Ферма
3) Числом Вильсона
4) Числом Вагстаффа
5) Числом Вифериха
6) Числом Софи Жермен
7) Числом Хиггса
*/

#include <iostream>
#include <cmath>
using namespace std;

bool Simple (int x)		//Функция проверки числа на простоту
{	
    bool is_simple = true;
    int n = sqrt(x);
    if (x == 1) 
    {
        is_simple = false;
    }
    for (int i = 2; is_simple == true && i <= n; i++ )
    {
        if (x % i == 0) 
        {
            is_simple = false;	
        }
    }
    return is_simple;
}

bool Mersenne_number (int x)	//Проверка на число Мерсенна
{
    bool is_mers_num = true;
    if (x % 2 == 0 || x < 0)
    {
        is_mers_num = false;
    }
    else
    {
        x += 1;
        while (x % 2 == 0)
        {
            x /= 2;
        }
        if (x != 1)
        {
            is_mers_num = false;
        }
    }
    return is_mers_num;
}

bool Fermat_number (int x)	//Проверка на число Ферма
{
    bool is_fer_num = true;
    if (x % 2 == 0 || x < 3)
    {
        is_fer_num = false;
    }
    else
    {
        int k = 0;
        x -= 1;
        while (x % 2 == 0)
        {
            x /= 2;
            k += 1;
        }
        if (x != 1)
        {
            is_fer_num = false;
        }
        else
        {
            while (k % 2 == 0)
            {
                k /= 2;
            }
            if (k != 1)
            {
                is_fer_num = false;
            }
        }
    }
    return is_fer_num;
}

bool Wilson_number (int x)	//Проверка на число Вильсона
{
    bool is_wils_num = true;
    if (x < 1 || x > 600000)
    {
        is_wils_num = false;
    }
    else
    {
        long long unsigned int balance = 1, mod = x*x;
        for (int i = 1; i < x; i++)
        {
            balance *= i;
            balance %= mod;
        }
        if ((balance + 1) % mod != 0)
        {
            is_wils_num = false;
        }
    }
    return is_wils_num;
}

bool Wagstaff_number (int x)	//Проверка на число Вагстаффа
{
    bool is_wags_num = true;
    if (x % 2 == 0 || x < 0)
    {
        is_wags_num = false;
    }
    else
    {
        int k = 0;
        x *= 3;
        x -= 1;
        while (x % 2 == 0)
        {
            x /= 2;
            k += 1;
        }
        if (x != 1)
        {
            is_wags_num = false;
        }
        else
        {
            if (!Simple(k))
            {
                is_wags_num = false;
            }
        }
    }
    return is_wags_num;
}

bool Wieferich_number (int x)	//Проверка на число Вифериха
{
    bool is_wief_num = true;
    if (x < 2 || x % 2 == 0)
    {
        is_wief_num = false;
    }
    else
    {
        long long unsigned int balance = 1, mod = x*x;
        for (int i = 1; i < x; i++)
        {
            balance *= 2;
            balance %= mod;
        }
        if (balance != 1)
        {
            is_wief_num = false;
        }
    }
    return is_wief_num;
}

bool Sophie_g_number (int x)	//Проверка на число Софи Жермен
{
    return (Simple(x) && x > 1 && Simple(2*x+1));
}

/*
bool Higgs_number (int x)	//Проверка на число Хиггса реккурсивным алгоритмом
{
    bool is_hig_num = true;
    if (!Simple(x) || x < 2 || x > 127)
    {
        is_hig_num = false;
    }
    else
    if (x != 2)
    {
        int mod = x - 1;
        unsigned int multiply = 1;
        for (int i = x - 1; i >= 2; i--)
        {
            if (Higgs_number(i))
            {
                multiply *= i*i;
                multiply %= mod;
            }
        }
        if (multiply != 0)
        {
            is_hig_num = false;
        }
    }
    return is_hig_num;
}
*/

bool Higgs_number (int x)	//Проверка на число Хиггса
{
    bool is_hig_num = true;
    if (!Simple(x) || x < 2 || x > 100000)
    {
        is_hig_num = false;
    }
    else
    if (x != 2)
    {
        bool* hig = new bool[x+1];
        for (int i = 0; i <= x; hig[i++] = 1);
        for (int i = 3; i <= x; i++)
        {
            if (Simple(i))
            {
                unsigned int multiply = 1, mod = i-1;
                for (int j = 2; j < i; j++)
                {
                    if (hig[j])
                    {
                        multiply *= j*j;
                        multiply %= mod;
                    }
                }
                if (multiply != 0)
                {
                    hig[i] = 0;
                }
            }
            else
            {
                hig[i] = 0;
            }
        }
        if (hig[x] != 1)
        {
            is_hig_num = false;
        }
        delete[] hig;
    }
    return is_hig_num;
}

int main()
{
    int x = 0;
    cout << "Write number : ";
    cin >> x;

    if (Mersenne_number(x)) 
        cout << "1) Mersenne number  (True)" << endl;
    else
        cout << "1) Mersenne number  (False)" << endl;

    if (Fermat_number(x)) 
        cout << "2) Fermat number    (True)" << endl;
    else
        cout << "2) Fermat number    (False)" << endl;

    if (Wilson_number(x)) 
        cout << "3) Wilson number    (True)" << endl;
    else
        cout << "3) Wilson number    (False)" << endl;

    if (Wagstaff_number(x)) 
        cout << "4) Wagstaff number  (True)" << endl;
    else
        cout << "4) Wagstaff number  (False)" << endl;

    if (Wieferich_number(x)) 
        cout << "5) Wieferich number (True)" << endl;
    else
        cout << "5) Wieferich number (False)" << endl;

    if (Sophie_g_number(x)) 
        cout << "6) Sophie G. number (True)" << endl;
    else
        cout << "6) Sophie G. number (False)" << endl;

    if (Higgs_number(x)) 
        cout << "7) Higgs number     (True)" << endl;
    else
        cout << "7) Higgs number     (False)" << endl;

    system("Pause");
    return 0;
}