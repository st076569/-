#ifndef STACK_H
#define STACK_H

////////// stack /////////////////////////////////////////////////////////////
// Автор  : Баталов Семен                                                   //
// Дата   : 06.09.2020                                                      //
// Задача : Реализовать шаблон Stack с операцией многократного              //
//          извлечения (multipop) выписывающей промежуточные значения.      //
//          Сделать специализацию шаблона для логического типа.             //
//////////////////////////////////////////////////////////////////////////////

#include <iostream>

namespace bat
{
    ////////// struct Element ////////////////////////////////////////////////
    // Это шаблон структуры, которая является элементом стека.              //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename A>
    
    struct Element
    {
        public :
            
            Element* next;          // Указатель на следующий элемент стека
            A        object;        // Содержимое элемента стека
            
        public :
        
            // (1) Конструктор
            Element();
	    
            // (2) Конструктор копирования
            Element(const Element& element);
	    
            // (3) Перегрузка оператора присваивания
            Element<A>& operator=(const Element& element);
	    
            // (4) Деструктор
            ~Element();
    };
    
    ////////// Element Methods ///////////////////////////////////////////////
    // Реализация методов структуры "Element".                              //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename A>
    
    // (1) Конструктор
    Element<A>::Element()
    {
        next = NULL;
    }
    
	template <typename A>
    
    // (2) Конструктор копирования
    Element<A>::Element(const Element& element)
    {
        *this = element;
    }
	
    template <typename A>
    
    // (3) Перегрузка оператора присваивания
    Element<A>& Element<A>::operator=(const Element& element)
    {
        if (this != &element)
        {
            next = element.next;
            object = element.object;
        }
        return *this;
    }
	
    template <typename A>
    
    // (4) Деструктор
    Element<A>::~Element()
    {
        next = NULL;
    }
    
    ////////// class Stack ///////////////////////////////////////////////////
    // Это шаблон класса, который реализует цепную структуру данных - стек. //
    // Описание ошибок:                                                     //
    //  1) status_ = 0 : Отсутствие ошибок.                                 //
    //  2) status_ = 1 : Ошибка выделения динамической памяти.              //
    //  3) status_ = 2 : Некорректный вызов метода.                         //
    //  4) status_ = 3 : В вызываемый метод передан аргумент с некорректным //
    //                   значением.                                         //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename B>
    
    class Stack
    {
        private :
        
            Element<B>*  head_;     // Указатель на последний элемент стека
            int          size_;     // Количество элементов в стеке
            int          status_;   // Текущее состояние стека (0 - нет ошибок)
        
        public :
        
            // (1) Конструктор
            Stack();
	    
            // (2) Конструктор копирования
            Stack(const Stack& stack);
	    
            // (3) Перегрузка оператора присваивания
            Stack<B>& operator=(const Stack& stack);
        
            // (4) Возвращает "false", если статус 0, иначе "true"
            bool fail() const;
        
            // (5) Присваивает статусу значение 0
            void reset();
        
            // (6) Возвращает код ошибки
            int status() const;
        
            // (7) Возвращает количество элементов в стеке
            int size() const;
        
            // (8) Извлекает последний записанный элемент
            B pop();
        
            // (9) Позволяет увидеть последний элемент без извлечения
            B peek();
        
            // (10) Добавляет в стек элемент "newElement"
            void push(const B& newObject);
	    
            // (11) Извлекает из стека "number" элементов
            void multiplyPop(const int& number);
        
            // (12) Освобождает динамически выделенную память
            void clear();
	    
            // (13) Деструктор
            ~Stack();
        
        private :
            
            // (14) Удаляет элементы стека, начиная с "element"
            void deleteFromPointer(const Element<B>* element);
    };
    
    ////////// Stack Methods /////////////////////////////////////////////////
    // Реализация методов класса "стек".                                    //
    //////////////////////////////////////////////////////////////////////////
    
    template <typename B>
    
    // (1) Конструктор
	Stack<B>::Stack()
    {
        head_   = NULL;
        size_   = 0;
        status_ = 0;
    }
    
    template <typename B>
    
    // (2) Конструктор копирования
	Stack<B>::Stack(const Stack& stack)
    {
        head_   = NULL;
        size_   = 0;
        status_ = 0;
        *this   = stack;
    }
    
    template <typename B>
    
