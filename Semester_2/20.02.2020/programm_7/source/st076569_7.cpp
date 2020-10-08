/*
(15 баллов)
Дан массив, содержащий перестановку чисел от 0 до N. Посчитать амортизационную 
стоимость линейного поиска элемента со значением i. провести численный эксперимент.
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "functions.h"

using namespace std;

int main()
{
    int start_N = 200;
    int sup = 20;
    int repeat_N = 3;
    float del = 0;
    
    srand(time(0));
    cout << " << Average time >>" << endl;
    
    for (int i = 1; i <= sup; ++i)
    {
        int count = start_N * i;
        int array[count];
        float average = 0;
        
        for (int j = 0; j < repeat_N; ++j)
        {
            float sum = 0;
            create_transposition(array, count);
            for (int k = 0; k < count; ++k)
            {
                sum += steps_num(array, count, rand() % count);
            }
            average += sum / count;
        }
        
        average /= repeat_N;
        if (i == 1)
        {
            del = average;
        }
        printf(" > ( %*u %s" ,4 , count, ") "); 
        printf("%8.3f", average);
        cout << " : [" << (average / del) << "]" << endl;
    }
    
    cout << "Press 'Enter' to continue...";
    getchar();
    
    return 0;
}
