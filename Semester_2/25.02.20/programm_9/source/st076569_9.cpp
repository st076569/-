/*
(10 баллов)
Создать класс с ~8 закрытыми полями. 
Написать функции обращающиеся к этим закрытым полям.
*/

#include "functions.h"

int main()
{
    MainElement temp;
    cout << "+------------------------------------------+" << endl;
    cout << "|                  Before                  |" << endl;
    temp.print();       // Выводим неизмененный temp
    fill_class(temp);   // Меняем поля temp
    cout << "|                  After                   |" << endl;
    temp.print();       // Выводим измененный temp
    return 0;
}