    // (3) Перегрузка оператора присваивания
	Stack<B>& Stack<B>::operator=(const Stack& stack)
    {
        // Проверка на самоприсваивание, наличие ошибки
        if (this != &stack && !fail() && !stack.fail())
        {
            if (size_ == stack.size_)
            {
                Element<B>* assignable = head_;
                Element<B>* copied     = stack.head_;
                
                while (assignable != NULL && copied != NULL)
                {
                    assignable -> object = copied -> object;
                    assignable           = assignable -> next;
                    copied               = copied -> next;
                }
            }
            else
            {
                clear();
                
                Element<B>** assignable = &head_;
                Element<B>*  copied     = stack.head_;
                
                while (copied != NULL && status_ == 0)
                {
                    *assignable = new Element<B>;
                    if (*assignable == NULL)
                    {
                        status_ = 1;
                    }
                    else
                    {
                        ++size_;
                        *(*assignable) = *copied;
                        copied         = copied -> next;
                        assignable     = &((*assignable) -> next); 
                    }
                }
            }
        }
        return *this;
    }
    
    template <typename B>
    
    // (4) Возвращает "false", если статус 0, иначе "true"
    bool Stack<B>::fail() const
    {
        return status_ > 0;
    }
    
    template <typename B>
    
    // (5) Присваивает статусу значение 0
    void Stack<B>::reset()
    {
        status_ = 0;
    }
    
    template <typename B>
    
    // (6) Возвращает код ошибки
    int Stack<B>::status() const
    {
        return status_;
    }
    
    template <typename B>
    
    // (7) Возвращает количество элементов в стеке
    int Stack<B>::size() const
    {
        return size_;
    }
    
    template <typename B>
    
    // (8) Извлекает последний записанный элемент
    B Stack<B>::pop()
    {
        B temp;
        // Проверка состояния объекта
        if (!fail())
        {
            if (head_ != NULL)
            {
                Element<B>* tempHead = head_;
                
                head_ = head_ -> next;
                temp  = tempHead -> object;
                --size_;
                
                delete tempHead;
            }
            else
            {
                status_ = 2;
            }
        }
        return temp;
    }
    
    template <typename B>
    
    // (9) Позволяет увидеть последний элемент без извлечения
    B Stack<B>::peek()
    {
        B temp;
        // Проверка состояния объекта
        if (!fail())
        {
            if (head_ != NULL)
            {
                temp = head_ -> object;
            }
            else
            {
                status_ = 2;
            }
        }
        return temp;
    }
    
    template <typename B>
    
    // (10) Добавляет в стек элемент "newElement"
    void Stack<B>::push(const B& newObject)
    {
        // Проверка состояния объекта
        if (!fail())
        {
            Element<B>* temp = head_;
            head_ = new Element<B>;
            if (head_ != NULL)
            {
                head_ -> object = newObject;
                head_ -> next   = temp;
                ++size_;
            }
            else
            {
                status_ = 1;
            }
        }
    }
	
    template <typename B>
    
    // (11) Извлекает из стека "number" элементов
    void Stack<B>::multiplyPop(const int& number)
    {
        // Проверка состояния объекта
        if (!fail())
        {
            if (number <= size_ && number > 0)
            {
                std::cout << "(";
                for (int i = 0; i < number && status_ == 0; ++i)
                {
                    std::cout << pop();
                    if (i != number - 1)
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << ")";
            }
            else
            {
                status_ = 3;
            }
        }
    }
    
    template <>
    
    // (11) Специализация шаблона метода "multiplyPop" для типа "bool"
    void Stack<bool>::multiplyPop(const int& number)
    {
        // Проверка состояния объекта
        if (!fail())
        {
            if (number <= size_ && number > 0)
            {
                std::cout << "(";
                for (int i = 0; i < number && status_ == 0; ++i)
                {
                    if (pop())
                    {
                        std::cout << "true";
                    }
                    else
                    {
                        std::cout << "false";
                    }
                    if (i != number - 1)
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << ")";
            }
            else
            {
                status_ = 3;
            }
        }
    }
    
    template <typename B>
    
	// (12) Освобождает динамически выделенную память и обнуляет переменные
    void Stack<B>::clear()
    {
        deleteFromPointer(head_);
        head_ = NULL;
        size_   = 0;
        status_ = 0;
    }
	
    template <typename B>
    
    // (13) Деструктор
	Stack<B>::~Stack()
    {
        clear();
    }
    
    template <typename B>
    
    // (14) Удаляет элементы стека, начиная с "element"
    void Stack<B>::deleteFromPointer(const Element<B>* element)
    {
        if (element != NULL)
        {
            deleteFromPointer(element -> next);
            delete element;
        }
    }
}
    
#endif