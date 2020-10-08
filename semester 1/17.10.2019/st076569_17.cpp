//Реализовать умножение Карацубы для длинной арифметики

#include <iostream>
using namespace std;

const int N = 256;		//Максимальная длина числа

struct bigint			//Длинная арифметика
{
    short int num[N];		//Массив - число
    short int beg;		//Начало последовательности
    bool sign;			//true - положительное; false - отрицательное

    bigint()			//Конструктор по умолчанию
     {
        for (int i = 0; i < N; num[i++] = 0);
        sign = true;
        beg = N - 1;
     }
    bigint(const bigint& a)	//Конструктор копирования
     {
        for (int i = 0; i < N; i++)
        {
            num[i] = a.num[i];
        }
        sign = a.sign;
        beg = a.beg;
     }
    void clear()		//Обнуление числа
     {
        for (int i = 0; i < N; num[i++] = 0);
        sign = true;
        beg = N - 1;
     }
    int length()		//Возвращает длину числа
     {
        return N - beg;
     }
    void reduce()		//Убрать ненужные нули
     {
        while (beg < N - 1 && num[beg] == 0)
        {
            beg++;
        }
     }
    bigint lhalf()		//Возвращает левую половину числа
     {
        bigint temp;
        if (length() > 1)
        {
            int len = length() - length() / 2, j = N - 1;
            temp.sign = sign;
            for (int i = beg + len - 1; i >= beg; i--)
            {
                temp.num[j--] = num[i];
            }
            temp.beg = j + 1;
            temp.reduce();
        }
        else
        {
            temp = *this;
        }
        return temp;
     }
    bigint rhalf()		//Возвращает правую половину числа
     {
        bigint temp;
        if (length() > 1)
        {
            int len = length() / 2, j = N - 1;
            temp.sign = sign;
            for (int i = N - 1; i >= N - len ; i--)
            {
                temp.num[j--] = num[i];
            }
            temp.beg = j + 1;
            temp.reduce();
        }
        else
        {
            temp = *this;
        }
        return temp;
     }
    void lmove(int k)		//Сдвиг влево на k позиций
     {
        for (int i = beg; i < N; i++)
        {
            num[i - k] = num[i];
            num[i] = 0;
        }
        beg -= k;
     }
    bigint& operator+= (bigint a)
     {
        short int digit = 0, count = N - 1, sum = 0;
        while (count >= beg || count >= a.beg || digit != 0)
        {
            sum = digit + a.num[count] + num[count];
            num[count] = sum % 10;
            digit = sum / 10;
            if (count < beg)
            {
                beg = count;
            }
            count -= 1;
        }
        return *this;
     }
    bigint& operator-= (bigint a)
     {
        if (beg < a.beg || beg == a.beg && num[beg] >= a.num[a.beg])
        {
            short int count = N - 1;
            while (count >= beg || count >= a.beg)
            {
                if (num[count] < a.num[count])
                {
                    num[count] += 10;
                    num[count - 1] -= 1;
                }
                num[count] -= a.num[count];
                if (count < beg)
                {
                    beg = count;
                }
                count -= 1;
            }
            reduce();
        }
        return *this;
     }
    bigint& operator*= (short int a)	//Умножение на число (0..9)
     {
        bigint x;
        for (int i = 1; i <= a; i++)
        {
            x += *this;
        }
        *this = x;
        return *this;
     }
};

bigint operator+ (bigint a, bigint b)
{
    a += b;
    return a;
}

bigint operator- (bigint a, bigint b)
{
    a -= b;
    return a;
}

void givenull(bigint& a, bigint& b)	//Дополняет числа нулями до выравнивания по четной длине
{
    int delta = 0;
    if (a.length() > b.length())
    {
        delta = a.length() - b.length();
        if (a.length() % 2 != 0)
        {
            a.beg -= 1;
            delta += 1;
        }
        b.beg -= delta;
    }
    else
    {
        delta = b.length() - a.length();
        if (b.length() % 2 != 0)
        {
            b.beg -= 1;
            delta += 1;
        }
        a.beg -= delta;
    }
}

bigint operator*(bigint a, bigint b)		//Процедура умножения
{
    bigint x;
    if (a.beg == N - 1)
    {
        x = b;
        x *= a.num[a.beg];
    }
    else
    if (b.beg == N - 1)
    {
        x = a;
        x *= b.num[b.beg];
    }
    else
    {
        givenull(a,b);
        bigint A1, B1, A2, B2, A1A2, B1B2, A1B2_A2B1;
        int shift = a.length() / 2;
        A1 = a.lhalf();
        B1 = a.rhalf();
        A2 = b.lhalf();
        B2 = b.rhalf();
        A1A2 = A1 * A2;
        B1B2 = B1 * B2;
        A1B2_A2B1 = (A1 + B1) * (A2 + B2) - A1A2 - B1B2;
        A1A2.lmove(2*shift);
        A1B2_A2B1.lmove(shift);
        x = A1A2 + A1B2_A2B1 + B1B2;
    }
    if (a.sign != b.sign) 
    {
        x.sign = false;
    }
    return x;
}

std::ostream& operator<< (std::ostream &out, const bigint& a)	//Вывод на экран
{
    if (!a.sign) 
    {
        out << '-';
    }
    for (int i = a.beg; i < N; out << a.num[i++]);
    return out;
}

std::istream& operator>> (std::istream &in, bigint& a)		//Ввод чисел
{
    string str = "";
    int j = N - 1;
    in >> str;
    a.clear();
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] == '-')
        {
            a.sign = false;
        }
        else
        {
            a.num[j--] = str[i] - '0';
        }
    }
    a.beg = j + 1;
    a.reduce();
    return in;
}

int main()
{
    bigint x, y;
    cout << "Write down numbers : ";
    cin >> x >> y;
    cout << "Product : " << x * y << endl;
    system("Pause");
    return 0;
}