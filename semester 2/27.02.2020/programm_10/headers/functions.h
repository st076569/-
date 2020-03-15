/*
(20 баллов)
Реализовать структуру данных очередь с приоритетом с таймером
и с помощью такой структуры данных эмулировать работу
диспетчера задач.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct Objective
{
    unsigned int time_in;
    unsigned int waiting;
    unsigned int duration;
    unsigned int priority;
};

struct Element
{
    Objective task;
    Element* next;
};

struct QueuePriority
{
    Element* tail;
    Element* begin;
    
    void push_back(Objective obj);
    void push(Objective obj);
    void increase_priority();
    void pop();
    Objective* last();
    QueuePriority(Objective obj);
    QueuePriority();
    ~QueuePriority();
};

void read_Objectives(Objective* head, int size);
void read_information(Objective** head, int& obj_num);
void task_manager();

#endif
