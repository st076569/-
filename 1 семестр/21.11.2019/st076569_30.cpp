/*
Реализовать определение числа уникальных элементов во множестве с помощью алгоритма HyperLogLog.
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const uint32_t MultiplyFNV = 0x01000193;	// 16777619
const uint32_t InitialFNV  = 0x811C9DC5;	// 2166136261
const uint32_t max_len = 32;			// Длина хеш-кода
const double omega = 1.04;

uint32_t FNV1(string s)		// Хеш-функция
{
    uint32_t hash = InitialFNV;
    for(int i = 0; i < s.length(); i++)
    {
        hash ^= s[i];
        hash *= MultiplyFNV;
    }
    return hash;
}

int rang(uint32_t hash, int end)
{
    int r = 1;
    while (hash % 2 == 0 && r <= end)
    {
        hash >>= 1;
        r++;
    }
    return r;
}

double log2(double x)
{
    return log(x)/log(2);
}

void CreateWords(string* array, int num_word)	// Заполняет массив строками (с некоторой периодичностью)
{
    for (int i = 0; i < num_word; i++)
    {
        array[i] = "ghfhgfhguytyyyyuyuytggfhgytuyty" + to_string(i % 10000);
    }
}

int HyperLogLog(double std_err, string* word, int num_word)
{
    int k = log2(pow(omega / std_err,2));
    int hash_len = max_len - k, num_rate = round(pow(2,k));
    double alpha = 0.7213 / (1 + 1.079 / num_rate);
    int rate[num_rate];
    for (int i = 0; i < num_rate; i++)
    {
        rate[i] = 0;
    }
    uint32_t hash = 0;
    int j = 0;
    for (int i = 0; i < num_word; i++)
    {
        hash = FNV1(word[i]);
        j = hash >> hash_len;
        rate[j] = max(rate[j],rang(hash,hash_len));
    }
    double c = 0;
    int E = 0;
    uint64_t pow_2_32 = pow(2,32);
    for (int i = 0; i < num_rate; i++)
    {
        c += 1 / (pow(2,rate[i]));
    }
    E = alpha * pow(num_rate,2) / c;
    // +-------------------------------+ //
    // | Проводим коррекцию результата | //
    // +-------------------------------+ //
    if (E <= round(num_rate * 5 / 2.0))
    {
        double v = 0;
        for (int i = 0; i < num_rate; i++)
        {
            if (rate[i] == 0) 
            {
                v++;
            }
        }
        if (round(v) > 0)
        {
            E = num_rate * log(num_rate / v);
        }
    }
    else 
    if (E > round(pow_2_32 * 1 / 30.0))
    {
        E = -pow_2_32 * log(1.0 - static_cast<double>(E) / pow_2_32);
    }
    // +-------------------------------+ //
    return E;
}

int main()
{
    string W[15000];
    CreateWords(W,15000);
    cout << " > Number of unique items : ";
    cout << HyperLogLog(0.065,W,15000) << endl;
    system("Pause");
    return 0;
}