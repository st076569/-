/*
(10 баллов)
Написать структуру(не менее 10 полей), и пару функций:
put_to_file(), get_from_file().
Программа должна быть записана в стиле С.
*/

#include <ctime>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "functions.h"

using namespace std;

int main()
{
    srand(time(0));
    MainElement a, b;
    
    element_init(a);
    cout << "+------------------------------------------+" << endl;
    cout << "<<<<<<<<<< To file >>>>>>>>>>" << endl;
    element_out(a);
    put_to_file("test.txt", a);
    
    get_from_file("test.txt", b);
    cout << "<<<<<<<<<< From file >>>>>>>>>>" << endl;
    element_out(b);
    
    cout << "Press 'Enter' to continue...";
    getchar();
    
    return 0;
}
