#ifndef STACKLIB_H
#define STACKLIB_H

////////// st076569_11 ///////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 22.10.2020                                                      //
// Задача : Реализовать безопасный параллельный стек через мьютексы.        //
//////////////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include <mutex>

namespace bat
{
    ////////// struct Element ////////////////////////////////////////////////
    // Это шаблон структуры, которая является элементом стека.              //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    struct Element
    {
        public :
            
            Element* next;      // Указатель на следующий элемент стека
            T        value;     // Содержимое элемента стека
            
        public :
            
            // (1) Конструктор
            Element();
            
            // (2) Конструктор копирования
            Element(const Element& newElement) = default;
            
            // (3) Перегрузка оператора присваивания
            Element<T>& operator=(const Element& newElement) = default;
            
            // (4) Деструктор
            ~Element() = default;
    };
    
    // (1) Конструктор
    template <typename T>
    Element<T>::Element()
    {
        next = nullptr;
    }
    
    ////////// class Stack ///////////////////////////////////////////////////
    // Это шаблон класса, который реализует цепную структуру данных - стек. //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename T>
    class Stack
    {
        private :
        
            Element<T>* head_;      // Указатель на верхний элемент стека
            int         size_;      // Количество элементов в стеке
            std::mutex  mut_;       // Флаг для безопасного обращения            
        
        public :
            
            // (1) Конструктор
            Stack();
            
            // (2) Конструктор копирования
            Stack(const Stack& newStack);
            
            // (3) Перегрузка оператора присваивания
            Stack<T>& operator=(const Stack& newStack);
            
            ////////// Методы доступа ////////////////////////////////////////
            
            // (4) Извлекает последний записанный элемент
            void pop();
            
            // (5) Доступ по ссылке к последнему элементу
            T top();
            
            // (6) Добавляет в стек элемент "newElement"
            void push(const T& newElement);
            
            ////////// Методы работы с размерами /////////////////////////////
            
            // (7) Возвращает количество элементов в стеке
            int size();
            
            // (8) Возвращает "true", если стек пуст, иначе "false"
            bool empty();
            
            ////////// Освобождение памяти ///////////////////////////////////
            
            // (9) Освобождает динамически выделенную память
            void clear();
            
            // (10) Деструктор
            ~Stack();
    };
    
    // (1) Конструктор
    template <typename T>
	Stack<T>::Stack()
    {
        head_ = nullptr;
        size_ = 0;
    }
    
    // (2) Конструктор копирования
    template <typename T>
	Stack<T>::Stack(const Stack& newStack)
    {
        *this = newStack;
    }
    
    // (3) Перегрузка оператора присваивания
    template <typename T>
	Stack<T>& Stack<T>::operator=(const Stack& newStack)
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        // Проверка на самоприсваивание
        if (this != &newStack)
        {
            try
            {
                T           tempValue;
                Element<T>* assignable = nullptr;
                Element<T>* copied     = nullptr;
                
                // Подгоняем по размеру
                while (size_ > newStack.size_)
                {
                    Element<T>* tempHead = head_;
                    head_ = tempHead->next;
                    --size_;
                    delete tempHead;
                }
                while (size_ < newStack.size_)
                {
                    // Добавляем новый элемент
                    Element<T>* tempHead = head_;
                    head_        = new Element<T>;
                    head_->value = tempValue;
                    head_->next  = tempHead;
                    ++size_;
                }
                
                // Инициализируем
                assignable = head_;
                copied     = newStack.head_;
                
                // Копируем значения "newStack" в стек
                while (assignable != nullptr && copied != nullptr)
                {
                    assignable->value = copied->value;
                    assignable        = assignable->next;
                    copied            = copied->next;
                }
            }
            catch (...)
            {
                // Предотвращаем выброс исключения
            }
        }
        return *this;
    }
    
    // (4) Извлекает последний записанный элемент
    template <typename T>
    void Stack<T>::pop()
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        // Проверка на пустоту
        if (size_ != 0)
        {
            Element<T>* tempHead = head_;
            head_ = tempHead->next;
            --size_;
            delete tempHead;
        }
    }
    
    // (5) Доступ по ссылке к последнему элементу
    template <typename T>
    T Stack<T>::top()
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        // Выбрасываем исключение, если нечего возвращать
        if (size_ == 0)
        {
            throw std::logic_error("Calling a non-existent element!");
        }
        return head_->value;
    }
    
    // (6) Добавляет в стек элемент "newElement"
    template <typename T>
    void Stack<T>::push(const T& newElement)
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        // Добавляем новый элемент
        Element<T>* tempHead = head_;
        head_        = new Element<T>;
        head_->value = newElement;
        head_->next  = tempHead;
        ++size_;
    }
    
    // (7) Возвращает количество элементов в стеке
    template <typename T>
    int Stack<T>::size()
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        return size_;
    }
    
    // (8) Возвращает "true", если стек пуст, иначе "false"
    template <typename T>
    bool Stack<T>::empty()
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        return size_ == 0;
    }
    
    // (9) Освобождает динамически выделенную память и обнуляет переменные
    template <typename T>
    void Stack<T>::clear()
    {
        // Перехват управления
        std::lock_guard<std::mutex> lg(mut_);
        
        // Удаляем все элементы
        while (size_ != 0)
        {
            Element<T>* tempHead = head_;
            head_ = tempHead->next;
            --size_;
            delete tempHead;
        }
    }
    
    // (10) Деструктор
    template <typename T>
	Stack<T>::~Stack()
    {
        clear();
    }
}
    
#endif