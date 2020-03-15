/*
(10 баллов)
Создать структуру с ~8 полями. Экспериментально выяснить, 
как устроена укладка объекта такой структуры в памяти.
*/

#include "functions.h"

void MainElement::print()   // Вывод структуры в консоль
{
    cout << "+------------------------------------------+" << endl;
    cout << " <<<1>>> " << endl << "> " << ai << "; " << bi << "; " << ci << endl;
    cout << " <<<2>>> " << endl << "> " << ad << "; " << bd << "; " << cd << endl;
    cout << " <<<3>>> " << endl << "> ";
    for (int i = 0; i < arr_num; i++)   // Вывод на экран array1
    {
        if (i != arr_num - 1)
        {
            cout << array1[i] << ", ";
        }
        else
        {
            cout << array1[i] << endl;
        }
    }
    cout << " <<<4>>> " << endl << "> ";
    for (int i = 0; i < arr_num; i++)   // Вывод на экран array2
    {
        if (i != arr_num - 1)
        {
            cout << array2[i] << ", ";
        }
        else
        {
            cout << array2[i] << endl;
        }
    }
    cout << " <<<5>>> " << endl << "> ";
    for (int i = 0; i < arr_num; i++)   // Вывод на экран array3
    {
        if (i != arr_num - 1)
        {
            cout << array3[i] << ", ";
        }
        else
        {
            cout << array3[i] << endl;
        }
    }
    cout << " <<<6>>> " << endl << "> ";
    for (int i = 0; i < vec_num; i++)   // Вывод на экран vec1
    {
        if (i != vec_num - 1)
        {
            cout << vec1[i] << ", ";
        }
        else
        {
            cout << vec1[i] << endl;
        }
    }
    cout << " <<<7>>> " << endl << "> ";
    for (int i = 0; i < vec_num; i++)   // Вывод на экран vec2
    {
        if (i != vec_num - 1)
        {
            cout << vec2[i] << ", ";
        }
        else
        {
            cout << vec2[i] << endl;
        }
    }
    cout << " <<<8>>> " << endl << "> ";
    for (int i = 0; i < vec_num; i++)   // Вывод на экран vec3
    {
        if (vec3[i])
        {
            cout << "True";
        }
        else
        {
            cout << "False";
        }
        if (i != vec_num - 1)
        {
            cout << ", ";
        }
        else
        {
            cout << endl;
        }
    }
    cout << "+------------------------------------------+" << endl;
}

MainElement::MainElement()  // Инициализация полей нулевыми значениями
{   
    ai = 0;
    bi = 0;
    ci = 0;

    ad = 0;
    bd = 0;
    cd = 0;
    
    for (int i = 0; i < arr_num; i++)
    {
        array1[i] = 0;
        array2[i] = 0;
        array3[i] = 0;
    }
    
    for (int i = 0; i < vec_num; i++)
    {
        vec1[i] = 0;
        vec2[i] = 0;
        vec3[i] = false;
    }
}

void check_bytes_positions()  // Выводит побайтовое распределение памяти для структуры
{
    MainElement temp;
    char* tp = (char*)&temp;
    int size = sizeof(MainElement);
    int longintsize = sizeof(long int);
    int intsize = sizeof(int);
    int doublesize = sizeof(double);
    int floatsize = sizeof(float);
    
    cout << endl;   // Выводит переменные и номера занимаемых ими байтов
    char* pt = (char*)&temp.ai;
    cout << " > ai : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + longintsize - 1 << ")" << endl;
    pt = (char*)&temp.bi;
    cout << " > bi : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + longintsize - 1 << ")" << endl;
    pt = (char*)&temp.ci;
    cout << " > ci : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + longintsize - 1 << ")" << endl;
    cout << endl;
    pt = (char*)&temp.ad;
    cout << " > ad : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + doublesize - 1 << ")" << endl;
    pt = (char*)&temp.bd;
    cout << " > bd : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + doublesize - 1 << ")" << endl;
    pt = (char*)&temp.cd;
    cout << " > cd : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + doublesize - 1 << ")" << endl;
    
    cout << endl;   // Выводит массивы и номера занимаемых ими байтов
    pt = (char*)&temp.array1;
    cout << " > array1 : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + arr_num * intsize - 1 << ")" << endl;
    pt = (char*)&temp.array2;
    cout << " > array2 : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + arr_num - 1 << ")" << endl;
    pt = (char*)&temp.array3;
    cout << " > array3 : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + arr_num * floatsize - 1 << ")" << endl;
    
    cout << endl;   // Выводит массивы и номера занимаемых ими байтов
    pt = (char*)&temp.vec1;
    cout << " > vec1 : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + vec_num * doublesize - 1 << ")" << endl;
    pt = (char*)&temp.vec2;
    cout << " > vec2 : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + vec_num * floatsize - 1 << ")" << endl;
    pt = (char*)&temp.vec3;
    cout << " > vec3 : (" << (int)(pt - tp) << ") -- (" << (int)(pt - tp) + vec_num - 1 << ")" << endl;
    cout << endl;
}