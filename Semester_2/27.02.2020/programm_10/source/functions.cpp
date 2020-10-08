/*
(20 баллов)
Реализовать структуру данных очередь с приоритетом с таймером
и с помощью такой структуры данных эмулировать работу
диспетчера задач.
*/

#include "functions.h"

void QueuePriority::push_back(Objective obj)
{
    Element* temp = begin;
    begin = new Element;
    
    (*(begin)).task = obj;
    (*(begin)).next = temp;
    if ((*(begin)).next == NULL)
    {
        tail = begin;
    }
}

QueuePriority::QueuePriority(Objective obj)
{
    push_back(obj);
}

QueuePriority::QueuePriority()
{
    begin = NULL;
    tail = NULL;
}

Objective* QueuePriority::last()
{
    if (tail != NULL)
    {
        return &((*(tail)).task);
    }
    else
    {
        return NULL;
    }
}

void QueuePriority::pop()
{
    Element* previous = NULL;
    Element* actual = begin;
    
    if (tail != NULL)
    {
        while (actual != tail)
        {
            previous = actual;
            actual = (*(actual)).next;
        }
        delete tail;
        tail = previous;
        if (tail != NULL)
        {
            (*(tail)).next = NULL;
        }
        else
        {
            begin = NULL;
        }
    }
}

QueuePriority::~QueuePriority()
{
    while (tail != NULL)
    {
        pop();
    }
}

void QueuePriority::increase_priority()
{
    Element* actual = begin;
    while (actual != NULL)
    {
        ++(*(actual)).task.priority;
        ++(*(actual)).task.waiting;
        actual = (*(actual)).next;
    }
}

void QueuePriority::push(Objective obj)
{
    Element* previous = NULL;
    Element* actual = begin;
    
    while (actual != NULL && (*(actual)).task.priority < obj.priority)
    {
        previous = actual;
        actual = (*(actual)).next;
    }
    if (previous != NULL)
    {
        (*(previous)).next = new Element;
        previous = (*(previous)).next;
        (*(previous)).task = obj;
        (*(previous)).next = actual;
        if (actual == NULL)
        {
            tail = previous;
        }
    }
    else
    {
        push_back(obj);
    }
}

void read_Objectives(Objective* head, int size)
{
    cout << endl;
    cout << "+--------------------------------+" << endl;
    cout << "| Notification:                  |" << endl;
    cout << "| i) : time_in duration priority |" << endl;
    cout << "+--------------------------------+" << endl;
    cout << endl;
    cout << " > Write down objectives" << endl;
    
    Objective temp;
    int j = 0;
    
    for (int i = 0; i < size; ++i)
    {
        cout << " " << i + 1 << ") : ";
        cin >> temp.time_in >> temp.duration >> temp.priority;
        j = 0;
        while (j < i && head[j].time_in < temp.time_in)
        {
            ++j;
        }
        for (int k = i; k > j; --k)
        {
            head[k] = head[k - 1];
        }
        head[j] = temp;
    }
}

void read_information(Objective** head, int& obj_num)
{
    cout << "+---------------------+" << endl;
    cout << "|     Programm 10     |" << endl;
    cout << "+---------------------+" << endl << endl;
    while (obj_num < 1)
    {
        cout << " > Write down number of objectives : ";
        cin >> obj_num;
    }
    *(head) = new Objective[obj_num];
    read_Objectives(*(head), obj_num);
}

void task_manager()
{
    QueuePriority queue;
    Objective* list = NULL;
    int obj_num = 0, end_time = 0, i = 1;
    int sum = 0, array_num = 0, step = 0, queue_num = 0;
    
    read_information(&list, obj_num);
    step = list[0].time_in;
    end_time = step;
    cout << endl;
    cout << " > Sequence of completed objectives" << endl;
    while (queue_num != 0 || array_num < obj_num )
    {
        if (array_num < obj_num && step == list[array_num].time_in)
        {
            queue.push(list[array_num]);
            ++queue_num;
            ++array_num;
        }
        if (end_time <= step && queue_num != 0)
        {
            sum += (*(queue.last())).waiting;
            end_time = step + (*(queue.last())).duration;
            cout << " " << i << ") time_in : " << (*(queue.last())).time_in << endl;
            ++i;
            queue.pop();
            --queue_num;
        }
        ++step;
        queue.increase_priority();
    }
    cout << endl;
    cout << "Average waiting time : " << (float) sum / obj_num << endl;
    delete[] list;
}
