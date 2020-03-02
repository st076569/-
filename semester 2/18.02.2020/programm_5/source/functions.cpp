/*
 (10 баллов)
 С помощью <stack> из STL написать программу для
 проверки корректности скобочной последовательности.
 Используются скобки “{“, “}”, “(”, “)”
*/

#include <stack>
#include <iostream>
#include <string>

using namespace std;

int assignCode(char c)
{
    switch (c)
    {
        case '(':
            return 1;
            break;
        case ')':
            return -1;
            break;
        case '{':
            return 2;
            break;
        case '}':
            return -2;
            break;
        default:
            return c;
            break;
    }
}

void checkSequence(string s)
{
    stack <int> chain;
    int code = 0;
    
    for (int i = 0; i < s.length(); i++)
    {
        code = assignCode(s[i]);
        if (chain.size() != 0)
        {
            if (chain.top() + code == 0 && chain.top() > 0)
            {
                chain.pop();
            }
            else
            {
                chain.push(code);
            }
        }
        else
        {
            chain.push(code);
        }
    }
    
    if (chain.size() > 0 || s.empty())
    {
        cout << " >> Wrong!" << endl;
    }
    else
    {
        cout << " >> Correct!" << endl;
    }
}

void message()
{
    cout << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "| << Write '0' to exit >>                      |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "| >> Example :                                 |" << endl;
    cout << "| <> Write down sequence : {()}(){}{{(())}}    |" << endl;
    cout << "| >> Correct!                                  |" << endl;
    cout << "| <> Write down sequence : {()}({){}{{((}))}}  |" << endl;
    cout << "| >> Wrong!                                    |" << endl;
    cout << "| <> Write down sequence : )(                  |" << endl;
    cout << "| >> Wrong!                                    |" << endl;
    cout << "| <> Write down sequence : 0                   |" << endl;
    cout << "| >> End                                       |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << endl;
}