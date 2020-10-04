////////// managerlib ////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 28.09.2020                                                    //
// Задача   : Сделать диспетчер задач с применением идеологии "RAII". Ко    //
//            всем методам подписать тип гарантии.                          //
// Описание : Здесь приведено определение всех составляющих классов         //
//            "задача" и "диспетчер задач".                                 //
//////////////////////////////////////////////////////////////////////////////

////////// Типы гарантий /////////////////////////////////////////////////////
// 0) Нет никаких гарантий [ННГ]                                            //
//      Нет никаких гарантий относительно того, что произойдет, если        //
//      возникнет исключение.                                               //
// 1) Гарантия отсутствия исключений / сбоев [ГОИС]                         //
//      Ни при каких обстоятельствах функция не будет генерировать          //
//      исключения. Функция всегда успешно выполняет свою работу.           //
// 2) Базовая гарантия [БГ]                                                 //
//      При возникновении любого исключения состояние программы             //
//      останется согласованным.                                            //
// 3) Строгая гарантия [СГ]                                                 //
//      Если при выполнении операции возникнет исключение, то               //
//      программа останется том же в состоянии, которое было до             //
//      начала выполнения операции.                                         //
//////////////////////////////////////////////////////////////////////////////

#include "managerlib.h"

////////// class Task ////////////////////////////////////////////////////////
// Класс, описывающий произвольную задачу.                                  //
//////////////////////////////////////////////////////////////////////////////
    
// (1) Конструктор [ГОИС]
bat::Task::Task() noexcept
{
    executionTime_ = 0;
    importance_    = 0;
    number_        = 0;
}

// (2) Конструктор [ГОИС]
bat::Task::Task(const int& newExTime, const int& newImportance) noexcept
{
    setExecutionTime(newExTime);
    setImportance(newImportance);
    setNumber(0);
}

// (3) Конструктор копирования [ГОИС]
bat::Task::Task(const bat::Task& task) noexcept
{
    *this = task;
}

// (4) Перегрузка оператора присваивания [ГОИС]
bat::Task& bat::Task::operator=(const bat::Task& task) noexcept
{
    if (this != &task)
    {
        executionTime_ = task.executionTime_;
        importance_    = task.importance_;
        number_        = task.number_;
    }
    return *this;
}

// (5) Установить время выполнения "executionTime_" [ГОИС]
void bat::Task::setExecutionTime(const int& newExTime) noexcept
{
    if (newExTime >= 0 && newExTime <= MAX_EXECUTION_TIME)
    {
        executionTime_ = newExTime;
    }
}

// (6) Установить важность "importance_" [ГОИС]
void bat::Task::setImportance(const int& newImportance) noexcept
{
    if (newImportance >= 0 && newImportance <= MAX_IMPORTANCE)
    {
        importance_ = newImportance;
    }
}

// (7) Установить уникальный номер "number_" [ГОИС]
void bat::Task::setNumber(const int& newNumber) noexcept
{
    if (newNumber >= 0)
    {
        number_ = newNumber;
    }
}

// (8) Вернуть время выполнения "executionTime_" [ГОИС]
int bat::Task::getExecutionTime() const noexcept
{
    return executionTime_;
}

// (9) Вернуть важность "importance_" [ГОИС]
int bat::Task::getImportance() const noexcept
{
    return importance_;
}

// (10) Вернуть уникальный номер "number_" [ГОИС]
int bat::Task::getNumber() const noexcept
{
    return number_;
}

// (11) Увеличить приоритет на "1" [ГОИС]
void bat::Task::addImportance() noexcept
{
    if (importance_ <= MAX_IMPORTANCE)
    {
        ++importance_;
    }
}

// (12) Обнуляет поля [ГОИС]
void bat::Task::clear() noexcept
{
    executionTime_ = 0;
    importance_    = 0;
    number_        = 0;
}

// (13) Деструктор [ГОИС]
bat::Task::~Task() noexcept
{
    clear();
}

////////// struct TaskTime ///////////////////////////////////////////////////
// Структура, содержащая задачу и время в тактах, когда она поступит в      //
// диспетчер после прихода предыдущей задачи.                               //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор [ГОИС]
bat::TaskTime::TaskTime() noexcept
{
    delay = 0;
}

// (2) Конструктор копирования [ГОИС]
bat::TaskTime::TaskTime(const bat::TaskTime& taskTime) noexcept
{
    *this = taskTime;
}

