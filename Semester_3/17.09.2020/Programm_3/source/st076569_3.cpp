////////// st076569_3 ////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 27.09.2020                                                    //
// Задача   : Сделать стрессоустойчивую очередь с применением throw,        //
//            try, catch.                                                   //
// Описание : Здесь демонстрируется работа очереди.                         //
//////////////////////////////////////////////////////////////////////////////

#include "queuelib.h"

namespace bat
{
    // Выводит сообщение об ошибке
    void errMessage(const int& code)
    {
        switch (code)
        {
            case 0 :
                std::cerr << "Message : Have no errors!";
                break;
            case 1 :
                std::cerr << "Message : Attempt to call a nonexistent element!";
                break;
            case 2 :
                std::cerr << "Message : Attempt to extract a nonexistent element!";
                break;
            case 3 :
                std::cerr << "Message : Dynamic memory allocation error!";
                break;
            case 4 :
                std::cerr << "Message : Unknown error!";
                break;
        }
    }
    
    // Тестирует очередь
    void testingQueue()
    {
        bat::Queue testQueue;
        int        error = 0;
        
        std::cout << "\n////////// Begin //////////\n";
        // Производим тестовые операции
        try
        {
            // Вводим 10 элементов
            std::cout << "\n (1) Push 10 elements : ";
            for (int i = 0; i < 10 && error == 0; ++i)
            {
                testQueue.pushBack(static_cast<float> (i) / 10);
                std::cout << static_cast<float> (i) / 10 << ", ";
            }
            std::cout << "\n     <> Size   : " << testQueue.size();
            // Извлекаем 6 элементов
            std::cout << "\n\n (2) Pop(6)    : ";
            for (int i = 0; i < 6; ++i)
            {
                std::cout << testQueue.pop() << ", ";
            }
            std::cout << "\n     <> Size   : " << testQueue.size();
            // Вызываем без извлечения
            std::cout << "\n\n (3) Peek      : " << testQueue.peek();
            std::cout << "\n     <> Size   : " << testQueue.size();
            // Извлекаем все оставшиеся элементы
            std::cout << "\n\n (4) MultiPop(size) ";
            testQueue.multiPop(testQueue.size());
            std::cout << "\n     <> Size   : " << testQueue.size();
            std::cout << "\n\n (5) Peek(err) : " << testQueue.peek();
        }
        catch (const std::bad_alloc&)
        {
            error = 3;
        }
        catch (const bat::QueueException& exception)
        {
            error = exception.error();
        }
        catch (...)
        {
            error = 4;
        }
        // Выводим сообщение об ошибке
        std::cout << "\n\n > ";
        errMessage(error);
        std::cout << "\n";
        std::cout << "\n/////////// End ///////////\n\n";
    }
}

int main()
{
    bat::testingQueue();
    return 0;
}
