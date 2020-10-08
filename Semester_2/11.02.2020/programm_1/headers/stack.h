/*
 (10 баллов)
 Реализовать Stack целых чисел с операцией многократного извлечения (multipop).
*/

#ifndef STACK_H
#define STACK_H

using namespace std;

struct Element
{
    int data;
    Element* next;
};

struct Stack
{
    Element* head;
    
    Stack(int a);
    ~Stack();
    void push(int a);
    void multipop(int k);
    int pop();
};

#endif
