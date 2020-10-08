/*
(10 баллов)
Написать структуру(не менее 10 полей), и пару функций:
put_to_file(), get_from_file().
Программа должна быть записана в стиле С.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

using namespace std;

const int arr_num = 20;
const int vec_num = 30;

#include <string>

struct MainElement
{
    string str1,str2;
    double vec1[vec_num];
    float vec2[vec_num];
    bool vec3[vec_num];
    double a1, b1, c1;
    long int a2, b2, c2;
    bool bool1;
    int array1[arr_num];
    char array2[arr_num];
    float array3[arr_num];    
};

void put_to_file(const char* fname, MainElement &e);
void get_from_file(const char* fname, MainElement &e);

void element_out(MainElement &e);
void element_init(MainElement &e);

#endif