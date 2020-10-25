////////// swaplib ///////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 25.10.2020                                                    //
// Задача   : Написать Swap, меняющий константные объекты одного размера    //
//            местами.                                                      //
//////////////////////////////////////////////////////////////////////////////

#include "swaplib.h"

////////// class SwapClass1 //////////////////////////////////////////////////
// Класс, объект которого будем менять с объектом другого класса            //
// "SwapClass2".                                                            //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::SwapClass1::SwapClass1()
{
    clear();
}

// (2) Конструктор
bat::SwapClass1::SwapClass1(float v1, double v2, int v3, long int* v4)
{
    float1  = v1;
    double1 = v2;
    int1    = v3;
    ptr1    = v4;
}

// (3) Конструктор копирования
bat::SwapClass1::SwapClass1(const bat::SwapClass1& swapClass)
{
    *this = swapClass;
}

// (4) Перегрузка оператора присваивания
bat::SwapClass1& bat::SwapClass1::operator=(const bat::SwapClass1& swapClass)
{
    if (this != &swapClass)
    {
        float1  = swapClass.float1;
        double1 = swapClass.double1;
        int1    = swapClass.int1;
        ptr1    = swapClass.ptr1;
    }
    return *this;
}

// (5) Выводит содержимое полей на экран
void bat::SwapClass1::getContent() const
{
    std::cout << '\n';
    std::cout << "//////////////////// Content1 ////////////////////" << '\n';
    std::cout << "// 1) float1  : " << float1 << '\n';
    std::cout << "// 2) double1 : " << double1 << '\n';
    std::cout << "// 3) int1    : " << int1 << '\n';
    std::cout << "// 4) ptr1    : " << ptr1 << '\n';
    std::cout << "//////////////////////////////////////////////////" << '\n';
}

// (6) Обнуляет поля
void bat::SwapClass1::clear()
{
    float1  = 0;
    double1 = 0;
    int1    = 0;
    ptr1    = 0;
}

// (7) Деструктор
bat::SwapClass1::~SwapClass1()
{
    clear();
}

////////// class SwapClass2 //////////////////////////////////////////////////
// Класс, объект которого будем менять с объектом другого класса            //
// "SwapClass1".                                                            //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::SwapClass2::SwapClass2()
{
    clear();
}

// (2) Конструктор
bat::SwapClass2::SwapClass2(float v1, double v2, int v3, long int* v4)
{
    float2  = v1;
    double2 = v2;
    int2    = v3;
    ptr2    = v4;
}

// (3) Конструктор копирования
bat::SwapClass2::SwapClass2(const bat::SwapClass2& swapClass)
{
    *this = swapClass;
}

// (4) Перегрузка оператора присваивания
bat::SwapClass2& bat::SwapClass2::operator=(const SwapClass2& swapClass)
{
    if (this != &swapClass)
    {
        float2  = swapClass.float2;
        double2 = swapClass.double2;
        int2    = swapClass.int2;
        ptr2    = swapClass.ptr2;
    }
    return *this;
}

// (5) Выводит содержимое полей на экран
void bat::SwapClass2::getContent() const
{
    std::cout << '\n';
    std::cout << "//////////////////// Content2 ////////////////////" << '\n';
    std::cout << "// 1) float2  : " << float2 << '\n';
    std::cout << "// 2) double2 : " << double2 << '\n';
    std::cout << "// 3) int2    : " << int2 << '\n';
    std::cout << "// 4) ptr2    : " << ptr2 << '\n';
    std::cout << "//////////////////////////////////////////////////" << '\n';
}

// (6) Обнуляет поля
void bat::SwapClass2::clear()
{
    float2  = 0;
    double2 = 0;
    int2    = 0;
    ptr2    = 0;
}

// (7) Деструктор
bat::SwapClass2::~SwapClass2()
{
    clear();
}
