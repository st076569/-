#ifndef SWAPLIB_H
#define SWAPLIB_H

////////// swaplib ///////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 25.10.2020                                                    //
// Задача   : Написать Swap, меняющий константные объекты одного размера    //
//            местами.                                                      //
//////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>
#include <iostream>

namespace bat
{
    ////////// class SwapClass1 //////////////////////////////////////////////
    // Класс, объект которого будем менять с объектом другого класса        //
    // "SwapClass2".                                                        //
    //////////////////////////////////////////////////////////////////////////
    
    class SwapClass1
    {
        private :
            
            float     float1;
            double    double1;
            int       int1;
            long int* ptr1;
            
        public :
            
            // (1) Конструктор
            SwapClass1();
            
            // (2) Конструктор
            SwapClass1(float v1, double v2, int v3, long int* v4);
            
            // (3) Конструктор копирования
            SwapClass1(const SwapClass1& swapClass);
            
            // (4) Перегрузка оператора присваивания
            SwapClass1& operator=(const SwapClass1& swapClass);
            
            // (5) Выводит содержимое полей на экран
            void getContent() const;
            
            // (6) Обнуляет поля
            void clear();
            
            // (7) Деструктор
            ~SwapClass1();
    };
    
    ////////// class SwapClass2 //////////////////////////////////////////////
    // Класс, объект которого будем менять с объектом другого класса        //
    // "SwapClass1".                                                        //
    //////////////////////////////////////////////////////////////////////////
    
    class SwapClass2
    {
        private :
            
            float     float2;
            double    double2;
            int       int2;
            long int* ptr2;
            
        public :
            
            // (1) Конструктор
            SwapClass2();
            
            // (2) Конструктор
            SwapClass2(float v1, double v2, int v3, long int* v4);
            
            // (3) Конструктор копирования
            SwapClass2(const SwapClass2& swapClass);
            
            // (4) Перегрузка оператора присваивания
            SwapClass2& operator=(const SwapClass2& swapClass);
            
            // (5) Выводит содержимое полей на экран
            void getContent() const;
            
            // (6) Обнуляет поля
            void clear();
            
            // (7) Деструктор
            ~SwapClass2();
    };
    
    ////////// void Swap /////////////////////////////////////////////////////
    // Процедура, которая обменивает два константных объекта одного размера //
    // местами. (Является шаблонной)                                        //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename T1, typename T2>
    
    void swap(const T1& object1, const T2& object2)
    {
        T1 tempT1 = object1;
        const_cast<T1&> (object1) = reinterpret_cast<T1&> (
                                    const_cast<T2&> (object2));
        const_cast<T2&> (object2) = reinterpret_cast<T2&> (tempT1);
    }
}

#endif
