////////// st076569_1 ////////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 06.09.2020                                                      //
// Задача : Реализовать шаблон Stack с операцией многократного              //
//          извлечения (multipop) выписывающей промежуточные значения.      //
//          Сделать специализацию шаблона для логического типа.             //
//////////////////////////////////////////////////////////////////////////////

#include "stack.h"

namespace bat
{
    typedef bat::Stack<double> StackDouble;
    typedef bat::Stack<bool>   StackBool;
    
    // Записать в стек "stack" данные типа "double"
    void assignWithDouble(StackDouble& stack, const int& number)
    {
        stack.clear();
        for (int i = 0; i < number && stack.status() == 0; ++i)
        {
            stack.push((double) 127 / (double) (13 + i));
        }
    }

    // Записать в стек "stack" данные типа "bool"
    void assignWithBool(StackBool& stack, const int& number)
    {
        stack.clear();
        for (int i = 0; i < number && stack.status() == 0; ++i)
        {
            stack.push(i % 2 == 0);
        }
    }

    // Произвести проверку структуры "Stack"
    void checkWorkCorrection()
    {
        StackDouble stackDouble1;
        StackBool   stackBool1;
    
        bat::assignWithDouble(stackDouble1, 55);
        bat::assignWithBool(stackBool1, 273);
    
        std::cout << "\n >> Make random : stackDouble1, stackBool1.";
        std::cout << "\n\n > stackDouble1.size() : " << stackDouble1.size() << "\n";
        std::cout << "\n > stackBool1.size()   : " << stackBool1.size() << "\n";
        std::cout << "\n\n > stackDouble1 (multipop 13) : ";
        stackDouble1.multiplyPop(13);
        std::cout << "\n > stackBool1 (multipop 17)   : ";
        stackBool1.multiplyPop(17);
        std::cout << "\n\n > stackDouble1.size() : " << stackDouble1.size() << "\n";
        std::cout << "\n > stackBool1.size()   : " << stackBool1.size() << "\n";
    
        StackDouble stackDouble2(stackDouble1);
        StackBool   stackBool2(stackBool1);
    
        std::cout << "\n >> Assign : stackDouble1 --> stackDouble2, stackBool1 --> stackBool2.";
        std::cout << "\n\n > stackDouble2.size() : " << stackDouble2.size() << "\n";
        std::cout << "\n > stackBool2.size()   : " << stackBool2.size() << "\n";
        std::cout << "\n\n > stackDouble2 (multipop 15) : ";
        stackDouble2.multiplyPop(15);
        std::cout << "\n > stackBool1 (multipop 9)    : ";
        stackBool2.multiplyPop(9);
        std::cout << "\n\n > stackDouble2.size() : " << stackDouble2.size() << "\n";
        std::cout << "\n > stackBool2.size()   : " << stackBool2.size() << "\n";
    }
}

int main()
{
    bat::checkWorkCorrection();
    return 0;
}