// (3) Перегрузка оператора присваивания [ГОИС]
bat::TaskTime& bat::TaskTime::operator=(const bat::TaskTime& taskTime) noexcept
{
    if (this != &taskTime)
    {
        task  = taskTime.task;
        delay = taskTime.delay;
    }
    return *this;
}

// (4) Обнуляет поля [ГОИС]
void bat::TaskTime::clear() noexcept
{
    task.clear();
    delay = 0;
}

// (5) Деструктор [ГОИС]
bat::TaskTime::~TaskTime() noexcept
{
    clear();
}

////////// class Manager /////////////////////////////////////////////////////
// Класс, описывающий менеджер задач, который принимает задачи с            //
// использованием очереди с приоритетом (с увеличением времени ожидания     //
// приоритет задачи увеличивается).                                         //
// Описание состояний:                                                      //
//  1) status_ = 0 : нет ошибок                                             //
//  2) status_ = 1 : допущена ошибка при выделении динамической памяти      //
//  3) status_ = 2 : было выброшено стандартное исключение                  //
//  4) status_ = 3 : было выброшено неизвестное исключение                  //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор [ГОИС]
bat::Manager::Manager() noexcept
{
    status_     = 0;
    cycleCount_ = 0;
    curNumber_  = INIT_TASK_NUMBER;
}

// (2) Конструктор копирования [ГОИС]
bat::Manager::Manager(const bat::Manager& manager) noexcept
{
    *this = manager;
}

// (3) Перегрузка оператора присваивания [ГОИС]
bat::Manager& bat::Manager::operator=(const bat::Manager& manager) noexcept
{
    if (this != &manager)
    {
        try
        {
            tasks_      = manager.tasks_;
            cycleCount_ = manager.cycleCount_;
            curNumber_  = manager.curNumber_;
            status_     = manager.status_;
        }
        catch (const std::bad_alloc&)
        {
            status_ = 1;
        }
        catch (const std::exception&)
        {
            status_ = 2;
        }
        catch (...)
        {
            status_ = 3;
        }
    }
    return *this;
}

// (4) Обсчитывает один такт [ГОИС]
void bat::Manager::process() noexcept
{
    try
    {
        if (status_ == 0)
        {
            if (cycleCount_ > 0)
            {
                --cycleCount_;
                for (int i = 0; i < tasks_.size(); ++i)
                {
                    tasks_[i].addImportance();
                }
            }
            else
            {
                if (tasks_.size() > 0)
                {
                    cycleCount_ = tasks_.back().getExecutionTime();
                    curNumber_  = tasks_.back().getNumber();
                    tasks_.pop_back();
                }
                else
                {
                    cycleCount_ = 0;
                    curNumber_  = INIT_TASK_NUMBER;
                }
            }
        }
    }
    catch (const std::bad_alloc&)
    {
        status_ = 1;
    }
    catch (const std::exception&)
    {
        status_ = 2;
    }
    catch (...)
    {
        status_ = 3;
    }
}

// (5) Добавляет задачу в очередь [ГОИС]
void bat::Manager::push(const bat::Task& task) noexcept
{
    bool haveInsertPos = false;
    int  position      = 0;
    
    try
    {
        if (status_ == 0)
        {
            while (!haveInsertPos && position < tasks_.size())
            {
                if (tasks_[position].getImportance() < task.getImportance())
                {
                    ++position;
                }
                else
                {
                    haveInsertPos = true;
                }
            }
            if (position == tasks_.size())
            {
                tasks_.push_back(task);
            }
            else
            {
                tasks_.insert(tasks_.begin() + position, task);
            }
        }
    }
    catch (const std::bad_alloc&)
    {
        status_ = 1;
    }
    catch (const std::exception&)
    {
        status_ = 2;
    }
    catch (...)
    {
        status_ = 3;
    }
}

// (6) Если статус ошибочный (!= 0) [ГОИС]
bool bat::Manager::fail() const noexcept
{
    return status_ != 0;
}

// (7) Возвращает код состояния менеджера [ГОИС]
int bat::Manager::getStatus() const noexcept
{
    return status_;
}

// (8) Устанавливает состояние менеджера [ГОИС]
void bat::Manager::setStatus(const int& newStatus) noexcept
{
    if (newStatus >= 0 && newStatus <= MAX_STATUS_NUMBER)
    {
        status_ = newStatus;
    }
}

// (9) Вернуть значение номера текущей задачи [ГОИС]
int bat::Manager::getCurrentTaskNum() const noexcept
{
    return curNumber_;
}

