/*
(10 баллов)
Создать класс с ~8 закрытыми полями. 
Написать функции обращающиеся к этим закрытым полям.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int arr_num = 16;
const int vec_num = 32;

class MainElement   // Класс, у которого будем менять поля
{
  private:
    double ad, bd, cd;
    float array3[arr_num];
    char array2[arr_num];
    long int ai, bi, ci;
    double vec1[vec_num];
    float vec2[vec_num];
    bool vec3[vec_num];
    int array1[arr_num];
    
  public:
    MainElement();
    // Возвращают значения полей
    long int return_ai();
    long int return_bi();
    long int return_ci();
    double return_ad();
    double return_bd();
    double return_cd();
    double return_vec1(int i);
    float return_vec2(int i);
    float return_array3(int i);
    bool return_vec3(int i);
    char return_array2(int i);
    int return_array1(int i);
    // Позволяют менять поля
    void edit_ai(long int x);
    void edit_bi(long int x);
    void edit_ci(long int x);
    void edit_ad(double x);
    void edit_bd(double x);
    void edit_cd(double x);
    void edit_vec1(int i, double x);
    void edit_vec2(int i, float x);
    void edit_vec3(int i, bool x);
    void edit_array1(int i, int x);
    void edit_array2(int i, char x);
    void edit_array3(int i, float x);
    // Вывод на экран
    void print();
};

struct ChangeClass  // Структура, позволяющая менять поля класса MainElement
{
    // Указатели на соответствующие поля класса MainElement
    double* p_ad;
    double* p_bd;
    double* p_cd;
    long int* p_ai;
    long int* p_bi;
    long int* p_ci;
    int* array1;
    char* array2;
    float* array3;
    double* vec1;
    float* vec2;
    bool* vec3;
    // Методы, меняющие поля класса
    void tie_object(MainElement& temp);
    void edit_ai(long int x);
    void edit_bi(long int x);
    void edit_ci(long int x);
    void edit_ad(double x);
    void edit_bd(double x);
    void edit_cd(double x);
    void edit_vec1(int i, double x);
    void edit_vec2(int i, float x);
    void edit_vec3(int i, bool x);
    void edit_array1(int i, int x);
    void edit_array2(int i, char x);
    void edit_array3(int i, float x);
    ChangeClass(MainElement& temp);
};

char* changed_byte(char* tp, char* cp, int size);
void fill_class(MainElement& temp);

#endif