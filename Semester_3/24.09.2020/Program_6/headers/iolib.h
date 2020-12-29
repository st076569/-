#ifndef IOLIB_H
#define IOLIB_H

////////// iolib /////////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 25.10.2020                                                    //
// Задача   : Написать функции записи чтения массива объектов в файл        //
//            произвольного типа и одинакового размера.                     //
//////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace bat
{
    const int ARRAY_SIZE = 40;
    const int SETW_SIZE  = 6;
    
    ////////// class InputClass //////////////////////////////////////////////
    // Класс, объект которого будем читать из файла.                        //
    //////////////////////////////////////////////////////////////////////////
    
    class InputClass
    {
        private :
            
            float     float1;
            double    double1;
            int       int1;
            long int* ptr1;
            
        public :
            
            // (1) Конструктор
            InputClass();
            
            // (2) Конструктор
            InputClass(float v1, double v2, int v3, long int* v4);
            
            // (3) Конструктор копирования
            InputClass(const InputClass& inputClass);
            
            // (4) Перегрузка оператора присваивания
            InputClass& operator=(const InputClass& inputClass);
            
            // (5) Инициализирует объект класса значениями "v1...v4"
            void initialize(float v1, double v2, int v3, long int* v4);
            
            // (6) Выводит содержимое полей на экран
            void getContent() const;
            
            // (7) Обнуляет поля
            void clear();
            
            // (8) Деструктор
            ~InputClass();
    };
    
    ////////// class OutputClass /////////////////////////////////////////////
    // Класс, объект которого будем записывать в файл.                      //
    //////////////////////////////////////////////////////////////////////////
    
    class OutputClass
    {
        private :
            
            float     float2;
            double    double2;
            int       int2;
            long int* ptr2;
            
        public :
            
            // (1) Конструктор
            OutputClass();
            
            // (2) Конструктор
            OutputClass(float v1, double v2, int v3, long int* v4);
            
            // (3) Конструктор копирования
            OutputClass(const OutputClass& outputClass);
            
            // (4) Перегрузка оператора присваивания
            OutputClass& operator=(const OutputClass& outputClass);
            
            // (5) Инициализирует объект класса значениями "v1...v4"
            void initialize(float v1, double v2, int v3, long int* v4);
            
            // (6) Выводит содержимое полей на экран
            void getContent() const;
            
            // (7) Обнуляет поля
            void clear();
            
            // (8) Деструктор
            ~OutputClass();
    };
    
    ////////// void write ////////////////////////////////////////////////////
    // Процедура, которая записывает в файл "path" ровно "size" элементов   //
    // массива "output".                                                    //
    //////////////////////////////////////////////////////////////////////////
    
    void write(OutputClass* output, const int& size, const char* path);
    
    ////////// void read /////////////////////////////////////////////////////
    // Процедура, которая читает из файла "path" ровно "size" элементов     //
    // массива "input".                                                     //
    //////////////////////////////////////////////////////////////////////////
    
    void read(InputClass* input, const int& size, const char* path);
    
    ////////// void showOutputArray //////////////////////////////////////////
    // Выводит на экран массив объектов "output".                           //
    //////////////////////////////////////////////////////////////////////////
    
    void showOutputArray(OutputClass* output, const int& size);
    
    ////////// void showInputArray ///////////////////////////////////////////
    // Выводит на экран массив объектов "input".                            //
    //////////////////////////////////////////////////////////////////////////
    
    void showInputArray(InputClass* input, const int& size);
    
    ////////// void showInputArray ///////////////////////////////////////////
    // Заполняет массив объектов класса "OutputClass" значениями.           //
    //////////////////////////////////////////////////////////////////////////
    
    void fillOutputArray(OutputClass* output, const int& size);
}

#endif
