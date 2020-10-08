/*
(20 баллов)
Построить структуру данных дерево поиска (без добавления/удаления).
Реализовать конструктор, деструктор, обращение по ключу (operator[]),
выписывание в отсортированном порядке (operator<<), определение высоты,
глубины элементов, размера дерева.
*/

#include "functions.h"

InputElement::InputElement()
{
    key = 0;
    value = 0;
};

Element::Element()
{
    key = 0;
    value = 0;
    left = NULL;
    right = NULL;
}

////////////////////////////// BinarySearchTree \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Конструктор
BinarySearchTree::BinarySearchTree()
{
    head = NULL;
    max_depth = 0;
    max_width = 0;
}

// Деструктор
BinarySearchTree::~BinarySearchTree()
{
    delete_tree(head);
}

// Рекурсивно удаляет дерево
void BinarySearchTree::delete_tree(Element* start)
{
    if (start != NULL)
    {
        delete_tree((*(start)).left);
        delete_tree((*(start)).right);
        delete start;
    } 
}

// Инициализирует дерево значениями из массива
void BinarySearchTree::fill_tree(int num, InputElement* array)
{
    if (num > 0 && array != NULL)       // Корректность инициализации
    {
        head = new Element;             // Записываем корень
        (*(head)).value = array[0].value;
        (*(head)).key = array[0].key;

        Element* actual = NULL;
        Element* prev = NULL;
        bool isRight = false;
        
        for (int i = 1; i < num; ++i)   // Записываем все элементы в дерево поиска
        {
            actual = head;
            while (actual != NULL)      // Справа строго больше, слева меньше
            {
                prev = actual;
                if (array[i].key > (*(actual)).key)
                {
                    actual = (*(actual)).right;
                    isRight = true;
                }
                else
                {
                    actual = (*(actual)).left;
                    isRight = false;
                }
            }
            if (isRight)
            {
                (*(prev)).right = new Element;
                (*((*(prev)).right)).value = array[i].value;
                (*((*(prev)).right)).key = array[i].key;
            }
            else
            {
                (*(prev)).left = new Element;
                (*((*(prev)).left)).value = array[i].value;
                (*((*(prev)).left)).key = array[i].key;
            }
        }
        
        find_max_depth(head, 0, max_depth);
        int* width_mas = new int[max_depth + 1];
        for (int i = 0; i <= max_depth; ++i)
        {
            width_mas[i] = 0;
        }
        find_max_width(head, 0, width_mas);
        for (int i = 0; i <= max_depth; ++i)
        {
            if (max_width < width_mas[i])
            {
                max_width = width_mas[i];
            }
        }
        delete[] width_mas;
    }
}

// Находит высоту дерева
void BinarySearchTree::find_max_depth(Element* start, int actual_depth, int& max_depth)
{
    if (start != NULL)
    {
        find_max_depth((*(start)).left, actual_depth + 1, max_depth);
        find_max_depth((*(start)).right, actual_depth + 1, max_depth);
        if (actual_depth > max_depth)
        {
            max_depth = actual_depth;
        }
    }
}

// Находит ширину дерева
void BinarySearchTree::find_max_width(Element* start, int actual_depth, int* array)
{
    if (start != NULL)
    {
        find_max_width((*(start)).left, actual_depth + 1, array);
        find_max_width((*(start)).right, actual_depth + 1, array);
        ++array[actual_depth];
    }
}

// Вывод отсортированных элементов
void sort_output(Element* start, ostream& os)
{
    if (start != NULL)
    {
        sort_output((*(start)).left, os);
        os << " <> value : " << (*(start)).value << "; key : " << (*(start)).key << endl;
        sort_output((*(start)).right, os);
    }
}

// Возвращает высоту дерева
int BinarySearchTree::height()
{
    return max_depth;
}

// Возвращает ширину дерева
int BinarySearchTree::width()
{
    return max_width;
}

// Возвращает глубину элемента
int BinarySearchTree::depth(unsigned int num)
{
    Element* actual = head;
    int level = 0;
    
    while (actual != NULL && (*(actual)).key != num)
    {
        if (num > (*(actual)).key)
        {
            actual = (*(actual)).right;
        }
        else
        {
            actual = (*(actual)).left;
        }
        ++level;
    }
    if (actual != NULL)
    {
        return level;
    }
    else
    {
        return error;
    }
}

// Возвращает значение элемента по данному ключу
int BinarySearchTree::operator[](const unsigned int num)
{
    Element* actual = head;
    
    while (actual != NULL && (*(actual)).key != num)
    {
        if (num > (*(actual)).key)
        {
            actual = (*(actual)).right;
        }
        else
        {
            actual = (*(actual)).left;
        }
    }
    if (actual != NULL)
    {
        return (*(actual)).value;
    }
    else
    {
        return -1;
    }
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const BinarySearchTree& bst)
{
    os << "[ tree ]" << endl;
    sort_output(bst.head, os);
    os << "[ ---- ]";
    return os;
}

////////////////////////////// end \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Чтение входных данных
void read_tree(int& num, InputElement** array)
{
    cout << "<<<<<<<<        Programm_12        >>>>>>>>" << endl;
    cout << "+-----------------------------------------+" << endl;
    cout << "| Example :                               |" << endl;
    cout << "| > Write down number of elements : 3     |" << endl;
    cout << "| > Write down elements (value key)       |" << endl;
    cout << "| 1) : 5 1                                |" << endl;
    cout << "| 2) : 10 2                               |" << endl;
    cout << "| 3) : 7 8                                |" << endl;
    cout << "+-----------------------------------------+" << endl;
    cout << endl;
    
    do
    {
        cout << " > Write down number of elements : ";
        cin >> num;
    }
    while (num <= 0);
    (*(array)) = new InputElement[num];
    cout << " > Write down elements (value key)" << endl;
    for (int i = 0; i < num; ++i)
    {
        cout << " " << i + 1 << ") ";
        cin >> (*(array))[i].value >> (*(array))[i].key;
    }
}