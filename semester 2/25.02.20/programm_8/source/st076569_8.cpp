/*
(10 баллов)
Создать структуру с ~8 полями. Экспериментально выяснить, 
как устроена укладка объекта такой структуры в памяти.
*/

#include "functions.h"

int main()
{
    cout << "<<<<<<<<<< Begin >>>>>>>>>>" << endl;
    check_bytes_positions();
    cout << "<<<<<<<<<< End >>>>>>>>>>" << endl;
    return 0;
}
