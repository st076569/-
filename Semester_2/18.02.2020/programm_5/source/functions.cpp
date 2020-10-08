/*
(10 баллов)
Написать структуру(не менее 10 полей), и пару функций:
put_to_file(), get_from_file().
Программа должна быть записана в стиле С.
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include "functions.h"

using namespace std;

void element_out(MainElement &e)
{
    cout << "+------------------------------------------+" << endl;
    cout << " <<<1>>> " << endl << "> " << e.str1 << endl << "> " << e.str2 << endl;
    cout << " <<<2>>> " << endl << "> " << e.a1 << "; " << e.b1 << "; " << e.c1 << endl;
    cout << " <<<3>>> " << endl << "> " << e.a2 << "; " << e.b2 << "; " << e.c2 << endl;
    cout << " <<<4>>> " << endl << "> ";
    if (e.bool1)
    {
        cout << "True";
    }
    else
    {
        cout << "False";
    }
    cout << endl;
    cout << " <<<5>>> " << endl << "> ";
    for (int i = 0; i < arr_num; i++)
    {
        if (i != arr_num - 1)
        {
            cout << e.array1[i] << ", ";
        }
        else
        {
            cout << e.array1[i] << endl;
        }
    }
    cout << " <<<6>>> " << endl << "> ";
    for (int i = 0; i < arr_num; i++)
    {
        if (i != arr_num - 1)
        {
            cout << e.array2[i] << ", ";
        }
        else
        {
            cout << e.array2[i] << endl;
        }
    }
    cout << " <<<7>>> " << endl << "> ";
    for (int i = 0; i < arr_num; i++)
    {
        if (i != arr_num - 1)
        {
            cout << e.array3[i] << ", ";
        }
        else
        {
            cout << e.array3[i] << endl;
        }
    }
    cout << " <<<8>>> " << endl << "> ";
    for (int i = 0; i < vec_num; i++)
    {
        if (i != vec_num - 1)
        {
            cout << e.vec1[i] << ", ";
        }
        else
        {
            cout << e.vec1[i] << endl;
        }
    }
    cout << " <<<9>>> " << endl << "> ";
    for (int i = 0; i < vec_num; i++)
    {
        if (i != vec_num - 1)
        {
            cout << e.vec2[i] << ", ";
        }
        else
        {
            cout << e.vec2[i] << endl;
        }
    }
    cout << " <<<10>>> " << endl << "> ";
    for (int i = 0; i < vec_num; i++)
    {
        if (e.vec3[i])
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

void element_init(MainElement &e)
{
    int str_len = 10 + rand() % 100;
    
    for (int i = 0; i < str_len; i++)
    {
        e.str1 += static_cast<char>(97 + rand() % 26);
        e.str2 += static_cast<char>(97 + rand() % 26);
    }
    
    e.a1 = 0.01 * (rand() % 50000);
    e.b1 = 0.01 * (rand() % 50000);
    e.c1 = 0.01 * (rand() % 50000);
    
    e.a2 = rand() % 50000;
    e.b2 = rand() % 50000;
    e.c2 = rand() % 50000;
    
    e.bool1 = rand() % 2 == 1;
    
    for (int i = 0; i < arr_num; i++)
    {
        e.array1[i] = rand() % 20000;
        e.array2[i] = static_cast <char> (32 + rand() % 94);
        e.array3[i] = -0.001 * (rand() % 50000);
    }
    
    for (int i = 0; i < vec_num; i++)
    {
        e.vec1[i] = 0.001 * (rand() % 50000);
        e.vec2[i] = -0.01 * (rand() % 50000);
        e.vec3[i] = rand() % 2 == 1;
    }
}

void put_to_file(const char* fname, MainElement &e)
{
    FILE *fp;
    int size = sizeof(MainElement);
    char *cp = (char*)&e;
    
    if ((fp = fopen(fname, "wb")) == NULL)
    {
        printf("Error : Can not open file");
        getchar();
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            fputc(*(cp + i), fp);
        }
    }
    fclose(fp);
}

void get_from_file(const char* fname, MainElement &e)
{
    FILE *fp;
    int size = sizeof(MainElement);
    char array[size];
    
    if ((fp = fopen(fname, "rb")) == NULL)
    {
        printf("Error : Can not open file");
        getchar();
    }
    else
    {
        for (int i = 0; i < size; ++i)
        {
            array[i] = fgetc(fp);
        }
    }
    fclose(fp);
    
    MainElement* A;
    A = (MainElement*)array;
    e = *A;
}
