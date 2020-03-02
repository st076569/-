/*
 (10 баллов)
 С помощью <stack> из STL написать программу для
 проверки корректности скобочной последовательности.
 Используются скобки “{“, “}”, “(”, “)”
*/

#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

int main()
{
    bool haveWayOut = false;
    string str;
    message();
    
    while (!haveWayOut)
    {
        cout << " <> Write down sequence : ";
        cin >> str;
        
        if (str.length() == 1 && str[0] == 48)
        {
            haveWayOut = true;
            cout << " >> End" << endl;
        }
        else
        {
            checkSequence(str);
        }
    }
    
    return 0;
}