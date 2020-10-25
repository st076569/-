////////// st076569_6 ////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 25.10.2020                                                    //
// Задача   : Написать функции записи чтения массива объектов в файл        //
//            произвольного типа и одинакового размера.                     //
// Описание : Здесь демонстрируется работа процедур записи/чтения.          //
//////////////////////////////////////////////////////////////////////////////

#include "iolib.h"

int main()
{
    // Выделяем динамическую память под два массива
    bat::OutputClass* output = new bat::OutputClass[bat::ARRAY_SIZE];
    bat::InputClass* input = new bat::InputClass[bat::ARRAY_SIZE];
    
    // Объявление начала работы
    std::cout << '\n';
    std::cout << "//////////////////// Start ////////////////////" << '\n';
    
    // Заполняем данными массив, который запишем в файл "objectsArray.exe"
    bat::fillOutputArray(output, bat::ARRAY_SIZE);
    // Выводим на экран массив
    bat::showOutputArray(output, bat::ARRAY_SIZE);
    
    // Записыаем массив объектов класса "bat::OutputClass" в файл
    bat::write(output, bat::ARRAY_SIZE, "./objectsArray.exe");
    // Считываем массив объектов класса "bat::InputClass" из файла
    bat::read(input, bat::ARRAY_SIZE, "./objectsArray.exe");
    
    // Выводим на экран массив
    bat::showInputArray(input, bat::ARRAY_SIZE);
    
    // Объявление завершения работы
    std::cout << '\n';
    std::cout << "///////////////////// End /////////////////////" << '\n';
    
    // Освобождение памяти
    delete[] output;
    delete[] input;
    
    return 0;
}
