/*
(15 баллов)
Дан массив, содержащий перестановку чисел от 0 до N. Посчитать амортизационную 
стоимость линейного поиска элемента со значением i. провести численный эксперимент.
*/

#include "functions.h"
#include <cstdlib>
#include <iostream>

using namespace std;

bool have_action(double v)
{
    double x = (double) rand() / RAND_MAX;
    
    return x <= v;
}

void create_transposition(int* array, int num)
{
    for (int i = 0; i < num; i++)
    {
        array[i] = -1;
    }
    int k = 0, i = 0;
    while (k < num)
    {
        if (array[i] == -1 && have_action((double) 1 / (num - k)))
        {
            array[i] = k;
            k++;
        }
        i++;
        i %= num;
    }
}

int steps_num(int* array, int num, int temp)
{
    int k = 0;
    
    while (array[k] != temp && k != num)
    {
        k++;
    }
    
    return k;
}
