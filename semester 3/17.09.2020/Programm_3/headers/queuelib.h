#ifndef QUEUELIB_H
#define QUEUELIB_H

////////// queuelib //////////////////////////////////////////////////////////
// Автор    : Баталов Семен                                                 //
// Дата     : 27.09.2020                                                    //
// Задача   : Сделать стрессоустойчивую очередь с применением throw,        //
//            try, catch.                                                   //
// Описание : Здесь приведено объявление всех составляющих класса           //
//            "очередь".                                                    //
//////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <exception>

namespace bat
{
    // Тип данных, содержащихся в очереди
    typedef float ContentType;
    
    ////////// class QueueException //////////////////////////////////////////
    // Дочерний класс, унаследованный от "std::exception". Содежит в себе   //
    // код ошибки "errCode".                                                //
    //////////////////////////////////////////////////////////////////////////
    
    class QueueException : public std::exception
    {
        private :
            
            int errCode_;           // Код ошибки (0 - отсутствие ошибок)
            
        public :
            
            // (1) Конструктор
            QueueException();
            
            // (2) Конструктор
            QueueException(const int& newErrCode);
	    
            // (3) Конструктор копирования
            QueueException(const QueueException& exeption);
	    
            // (4) Перегрузка оператора присваивания
            QueueException& operator=(const QueueException& exeption);
            
            // (5) Возвращает код ошибки
            int error() const;
    };
    
    ////////// struct Element ////////////////////////////////////////////////
    // Это структура, которая является элементом очереди.                   //
    //////////////////////////////////////////////////////////////////////////
    
    struct Element
    {
        public :
            
            Element*    next;       // Указатель на следующий элемент
            ContentType content;    // Содержимое элемента стека
            
        public :
        
            // (1) Конструктор
            Element();
	    
            // (2) Конструктор копирования
            Element(const Element& element);
	    
            // (3) Перегрузка оператора присваивания
            Element& operator=(const Element& element);
            
            // (4) Обнуляет поля
            void clear();
	    
            // (5) Деструктор
            ~Element();
    };
    
    ////////// class Queue ///////////////////////////////////////////////////
    // Класс, объектом которого является структура данных "очередь".        //
    // Коды ошибок:                                                         //
    //  1) "0" - Отсутствие ошибки                                          //
    //  2) "1" - Попытка вызвать несуществующий элемент                     //
    //  3) "2" - Попытка извлечь несуществующий элемент                     //
    //////////////////////////////////////////////////////////////////////////
    
    class Queue
    {
        private :
        
            Element* end_;          // Указатель на последний элемент очереди
            Element* beg_;          // Указатель на первый элемент очереди
            
        public :
            
            // (1) Конструктор
            Queue();
            
            // (2) Конструктор копирования
            Queue(const Queue& queue);
            
            // (3) Перегрузка оператора присваивания
            Queue& operator=(const Queue& queue);
            
            // (4) Возвращает количество элементов в очереди
            int size() const;
            
            // (5) Позволяет увидеть последний элемент без извлечения
            const ContentType& peek() const;
            
            // (6) Извлекает последний записанный элемент
            ContentType pop();
            
            // (7) Добавляет в конец очереди новый элемент
            void pushBack(const ContentType& newElement);
            
            // (8) Извлекает "number" элементов из очереди
            void multiPop(const int& number);
            
            // (9) Освобождает динамически выделенную память
            void clear();
            
            // (10) Деструктор
            ~Queue();
            
        private :
            
            // (11) Удаляет элементы очереди, начиная с "start"
            void deleteFromPointer(const Element* start);
    };
}

#endif
