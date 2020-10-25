////////// iolib /////////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 25.10.2020                                                    //
// Задача   : Написать функции записи чтения массива объектов в файл        //
//            произвольного типа и одинакового размера.                     //
//////////////////////////////////////////////////////////////////////////////

#include "iolib.h"

////////// class InputClass //////////////////////////////////////////////////
// Класс, объект которого будем записывать в файл.                          //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::InputClass::InputClass()
{
    clear();
}

// (2) Конструктор
bat::InputClass::InputClass(float v1, double v2, int v3, long int* v4)
{
    initialize(v1, v2, v3, v4);
}

// (3) Конструктор копирования
bat::InputClass::InputClass(const bat::InputClass& inputClass)
{
    *this = inputClass;
}

// (4) Перегрузка оператора присваивания
bat::InputClass& bat::InputClass::operator=(const bat::InputClass& inputClass)
{
    if (this != &inputClass)
    {
        float1  = inputClass.float1;
        double1 = inputClass.double1;
        int1    = inputClass.int1;
        ptr1    = inputClass.ptr1;
    }
    return *this;
}

// (5) Инициализирует объект класса значениями "v1...v4"
void bat::InputClass::initialize(float v1, double v2, int v3, long int* v4)
{
    float1  = v1;
    double1 = v2;
    int1    = v3;
    ptr1    = v4;
}

// (6) Выводит содержимое полей на экран
void bat::InputClass::getContent() const
{
    std::cout << "( " << std::setw(bat::SETW_SIZE) << float1;
    std::cout << " | " << std::setw(bat::SETW_SIZE) << double1;
    std::cout << " | " << std::setw(bat::SETW_SIZE) << int1;
    std::cout << " | " << std::setw(bat::SETW_SIZE) << ptr1;
    std::cout << " )";
}

// (7) Обнуляет поля
void bat::InputClass::clear()
{
    float1  = 0;
    double1 = 0;
    int1    = 0;
    ptr1    = 0;
}

// (8) Деструктор
bat::InputClass::~InputClass()
{
    clear();
}

////////// class OutputClass /////////////////////////////////////////////////
// Класс, объект которого будем читать из файла.                            //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::OutputClass::OutputClass()
{
    clear();
}

// (2) Конструктор
bat::OutputClass::OutputClass(float v1, double v2, int v3, long int* v4)
{
    initialize(v1, v2, v3, v4);
}

// (3) Конструктор копирования
bat::OutputClass::OutputClass(const bat::OutputClass& outputClass)
{
    *this = outputClass;
}

// (4) Перегрузка оператора присваивания
bat::OutputClass& bat::OutputClass::operator=(const OutputClass& outputClass)
{
    if (this != &outputClass)
    {
        float2  = outputClass.float2;
        double2 = outputClass.double2;
        int2    = outputClass.int2;
        ptr2    = outputClass.ptr2;
    }
    return *this;
}

// (5) Инициализирует объект класса значениями "v1...v4"
void bat::OutputClass::initialize(float v1, double v2, int v3, long int* v4)
{
    float2  = v1;
    double2 = v2;
    int2    = v3;
    ptr2    = v4;
}

// (6) Выводит содержимое полей на экран
void bat::OutputClass::getContent() const
{
    std::cout << "( " << std::setw(bat::SETW_SIZE) << float2;
    std::cout << " | " << std::setw(bat::SETW_SIZE) << double2;
    std::cout << " | " << std::setw(bat::SETW_SIZE) << int2;
    std::cout << " | " << std::setw(bat::SETW_SIZE) << ptr2;
    std::cout << " )";
}

// (7) Обнуляет поля
void bat::OutputClass::clear()
{
    float2  = 0;
    double2 = 0;
    int2    = 0;
    ptr2    = 0;
}

// (8) Деструктор
bat::OutputClass::~OutputClass()
{
    clear();
}

////////// void write ////////////////////////////////////////////////////////
// Процедура, которая записывает в файл "path" ровно "size" элементов       //
// массива "output".                                                        //
//////////////////////////////////////////////////////////////////////////////

void bat::write(bat::OutputClass* output, const int& size, const char* path)
{
    std::ofstream outf;
    outf.open(path, std::ios::binary);
    
    if (outf)
    {
        for (int i = 0; i < size && !outf.fail(); ++i)
        {
            outf.write(reinterpret_cast<char*> (&output[i]), 
                       sizeof(bat::OutputClass));
        }
        if (outf.fail())
        {
            outf.clear();
        }
        outf.close();
    }
}

////////// void read /////////////////////////////////////////////////////////
// Процедура, которая читает из файла "path" ровно "size" элементов         //
// массива "input".                                                         //
//////////////////////////////////////////////////////////////////////////////

void bat::read(bat::InputClass* input, const int& size, const char* path)
{
    std::ifstream inf;
    inf.open(path, std::ios::binary);
    
    if (inf)
    {
        for (int i = 0; i < size && !inf.fail(); ++i)
        {
            inf.read(reinterpret_cast<char*> (&input[i]), 
                       sizeof(bat::InputClass));
        }
        if (inf.fail())
        {
            inf.clear();
        }
        inf.close();
    }
}

////////// void showOutputArray //////////////////////////////////////////////
// Выводит на экран массив объектов "output".                               //
//////////////////////////////////////////////////////////////////////////////

void bat::showOutputArray(bat::OutputClass* output, const int& size)
{
    std::cout << '\n' << "// Output Array" << '\n';
    
    for (int i = 0; i < size && output + i != 0; ++i)
    {
        std::cout << "//" << std::setw(bat::SETW_SIZE) << i << ") : ";
        output[i].getContent();
        std::cout << '\n';
    }
}

////////// void showInputArray ///////////////////////////////////////////////
// Выводит на экран массив объектов "input".                                //
//////////////////////////////////////////////////////////////////////////////

void bat::showInputArray(bat::InputClass* input, const int& size)
{
    std::cout << '\n' << "// Input Array" << '\n';
    
    for (int i = 0; i < size && input + i != 0; ++i)
    {
        std::cout << "//" << std::setw(bat::SETW_SIZE) << i << ") : ";
        input[i].getContent();
        std::cout << '\n';
    }
}

////////// void showInputArray ///////////////////////////////////////////////
// Заполняет массив объектов класса "OutputClass" значениями.               //
//////////////////////////////////////////////////////////////////////////////

void bat::fillOutputArray(bat::OutputClass* output, const int& size)
{
    if (output != 0 && size > 0)
    {
        for (int i = 0; i < size; ++i)
        {
            output[i].initialize(i, 2 * i, 3 * i, 
                                 reinterpret_cast<long int*> (i));
        }
    }
}