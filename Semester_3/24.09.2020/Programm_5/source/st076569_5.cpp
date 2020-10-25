////////// st076569_5 ////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 25.10.2020                                                    //
// Задача   : Написать Swap, меняющий константные объекты одного размера    //
//            местами.                                                      //
// Описание : Здесь демонстрируется работа процедуры "swap".                //
//////////////////////////////////////////////////////////////////////////////

#include "swaplib.h"

namespace bat
{
    long int SOME_INT1 = 10;
    long int SOME_INT2 = 20;
    
    const SwapClass1 object1(27.34, 45.17, 567, &SOME_INT1);
    const SwapClass2 object2(317.4, 987.675, 256, &SOME_INT2);
}

int main()
{
    std::cout << '\n';
    std::cout << "//////////////////// Start ///////////////////////" << '\n';
    
    // Состояние до "swap"
    std::cout << '\n' << "// Before" << '\n';
    bat::object1.getContent();
    bat::object2.getContent();
    
    // Производим операцию "swap"
    bat::swap(bat::object1, bat::object2);
    
    // Состояние после "swap"
    std::cout << '\n' << "// After" << '\n';
    bat::object1.getContent();
    bat::object2.getContent();
    
    std::cout << '\n';
    std::cout << "//////////////////// End /////////////////////////" << '\n';
    
    return 0;
}
