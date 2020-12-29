////////// queuelib //////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 27.09.2020                                                    //
// Задача   : Сделать стрессоустойчивую очередь с применением throw,        //
//            try, catch.                                                   //
// Описание : Здесь приведено определение всех составляющих класса          //
//            "очередь".                                                    //
//////////////////////////////////////////////////////////////////////////////

#include "queuelib.h"

////////// struct Element ////////////////////////////////////////////////
// Дочерний класс, унаследованный от "std::exception". Содежит в себе   //
// код ошибки "errCode".                                                //
//////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::QueueException::QueueException()
{
    errCode_ = 0;
}

// (2) Конструктор
bat::QueueException::QueueException(const int& newErrCode)
{
    errCode_ = newErrCode;
}

// (3) Конструктор копирования
bat::QueueException::QueueException(const QueueException& exception)
{
    *this = exception;
}

// (4) Перегрузка оператора присваивания
bat::QueueException& bat::QueueException::operator=(const QueueException& 
                                               exception)
{
    if (&exception != this)
    {
        errCode_ = exception.errCode_;
    }
    return *this;
}

// (5) Возвращает код ошибки
int bat::QueueException::error() const
{
    return errCode_;
}

////////// struct Element ////////////////////////////////////////////////////
// Это структура, которая является элементом очереди.                       //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::Element::Element()
{
    content = 0;
    next    = 0;
}

// (2) Конструктор копирования
bat::Element::Element(const bat::Element& element)
{
    *this = element;
}

// (3) Перегрузка оператора присваивания
bat::Element& bat::Element::operator=(const bat::Element& element)
{
    if (&element != this)
    {
        content = element.content;
        next    = element.next;
    }
    return *this;
}

// (4) Обнуляет поля
void bat::Element::clear()
{
    content = 0;
    next    = 0;
}

// (5) Деструктор
bat::Element::~Element()
{
    clear();
}

////////// class Queue ///////////////////////////////////////////////////////
// Класс, объектом которого является структура данных "очередь".            //
//////////////////////////////////////////////////////////////////////////////

// (1) Конструктор
bat::Queue::Queue()
{
    end_ = 0;
    beg_ = 0;
}

// (2) Конструктор копирования
bat::Queue::Queue(const bat::Queue& queue)
{
    *this = queue;
}

// (3) Перегрузка оператора присваивания
bat::Queue& bat::Queue::operator=(const bat::Queue& queue)
{
    if (&queue != this)
    {
        clear();
        
        bat::Element*  currentPos = queue.end_;
        bat::Element** temp       = &end_;
        
        while (currentPos != 0)
        {
            *temp = new Element;
            beg_ = *temp;
            temp = &((*temp) -> next);
            currentPos = currentPos -> next;
        }
    }
    return *this;
}

// (4) Возвращает количество элементов в очереди
int bat::Queue::size() const
{
    int           length     = 0;
    bat::Element* currentPos = end_;
    // Проходим по очереди
    while (currentPos != 0)
    {
        ++length;
        currentPos = currentPos -> next;
    }
    return length;
}

// (5) Позволяет увидеть последний элемент без извлечения
const bat::ContentType& bat::Queue::peek() const
{
    // Проверяем наличие хотя бы одного элемента в очереди
    if (beg_ == 0)
    {
        throw QueueException(1);
    }
    // Если есть элемент, то показываем
    return beg_ -> content;
}

// (6) Извлекает последний записанный элемент
bat::ContentType bat::Queue::pop()
{
    bat::ContentType copy = 0;
    // Проверяем наличие хотя бы одного элемента в очереди
    if (beg_ == 0)
    {
        throw QueueException(2);
    }
    // Если есть элемент, то извлекаем
    bat::Element* currentPos = end_;
    while (currentPos -> next != beg_ && currentPos -> next != 0)
    {
        currentPos = currentPos -> next;
    }
    if (currentPos -> next == 0)
    {
        copy = currentPos -> content;
        end_ = 0;
        beg_ = 0;
        delete currentPos;
    }
    else
    if (currentPos -> next == beg_)
    {
        copy = currentPos -> next -> content;
        currentPos -> next = 0;
        delete beg_;
        beg_ = currentPos;
    }
    return copy;
}

// (7) Добавляет в конец очереди новый элемент
void bat::Queue::pushBack(const bat::ContentType& newElement)
{
    bat::Element* oldEnd = end_;
    // Выделяем память
    end_ = new Element;
    // Если память выделена, то присваиваем
    end_ -> content = newElement;
    end_ -> next    = oldEnd;
    if (beg_ == 0)
    {
        beg_ = end_;
    }
}

// (8) Извлекает "number" элементов из очереди
void bat::Queue::multiPop(const int& number)
{
    int length = size();
    // Проверяем корректность входного аргумента
    if (length < number)
    {
        throw QueueException(2);
    }
    // Если значение аргумента корректно, то удаляем 
    if (length == number)
    {
        deleteFromPointer(end_);
        end_ = 0;
        beg_ = 0;
    }
    else
    {
        bat::Element* currentPos = end_;
        for (int i = 0; i < length - number - 1; ++i)
        {
            currentPos = currentPos -> next;
        }
        deleteFromPointer(currentPos -> next);
        currentPos -> next = 0;
        beg_ = currentPos;
    }
}

// (9) Освобождает динамически выделенную память
void bat::Queue::clear()
{
    deleteFromPointer(end_);
    end_ = 0;
    beg_ = 0;
}

// (10) Деструктор
bat::Queue::~Queue()
{
    clear();
}

// (11) Удаляет элементы очереди, начиная с "start"
void bat::Queue::deleteFromPointer(const Element* start)
{
    if (start != 0)
    {
        deleteFromPointer(start -> next);
        delete start;
    }
}
