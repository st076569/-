/*
 (10 баллов)
 Реализовать Stack целых чисел с операцией многократного извлечения (multipop).
*/

#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    
    Stack A(5);
    
    for (int i = 0; i < 37; i++)    // заполнение
    {
        A.push(i);
    }
    
    for (int i = 0; i < 10; i++)    // опустошение частичное
    {
        cout << A.pop() << ", ";
    }
    
    cout << endl;
    A.multipop(20);                 // извлечение multipop
    
    for (int i = 0; i < 8; i++)
    {
        cout << A.pop() << ", ";    // извлечение всех элементов
    }
    
    cout << endl;
    A.pop();                        // ошибка извлечения
    
    return 0;
}
