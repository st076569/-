/*
(10 баллов)
Написать структуру(не менее 10 полей), и пару функций:
put_to_file(), get_from_file().
Программа должна быть записана в стиле С.
*/

#include <ctime>
#include "functions.h"

using namespace std;

int main()
{
    srand(time(0));    
    MainElement a, b;
    
    element_init(a);
    element_out(a);
    put_to_file("test.txt", a);
    get_from_file("test.txt", b);
    element_out(b);
    
    system("Pause");
    return 0;
}