// (10) Возвращает "true", если очередь пуста [ГОИС]
bool bat::Manager::isEmpty() const noexcept
{
    return tasks_.empty();
}

// (11) Обнуляет поля [ГОИС]
void bat::Manager::clear() noexcept
{
    status_     = 0;
    cycleCount_ = 0;
    curNumber_  = INIT_TASK_NUMBER;
    tasks_.clear();
}

// (12) Деструктор [ГОИС]
bat::Manager::~Manager() noexcept
{
    clear();
}

////////// void createTasksArray /////////////////////////////////////////////
// Создает массив задач с учетом задержки поступления. Данные               //
// вводятся случайные.                                                      //
//////////////////////////////////////////////////////////////////////////////

void bat::createTasksArray(TaskTime** head, const int& size, int& error)
{
    try
    {
        if (size >= 0 && size <= MAX_TASK_NUMBER)
        {
            (*head) = new TaskTime[size];
            for (int i = 0; i < size; ++i)
            {
                (*head)[i].task.setImportance(rand() % MAX_IMPORTANCE);
                (*head)[i].task.setNumber(i);
                (*head)[i].task.setExecutionTime(
                                rand() % MAX_EXECUTION_TIME);
                (*head)[i].delay = rand() % MAX_DELAY;
            }
        }
    }
    catch (const std::bad_alloc&)
    {
        error = 1;
    }
    catch (const std::exception&)
    {
        error = 2;
    }
    catch (...)
    {
        error = 3;
    }
}

////////// void printTaskArray ///////////////////////////////////////////////
// Выводит на экран массив задач для диспетчера.                            //
//////////////////////////////////////////////////////////////////////////////

void bat::printTaskArray(TaskTime* head, const int& size)
{
    std::cout << "\n/////////////// Task Array /////////////////////\n";
    std::cout << " (" << std::setw(3) << "i";
    std::cout << ") :: [Task Number] <Execution Time> {Delay} ";
    std::cout << "/Importance/\n";
    std::cout << "////////////////////////////////////////////////\n";
    for (int i = 0; i < size; ++i)
    {
        std::cout << " (" << std::setw(3) << i << ") :: ";
        std::cout << "[" << std::setw(3);
        std::cout << head[i].task.getNumber() << "] : ";
        std::cout << "<" << std::setw(3); 
        std::cout << head[i].task.getExecutionTime() << "> : ";
        std::cout << "{" << std::setw(3) << head[i].delay << "} : ";
        std::cout << "/" << std::setw(3);
        std::cout << head[i].task.getImportance() << "/\n";
    }
    std::cout << "\n";
}

////////// void processTasks /////////////////////////////////////////////////
// Запускает диспетчер задач на созданном массиве.                          //
//////////////////////////////////////////////////////////////////////////////

void bat::processTasks(TaskTime* head, const int& size, int& error)
{
    if (error == 0)
    {
        Manager dispatcher;
        
        if (size >= 0 && size <= MAX_TASK_NUMBER)
        {
            bool haveExit   = false;
            bool haveError  = false;
            bool haveTask   = false;
            bool isEmpty    = false;
            int  count      = 0;
            int  taskCount  = 0;
            int  tempExTime = 0;
            int  tempNumber = INIT_TASK_NUMBER;
            int  taskNumber = 0;
            
            while (!haveExit)
            {
                if (taskNumber < size)
                {
                    if (head[taskNumber].delay == count)
                    {
                        dispatcher.push(head[taskNumber].task);
                        ++taskNumber;
                        count = 0;
                    }
                    else
                    {
                        ++count;
                    }
                }
                dispatcher.process();
                if (tempNumber != dispatcher.getCurrentTaskNum())
                {
                    std::cout << " (" << std::setw(3);
                    std::cout << taskCount << ") :: [" << std::setw(3);
                    std::cout << tempNumber << "] : <";
                    std::cout << std::setw(3) << tempExTime << ">\n";
                    ++taskCount;
                    tempNumber = dispatcher.getCurrentTaskNum();
                    tempExTime = 0;
                }
                else
                {
                    ++tempExTime;
                }
                haveError = dispatcher.fail();
                haveTask  = dispatcher.getCurrentTaskNum() != 
                            INIT_TASK_NUMBER;
                isEmpty   = taskNumber >= size && dispatcher.isEmpty();
                haveExit  = haveError || !haveTask && isEmpty;
            }
        }
        error = dispatcher.getStatus();
    }
}