////////// managerlib ////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 28.09.2020                                                    //
// Задача   : Взять старый код и распараллелить. При этом эффективность     //
//            должна вырасти.                                               //
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