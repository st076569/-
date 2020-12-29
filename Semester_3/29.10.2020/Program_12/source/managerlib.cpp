////////// st076569_12 ///////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 29.10.2020                                                      //
// Задача : Реализовать потокобезопасную очередь. С помощью такой очереди   //
//          написать эффективную программу, обрабатывающую в k потоках      //
//          N >> k задач, каждая из которых требует t1 времени на preparing //
//          и t2 на processing.                                             //
//////////////////////////////////////////////////////////////////////////////

#include "managerlib.h"

using namespace bat;

////////// struct Task ///////////////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
Task::Task()
{
    clear();
}

// (4) Выводит информацию о задании на экран
void Task::print() const
{
    std::cout << "# ";
    std::cout << "[" << std::setw(4) << id << "] : ";
    std::cout << "(" << std::setw(6) << start << ") : ";
    std::cout << "(" << std::setw(6) << duration << ") : ";
    std::cout << "(" << isFinal << ")";
}

// (5) Обнуляет поля
void Task::clear()
{
    duration = 0;
    start    = 0;
    id       = 0;
    isFinal  = false;
}

////////// struct Container //////////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
Container::Container()
{
    step = 0;
}

////////// class Buffer //////////////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
Buffer::Buffer()
{
    startPoint_ = 0;
    step_       = 0;
}

// (4) Инициализировать массив задач
void Buffer::initialize()
{
    Real portion = 0;
    tasks_.resize(BUFFER_SIZE);
    
    // Инициализируем случайным образом
    for (int i = 0; i < tasks_.size(); ++i)
    {
        tasks_[i].id = i;
        portion = static_cast<Real> (10 + rand() % 91) / 100;
        tasks_[i].duration = portion * MAX_DURATION;
        portion = static_cast<Real> (10 + rand() % 91) / 100;
        
        if (i == tasks_.size() - 1)
        {
            tasks_[i].isFinal = true;
        }
        if (i == 0)
        {
            tasks_[i].start = portion * MAX_DELAY;
        }
        else
        {
            tasks_[i].start = tasks_[i - 1].start + portion * MAX_DELAY;
        }
    }
}

// (5) Зафиксировать точку отсчета времени
void Buffer::setStartPoint(Real start)
{
    startPoint_ = start;
}

// (6) Если пришла очередная задача
bool Buffer::haveTask() const
{
    if (step_ < tasks_.size())
    {
        return tasks_[step_].start < (time() - startPoint_);
    }
    else
    {
        return false;
    }
}

// (7) Пуст ли буфер?
bool Buffer::empty() const
{
    return step_ == tasks_.size();
}

// (8) Вернуть поступившую задачу
Task Buffer::getTask()
{
    return tasks_[step_++];
}

// (9) Возвращает счетчик в начало
void Buffer::back()
{
    step_ = 0;
}

// (10) Выводит информацию о заданиях на экран
void Buffer::print() const
{
    for (int i = 0; i < tasks_.size(); ++i)
    {
        std::cout << std::setw(4) << i << ") ";
        tasks_[i].print();
        std::cout << "\n";
    }
}

// (11) Обнуляет поля
void Buffer::clear()
{
    startPoint_ = 0;
    step_       = 0;
    tasks_.clear();
}

////////// void delay ////////////////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

void bat::delay(Real duration)
{
    Real start = time();
    
    // Задержка по времени на "duration"
    while (time() - start < duration)
    {
        // В пустую
    }
}

////////// Real time /////////////////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

Real bat::time()
{
    return static_cast<Real> (clock()) / CLOCKS_PER_SEC;
}

////////// void dataPreparation //////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

void bat::dataPreparation(Container& dataQueue, Buffer& taskSeq)
{
    // Пока есть задачи, добавляем их в очередь
    while (!taskSeq.empty())
    {
        while (taskSeq.haveTask())
        {
            dataQueue.dataList.push(taskSeq.getTask());
        }
    }
}

////////// void dataProcessing ///////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

void bat::dataProcessing(Container& dataQueue)
{
    bool haveExit     = false;
    bool wasExtracted = false;
    Task copy;
    
    // Пока в очереди не оказался только финальный элемент
    while (!haveExit)
    {
        // Извлекаем очередной элемент
        copy = dataQueue.dataList.pop(wasExtracted);
        
        // Если смогли извлечь
        if (wasExtracted)
        {
            // Если элемент последний, то завершаем, иначе обрабатываем
            if (copy.isFinal)
            {
                haveExit = true;
                dataQueue.dataList.push(copy);
            }
            else
            {
                delay(copy.duration);
                std::lock_guard<std::mutex> lg(dataQueue.printMut);
                std::cout << std::setw(4) << dataQueue.step << ") ";
                copy.print();
                std::cout << "\n";
                ++dataQueue.step;
            }
        }
    }
}

////////// void parallelManager //////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

void bat::parallelManager(Buffer& taskSeq)
{
    Container tempQueue;
    Real      begin = time();
    
    // Начало
    std::cout << "\nSolving sequence 'parallel'\n";
    
    // Выделяем пять потоков под обработку и один под запись данных в очередь
    std::thread process1(dataProcessing, std::ref(tempQueue));
    std::thread process2(dataProcessing, std::ref(tempQueue));
    std::thread process3(dataProcessing, std::ref(tempQueue));
    std::thread prepare(dataPreparation, std::ref(tempQueue), 
                        std::ref(taskSeq));
    
    // Ожидаем завершения работы
    process1.join();
    process2.join();
    process3.join();
    prepare.join();
    
    std::cout << "Total time : " << time() - begin << " sec\n";
}

////////// void consistentManager ////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

void bat::consistentManager(Buffer& taskSeq)
{
    Container tempQueue;
    Real      begin = time();
    
    // Начало
    std::cout << "\nSolving sequence 'consistent'\n";
    
    // Выделяем один поток под обработку и один под запись данных в очередь
    std::thread process(dataProcessing, std::ref(tempQueue));
    std::thread prepare(dataPreparation, std::ref(tempQueue), 
                        std::ref(taskSeq));
    
    // Ожидаем завершения работы
    process.join();
    prepare.join();
    
    std::cout << "Total time : " << time() - begin << " sec\n";
}

////////// void message //////////////////////////////////////////////////////
// Описание : managerlib.h                                                  //
//////////////////////////////////////////////////////////////////////////////

void bat::message()
{
    std::cout << "\nInformation\n";
    std::cout << "   i) # [id] : (start time) : (duration) : (is final)\n";
}