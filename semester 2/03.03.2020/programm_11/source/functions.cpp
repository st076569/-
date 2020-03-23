/*
(20 баллов)
Построить структуру данных дерево поиска (без добавления/удаления).
Реализовать конструктор, деструктор, обращение по ключу (operator[]),
выписывание в отсортированном порядке (operator<<), определение высоты,
глубины элементов, размера дерева.
(сделать задачу в полиморфном стиле)
*/

#include "functions.h"

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

BinarySearchTree::BinarySearchTree(const BinarySearchTree& bst)
{
    head = NULL;
    max_depth = 0;
    max_width = 0;
    *(this) = bst;
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

// Копирует дерево рекурсивно
void BinarySearchTree::copy_bst(Element** assignable_head, Element* copied_head)
{
    if (copied_head != NULL)
    {
        (*(assignable_head)) = new Element;
        (*(*(assignable_head))).value = (*(copied_head)).value;
        (*(*(assignable_head))).key = (*(copied_head)).key;
        copy_bst(&(*(*(assignable_head))).left, (*(copied_head)).left);
        copy_bst(&(*(*(assignable_head))).right, (*(copied_head)).right);
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
int BinarySearchTree::depth(keyType num)
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
        return -1;
    }
}

// Возвращает значение элемента по данному ключу
int BinarySearchTree::operator[](const keyType num)
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

// Перегрузка оператора присваивания
BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& bst)
{
    if (this == &bst)   // проверка на присваивание себе
    {        
        return *this;
    }
    else
    {
        delete_tree(head);
        head = bst.head;
        max_depth = bst.max_depth;
        max_width = bst.max_width;
        if (head != NULL)
        {
            copy_bst(&head, bst.head);
        }
        return *this;
    }
}
////////////////////////////// end \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Считывает дерево
void input(Element** start, istream& is)
{
    int num = 0;
    cout << " > Number : ";
    is >> num;
    cout << " (Value, Key)" << endl;
    if (num > 0)
    {
        keyType tempKey = 0;
        valueType tempValue = 0;
        Element* actual = NULL;
        Element* prev = NULL;
        bool isRight = false;
        
        for (int i = 0; i < num; ++i)
        {
            cout << " " << i + 1 << ") : ";
            if (i == 0)
            {
                // Записываем корень
                (*(start)) = new Element;
                is >> (*(*(start))).value >> (*(*(start))).key;
            }
            else
            {
                is >> tempValue >> tempKey;
                actual = *(start);
                while (actual != NULL)      // Справа строго больше, слева меньше
                {
                    prev = actual;
                    if (tempKey > (*(actual)).key)
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
                    (*((*(prev)).right)).value = tempValue;
                    (*((*(prev)).right)).key = tempKey;
                }
                else
                {
                    (*(prev)).left = new Element;
                    (*((*(prev)).left)).value = tempValue;
                    (*((*(prev)).left)).key = tempKey;
                }
            }
        }    
    }
}

// Вывод отсортированных элементов
void output(Element* start, ostream& os)
{
    if (start != NULL)
    {
        output((*(start)).left, os);
        os << " <> value : " << (*(start)).value << "; key : " << (*(start)).key << endl;
        output((*(start)).right, os);
    }
}

// Демонстрирует возможности структуры BinarySearchTree
void allOutput(BinarySearchTree& bst)
{
    int key = 0;
    cout << "+======================= start =======================+" << endl;
    cout << " <> Height  : " << bst.height() << endl;   // Высота bst
    cout << " <> Width   : " << bst.width() << endl;    // Ширина bst
    
    do  // Запрос ключа
    {
        cout << " > Write down key : ";
        cin >> key;
    }
    while (key < 0);
    
    cout << " <> tree[" << key << "] = " << bst[key] << endl;               // Значение элемента по данному ключу
    cout << " <> tree.depth(" << key << ") = " << bst.depth(key) << endl;   // Глубина элемента по данному ключу
    cout << endl << bst;                                                    // Вывод элементов на экран в порядке возрастания значений ключей
    cout << "+======================== end ========================+" << endl;
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const BinarySearchTree& bst)
{
    os << "[ binary search tree ]" << endl;
    output(bst.head, os);
    os << "[      end tree      ]" << endl;
    return os;
}

// Перегрузка оператора ввода
istream& operator>>(istream& is, BinarySearchTree& bst)
{
    bst.delete_tree(bst.head);
    cout << "[ binary search tree ]" << endl;
    input(&bst.head, is);
    bst.find_max_depth(bst.head, 0, bst.max_depth);
    int* width_mas = new int[bst.max_depth + 1];
    for (int i = 0; i <= bst.max_depth; ++i)
    {
        width_mas[i] = 0;
    }
    bst.find_max_width(bst.head, 0, width_mas);
    for (int i = 0; i <= bst.max_depth; ++i)
    {
        if (bst.max_width < width_mas[i])
        {
            bst.max_width = width_mas[i];
        }
    }
    delete[] width_mas;
    cout << "[      end tree      ]" << endl;
    return is;
}