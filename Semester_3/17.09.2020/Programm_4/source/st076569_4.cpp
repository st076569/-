////////// managerlib ////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 28.09.2020                                                    //
// Задача   : Сделать диспетчер задач с применением идеологии "RAII". Ко    //
//            всем методам подписать тип гарантии.                          //
//////////////////////////////////////////////////////////////////////////////

#include "managerlib.h"

int main()
{
    int error = 0;
    int size  = 20;
    bat::TaskTime* testArray = 0;
    
    std::cout.setf(std::ios::fixed);
    srand(time(0));
    std::cout << "\n/////////////// Begin //////////////////////////\n";
    bat::createTasksArray(&testArray, size, error);
    bat::printTaskArray(testArray, size);
    std::cout << "/////////////// Dispatcher task sequence ///////\n";
    std::cout << " (" << std::setw(3) << "i";
    std::cout << ") :: [Task Number] <Execution Time>\n";
    std::cout << "////////////////////////////////////////////////\n";
    processTasks(testArray, size, error);
    std::cerr << "\nError status : " << error << "\n";
    std::cout << "\n//////////////// End ///////////////////////////\n";
    
    return 0;
}