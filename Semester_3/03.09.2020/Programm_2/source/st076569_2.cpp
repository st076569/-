////////// RAID 5 ////////////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 10.09.2020                                                      //
// Задача : Решить задачу с помощью STL. Эффективно смоделировать RAID 5,   //
//          для k буферов размера n кБайт. Технология использует            //
//          контрольные суммы для восстановления данных в случае выхода из  //
//          строя одного жёсткого диска. Нужно проделать тоже самое, только //
//          на буферах (массивах фиксированной длины). В моделировании      //
//          нужно заполнить несколько буферов данных, по ним построить      //
//          буфер контрольных сумм. Затем выбрать случайным образом один из //
//          буферов, как исчезнувший. После восстановить исчезнувшие данные //
//          и сравнить восстановленные данные с настоящими.                 //
//////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include "raidlib.h"

namespace bat
{
    // Размер буфера потока ввода
    const int CIN_BUFFER_SIZE = 32767;
    
    // Читает переменную типа "int"
    void read_int(int& inputVar, bool& err)
    {
        bool haveExit = false;
        err = false;
        while (!err && !haveExit)
        {
            std::cin >> inputVar;
            if (std::cin.fail())
            {
                std::cin.clear();
                inputVar = 0;
                err = true;
            }
            else
            {
                haveExit = true;
            }
        }
        std::cin.ignore(CIN_BUFFER_SIZE, '\n');
    }
    
    // Процедура проверки "Raid5"
    void testRaid5()
    {
        bat::Raid5 raidArray;
        bool       haveExit     = false;
        bool       error        = false;
        int        bufferNumber = 0;
        int        bufferSize   = 0;
        int        crushNumber  = 0;
        
        // Читаем количество буферов "bufferNumber" в массиве
        while (!haveExit)
        {
            std::cout << " > Input number of buffers (2 < int < ";
            std::cout << bat::MAX_BUFFER_NUMBER << ") : ";
            read_int(bufferNumber, error);
            if (!error && bufferNumber > 2 && bufferNumber < bat::MAX_BUFFER_NUMBER)
            {
                haveExit = true;
            }
            else
            {
                if (error)
                {
                    std::cout << " > Error : Uncorrect input!\n";
                }
                else
                {
                    std::cout << " > Error : Range error!\n";
                }
            }
        }
        
        // Читаем размер буферов "bufferSize" в блоках
        haveExit = false;
        while (!haveExit)
        {
            std::cout << " > Input size of buffers (0 < int < ";
            std::cout << bat::MAX_BUFFER_SIZE << ")   : ";
            read_int(bufferSize, error);
            if (!error && bufferSize > 0 && bufferSize < bat::MAX_BUFFER_SIZE)
            {
                haveExit = true;
            }
            else
            {
                if (error)
                {
                    std::cout << " > Error : Uncorrect input!\n";
                }
                else
                {
                    std::cout << " > Error : Range error!\n";
                }
            }
        }
        
        // Создаем массив, случайно заполняем, выставляем контрольные суммы
        raidArray.resize(bufferNumber, bufferSize);
        raidArray.setRandomValues();
        raidArray.setControlSums();
        
        // Выводим на экран массив
        std::cout << "\n > Raid5 (Start condition) :";
        std::cout << "\n";
        raidArray.print();
        std::cout << "\n";
        
        // Читаем номер буфера, который будем уничтожать
        haveExit = false;
        while (!haveExit)
        {
            std::cout << " > Input crashed buffer number (0 <= int < ";
            std::cout << bufferNumber << ") : ";
            read_int(crushNumber, error);
            if (!error && crushNumber >= 0 && crushNumber < bufferNumber)
            {
                haveExit = true;
            }
            else
            {
                if (error)
                {
                    std::cout << " > Error : Uncorrect input!\n";
                }
                else
                {
                    std::cout << " > Error : Range error!\n";
                }
            }
        }
        
        // Уничтожаем буфер
        raidArray.crashBuffer(crushNumber);
        
        // Выводим массив с уничтоженнным буфером
        std::cout << "\n > Raid5 (Crashed) :";
        std::cout << "\n";
        raidArray.print();
        std::cout << "\n";
        
        // Восстанавливаем потерянные данные
        raidArray.recoverInformation();
        
        // Выводим на экран восстановленный массив
        std::cout << "\n > Raid5 (Recovered) :";
        std::cout << "\n";
        raidArray.print();
        std::cout << "\n <Correct ending>";
    }
}

int main()
{
    srand(time(0));
    bat::testRaid5();
    
    return 0;
}
