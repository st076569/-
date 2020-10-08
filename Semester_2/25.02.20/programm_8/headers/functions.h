/*
(10 баллов)
Создать структуру с ~8 полями. Экспериментально выяснить, 
как устроена укладка объекта такой структуры в памяти.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int arr_num = 8;
const int vec_num = 32;
const int rand_border = 50000;

#include <string>

struct MainElement
{
    double ad, bd, cd;
    float array3[arr_num];
    char array2[arr_num];
    long int ai, bi, ci;
    double vec1[vec_num];
    float vec2[vec_num];
    bool vec3[vec_num];
    int array1[arr_num];

    MainElement();
    void print();
};

void check_bytes_positions();

#endif