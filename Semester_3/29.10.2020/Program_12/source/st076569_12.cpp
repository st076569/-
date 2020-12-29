////////// st076569_12 ///////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 29.10.2020                                                      //
// Задача : Реализовать потокобезопасную очередь. С помощью такой очереди   //
//          написать эффективную программу, обрабатывающую в k потоках      //
//          N >> k задач, каждая из которых требует t1 времени на preparing //
//          и t2 на processing.                                             //
//////////////////////////////////////////////////////////////////////////////

#include "managerlib.h"

using namespace bat;

int main()
{
    Buffer testBuffer;
    srand(std::time(0));
    
    // Инструкция
    message();
    
    // Инициализируем буфер задач
    testBuffer.initialize();
    std::cout << "\nStart sequence\n";
    testBuffer.print();
    
    // Последовательное вычисление
    testBuffer.back();
    testBuffer.setStartPoint(time());
    consistentManager(testBuffer);
    
    // Параллельное вычисление
    testBuffer.back();
    testBuffer.setStartPoint(time());
    parallelManager(testBuffer);
    
    return 0;
}