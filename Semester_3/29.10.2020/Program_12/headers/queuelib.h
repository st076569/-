#ifndef QUEUELIB_H
#define QUEUELIB_H

////////// st076569_12 ///////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 29.10.2020                                                      //
// Задача : Реализовать потокобезопасную очередь. С помощью такой очереди   //
//          написать эффективную программу, обрабатывающую в k потоках      //
//          N >> k задач, каждая из которых требует t1 времени на preparing //
//          и t2 на processing.                                             //
//////////////////////////////////////////////////////////////////////////////

#include <mutex>
#include <queue>

namespace bat
{
    ////////// class SafetyQueue /////////////////////////////////////////////
    // Этот класс описывает потокобезопасную очередь.                       //
    //////////////////////////////////////////////////////////////////////////
    
    template <class T>
    class SafetyQueue
    {
        private :
            
            std::queue<T> list_;    // Очередь
            std::mutex    mut_;     // Флаг безопасного доступа
            
        public :
            
            // (1) Конструктор
            SafetyQueue() = default;
            
            // (2) Конструктор копирования
            SafetyQueue(const SafetyQueue& newQueue) = delete;
            
            // (3) Перегрузка оператора присваивания
            SafetyQueue& operator=(const SafetyQueue& newQueue) = delete;
            
            // (4) Добавляет элемент
            void push(T newElement);
            
            // (5) Извлекает элемент
            T pop(bool& wasExtracted);
            
            // (6) Проверка на отсутствие элементов
            bool empty();
            
            // (7) Возвращает размер очереди
            int size();
            
            // (8) Деструктор
            ~SafetyQueue() = default;
    };
    
    // (4) Добавляет элемент
    template <class T>
    void SafetyQueue<T>::push(T newElement)
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        // Добавление элемента
        list_.push(newElement);
    }
    
    // (5) Извлекает элемент
    template <class T>
    T SafetyQueue<T>::pop(bool& wasExtracted)
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        // Возвращаемый объект
        T temp;
        
        // Извлекаем элемент из очереди, если возможно
        if (!list_.empty())
        {
            temp = list_.front();
            list_.pop();
            wasExtracted = true;
        }
        else
        {
            wasExtracted = false;
        }
        return temp;
    }
    
    // (6) Проверка на отсутствие элементов
    template <class T>
    bool SafetyQueue<T>::empty()
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        return list_.empty();
    }
    
    // (7) Возвращает размер очереди
    template <class T>
    int SafetyQueue<T>::size()
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        return list_.size();
    }
}

#endif