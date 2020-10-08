/*
(10 баллов)
Создать класс с ~8 закрытыми полями. 
Написать функции обращающиеся к этим закрытым полям.
*/

#include "functions.h"

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

////////// Методы класса, возвращающие значения полей \\\\\\\\\\

long int MainElement::return_ai()
{
    return ai;
}

long int MainElement::return_bi()
{
    return bi;
}

long int MainElement::return_ci()
{
    return ci;
}

double MainElement::return_ad()
{
    return ad;
}

double MainElement::return_bd()
{
    return bd;
}

double MainElement::return_cd()
{
    return cd;
}

double MainElement::return_vec1(int i)
{
    return vec1[i];
}

float MainElement::return_vec2(int i)
{
    return vec2[i];
}

bool MainElement::return_vec3(int i)
{
    return vec3[i];
}

int MainElement::return_array1(int i)
{
    return array1[i];
}

char MainElement::return_array2(int i)
{
    return array2[i];
}

float MainElement::return_array3(int i)
{
    return array3[i];
}

////////// end \\\\\\\\\\

////////// Методы класса, меняющие значения полей \\\\\\\\\\

void MainElement::edit_ai(long int x)
{
    ai = x;
}

void MainElement::edit_bi(long int x)
{
    bi = x;
}

void MainElement::edit_ci(long int x)
{
    ci = x;
}

void MainElement::edit_ad(double x)
{
    ad = x;
}

void MainElement::edit_bd(double x)
{
    bd = x;
}

void MainElement::edit_cd(double x)
{
    cd = x;
}

void MainElement::edit_vec1(int i, double x)
{
    vec1[i] = x;
}

void MainElement::edit_vec2(int i, float x)
{
    vec2[i] = x;
}

void MainElement::edit_vec3(int i, bool x)
{
    vec3[i] = x;
}

void MainElement::edit_array1(int i, int x)
{
    array1[i] = x;
}

void MainElement::edit_array2(int i, char x)
{
    array2[i] = x;
}

void MainElement::edit_array3(int i, float x)
{
    array3[i] = x;
}

////////// end \\\\\\\\\\

void MainElement::print()   // Вывод класса в консоль
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

char* changed_byte(char* tp, char* cp, int size)    // Возвращает указатель на измененный байт
{
    char* pointer = NULL;
    for (int i = 0; i < size; ++i)
    {
        if (tp[i] != cp[i])
        {
            pointer = tp + i;
        }
    }
    return pointer;
}

void ChangeClass::tie_object(MainElement& temp) // Связывает структуру с объектом класса
{
    MainElement copy = temp;
    char* tp = (char*)&temp;
    char* cp = (char*)&copy;
    int size = sizeof(temp);
    int longintsize = sizeof(long int);
    int intsize = sizeof(int);
    int doublesize = sizeof(double);
    int floatsize = sizeof(float);
    
    // Находим указатели на ai, bi, ci
    copy.edit_ai(1);
    p_ai = (long int*)changed_byte(tp, cp, size);
    copy.edit_ai(0);
    copy.edit_bi(1);
    p_bi = (long int*)changed_byte(tp, cp, size);
    copy.edit_bi(0);
    copy.edit_ci(1);
    p_ci = (long int*)changed_byte(tp, cp, size);
    copy.edit_ci(0);
    
    // Находим указатели на ad, bd, cd
    copy.edit_ad(1);
    p_ad = (double*)(changed_byte(tp, cp, size) - doublesize + 1);
    copy.edit_ad(0);
    copy.edit_bd(1);
    p_bd = (double*)(changed_byte(tp, cp, size) - doublesize + 1);
    copy.edit_bd(0);
    copy.edit_cd(1);
    p_cd = (double*)(changed_byte(tp, cp, size) - doublesize + 1);
    copy.edit_cd(0);
    
    // Находим указатели на array1, array2, array3
    copy.edit_array1(0, 1);
    array1 = (int*)changed_byte(tp, cp, size);
    copy.edit_array1(0, 0);
    copy.edit_array2(0, 1);
    array2 = changed_byte(tp, cp, size);
    copy.edit_array2(0, 0);
    copy.edit_array3(0, 1);
    array3 = (float*)(changed_byte(tp, cp, size) - floatsize + 1);
    copy.edit_array3(0, 0);
    
    // Находим указатели на vec1, vec2, vec3
    copy.edit_vec1(0, 1);
    vec1 = (double*)(changed_byte(tp, cp, size) - doublesize + 1);
    copy.edit_vec1(0, 0);
    copy.edit_vec2(0, 1);
    vec2 = (float*)(changed_byte(tp, cp, size) - floatsize + 1);
    copy.edit_vec2(0, 0);
    copy.edit_vec3(0, true);
    vec3 = (bool*)changed_byte(tp, cp, size);
    copy.edit_vec3(0, false);
}

ChangeClass::ChangeClass(MainElement& temp)
{
    tie_object(temp);
}

////////// Методы структуры, меняющие значения скрытых полей класса \\\\\\\\\\

void ChangeClass::edit_ai(long int x)
{
    *(p_ai) = x;
}

void ChangeClass::edit_bi(long int x)
{
    *(p_bi) = x;
}

void ChangeClass::edit_ci(long int x)
{
    *(p_ci) = x;
}

void ChangeClass::edit_ad(double x)
{
    *(p_ad) = x;
}

void ChangeClass::edit_bd(double x)
{
    *(p_bd) = x;
}

void ChangeClass::edit_cd(double x)
{
    *(p_cd) = x;
}

void ChangeClass::edit_vec1(int i, double x)
{
    vec1[i] = x;
}

void ChangeClass::edit_vec2(int i, float x)
{
    vec2[i] = x;
}

void ChangeClass::edit_vec3(int i, bool x)
{
    vec3[i] = x;
}

void ChangeClass::edit_array1(int i, int x)
{
    array1[i] = x;
}

void ChangeClass::edit_array2(int i, char x)
{
    array2[i] = x;
}

void ChangeClass::edit_array3(int i, float x)
{
    array3[i] = x;
}

////////// end \\\\\\\\\\

void fill_class(MainElement& temp)  // Заполняет скрытые поля класса MainElement
{
    ChangeClass change_temp(temp);
    
    change_temp.edit_ai(1001);
    change_temp.edit_bi(-81001);
    change_temp.edit_ci(9081001);
    change_temp.edit_ad(678.98);
    change_temp.edit_bd(-68.98);
    change_temp.edit_cd(98988.98);
    for (int i = 0; i < arr_num; ++i)   // Заполняем array1, array2, array3
    {
        change_temp.edit_array1(i, 7899 - i);
        change_temp.edit_array2(i, i + 60);
        change_temp.edit_array3(i, (float) 1 / (i + 1));
    }
    for (int i = 0; i < vec_num; ++i)   // Заполняем vec1, vec2, vec3
    {
        change_temp.edit_vec1(i, (double) (i * i) / (i + 100));
        change_temp.edit_vec2(i, (float) -(i * i * i) / (i + 100));
        change_temp.edit_vec3(i, i % 2 == 1);
    }
}