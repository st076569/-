/*
 (10 баллов)
 Реализовать Stack целых чисел с операцией многократного извлечения (multipop).
*/

#include <iostream>
#include "stack.h"

using namespace std;

Stack::Stack(int a)
{
    head = new Element;
    
    (*(head)).data = a;
    (*(head)).next = 0;
}

Stack::~Stack()
{
    Element* temp = 0;
    
    while (head != 0)
    {
        temp = (*(head)).next;
        delete head;
        head = temp;
    }
}

void Stack::push(int a)
{
    Element* temp = head;
    bool isErr = false;
    
    try
    {
        head = new Element;
    }
    catch(const bad_alloc& e)
    {
        cout << endl;
        cout << "Error: allocation failed" << endl;
        isErr = true;
    }
    
    if (!isErr)
    {
        (*(head)).data = a;
        (*(head)).next = temp;
    }
}

int Stack::pop()
{
    bool isErr = false;
    
    try
    {
        if (head == 0)
        {
            throw 1;
        }
    }
    catch(int)
    {
        cout << endl;
        cout << "Error: stack underflow" << endl;
        isErr = true;
    }
    
    if (!isErr)
    {
        int a = (*(head)).data;
        Element* temp = (*(head)).next;
        
        delete head;
        head = temp;
        return a;
    }
    else
    {
        return 0;
    }
}

void Stack::multipop(int k)
{
    Element* temp = head;
    int count = 0;
    
    while (temp != 0)
    {
        count++;
        temp = (*(temp)).next;
    }
    
    if (count >= k)
    {
        for (int i = 0; i < k; i++)
        {
            pop();
        }
    }
    else
    {
        cout << endl;
        cout << "Error: multipop can not extract items" << endl;
    }
}