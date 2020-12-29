////////// st076569_11 ///////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 22.10.2020                                                      //
// Задача : Реализовать безопасный параллельный стек через мьютексы.        //
//////////////////////////////////////////////////////////////////////////////

#include "stacklib.h"
#include <iostream>
#include <thread>

using namespace bat;

namespace bat
{
    // Количество элементов для записи из одного потока
    const int ELEMENT_NUMBER = 100000;
    
    ////////// void pushElements /////////////////////////////////////////////
    // Процедура добавления элементов в безопасный стек <int>.              //
    //////////////////////////////////////////////////////////////////////////
    
    void pushElements(Stack<int>& stack)
    {
        for (int i = 0; i < ELEMENT_NUMBER; ++i)
        {
            stack.push(i);
        }
    }
}

int main()
{
    // Потокобезопасный стек
    Stack<int> stack;
    
    // Запускаем в трех потоках процедуры добавления элементов
    std::thread t1(bat::pushElements, std::ref(stack));
    std::thread t2(bat::pushElements, std::ref(stack));
    std::thread t3(bat::pushElements, std::ref(stack));
    
    // Отлавливаем исключения
    try
    {
        t1.join();
        t2.join();
        t3.join();
    }
    catch (std::exception& ex)
    {
        std::cerr << "Error : " << ex.what();
    }
    catch (...)
    {
        std::cerr << "Error : " << "Unknown!";
    }
    
    // Выводим на экран размер стека (ни один элемент не потеряется)
    std::cout << "Total stack size : " << stack.size() << "\n";
    
    return 0;
}
