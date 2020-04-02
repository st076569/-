/*
(20 баллов)
Дан массив, содержащий перестановку чисел от 0 до N.
Вычислить ожидаемое число поворотов каждого типа при добавлении этого
массива в пустое авл дерево (провести численный эксперимент)
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

template <typename T1>
struct Element      // Элемент дерева
{
  public:
    T1 value;       // Данные
    int key;        // Ключ
    int hight;      // Высота дерева 
    Element* left;  // Указатель на левое поддерево
    Element* right; // Указатель на правое поддерево
  public:
    Element(const T1& init_value, const int& init_key);
};

template <typename T2>
struct AVLTree          // АВЛ дерево с функцией самобалансировки
{
  private:
    Element<T2>* root;  // Корень дерева
    int blr_number;     // Кол-во больших левых поворотов
    int brr_number;     // Кол-во больших правых поворотов
    int slr_number;     // Кол-во малых левых поворотов
    int srr_number;     // Кол-во малых правых поворотов
  private:
    void sort_output(Element<T2>* head);
    void refresh_hight(Element<T2>* head);
    void del_tree(Element<T2>* head);
    int return_hight(Element<T2>* head);
    int diff(Element<T2>* head);
    Element<T2>** next(const int& key, Element<T2>* head);
    Element<T2>* big_left_rotate(Element<T2>* head);
    Element<T2>* big_right_rotate(Element<T2>* head);
    Element<T2>* small_left_rotate(Element<T2>* head);
    Element<T2>* small_right_rotate(Element<T2>* head);
    Element<T2>* balance(Element<T2>* head);
  public:
    AVLTree();
    ~AVLTree();
    void insert(const T2& value, const int& key);
    void print_tree();
    void print_stat();
    void del();
    int return_slr();
    int return_srr();
    int return_blr();
    int return_brr();
};

void create_transposition(int* array, int& arrayNum);
bool have_action(const double& chance);
void print_average_stat(const int& number);

template <typename T3>
void fill_tree(const int& number, AVLTree<T3>& tree, const T3& value);

// <============================== Описание шаблонных конструкций ==============================>

// Заполняет дерево в соответствии с транспозицией
template <typename T>
void fill_tree(const int& number, AVLTree<T>& tree, const T& value)
{
    int* transpos = new int[number];
    create_transposition(transpos, (int&)number);
    for (int i = 0; i < number; ++i)
    {
        tree.insert(value, transpos[i]);
    }
    delete[] transpos;
}

// <========================================== Element ==========================================>

// Конструктор
template <typename T>
Element<T>::Element(const T& init_value, const int& init_key)
{
    value = init_value;
    key = init_key;
    hight = 0;
    left = NULL;
    right = NULL;
}

// <========================================== AVLTree ==========================================>

// Конструктор
template <typename T>
AVLTree<T>::AVLTree()
{
    root = NULL;
    blr_number = 0;
    brr_number = 0;
    slr_number = 0;
    srr_number = 0;
}

// Деструктор
template <typename T>
AVLTree<T>::~AVLTree()
{
    del_tree(root);
}

// Удаление дерева по указателю head
template <typename T>
void AVLTree<T>::del_tree(Element<T>* head)
{
    if (head != NULL)
    {
        del_tree((*(head)).left);
        del_tree((*(head)).right);
        delete head;
    }
}

// Упорядоченный вывод дерева по указателю head
template <typename T>
void AVLTree<T>::sort_output(Element<T>* head)
{
    if (head != NULL)
    {
        sort_output((*(head)).left);
        cout << "(" << (*(head)).value << "; " << (*(head)).key << ") ";
        sort_output((*(head)).right);
    }
}

// Вывод дерева на экран
template <typename T>
void AVLTree<T>::print_tree()
{
    cout << " [ AVLTree ]" << endl;
    cout << " (value; key) : ";
    sort_output(root);
    cout  << endl << " [ end ]" << endl;
}

// Возвращает высоту дерева head
template <typename T>
int AVLTree<T>::return_hight(Element<T>* head)
{
    if (head != NULL)
    {
        return (*(head)).hight;
    }
    else
    {
        return -1;
    }
}

// Обновляет значение высоты дерева head
template <typename T>
void AVLTree<T>::refresh_hight(Element<T>* head)
{
    int left_h = return_hight((*(head)).left) + 1;
    int right_h = return_hight((*(head)).right) + 1;
    (*(head)).hight = (left_h > right_h) ? left_h : right_h; 
}

// Возвращает разницу высот поддеревьев head
template <typename T>
int AVLTree<T>::diff(Element<T>* head)
{
    return return_hight((*(head)).right) - return_hight((*(head)).left);
}

// Возвращает указатель на место следующей вставки элемента
template <typename T>
Element<T>** AVLTree<T>::next(const int& key, Element<T>* head)
{
    if (key > (*(head)).key)
    {
        return &(*(head)).right;
    }
    else
    {
        return &(*(head)).left;
    }
}

// Выводит статистику на экран
template <typename T>
void AVLTree<T>::print_stat()
{
    cout << " [ Statistic ]" << endl;
    cout << " > blr : " << blr_number << endl;
    cout << " > brr : " << brr_number << endl;
    cout << " > slr : " << slr_number << endl;
    cout << " > srr : " << srr_number << endl;
    cout << " [ end ]" << endl;
}

// Малое левое вращение
template <typename T>
Element<T>* AVLTree<T>::small_left_rotate(Element<T>* head)
{
    if (head != NULL)
    {
        if ((*(head)).right != NULL)
        {
            Element<T>* right = (*(head)).right;
            (*(head)).right = (*(right)).left;
            (*(right)).left = head;
            refresh_hight(head);
            refresh_hight(right);
            ++slr_number;
            return right;
        }
        else
        {
            return head;
        }
    }
    else
    {
        return head;
    }
}

// Малое правое вращение
template <typename T>
Element<T>* AVLTree<T>::small_right_rotate(Element<T>* head)
{
    if (head != NULL)
    {
        if ((*(head)).left != NULL)
        {
            Element<T>* left = (*(head)).left;
            (*(head)).left = (*(left)).right;
            (*(left)).right = head;
            refresh_hight(head);
            refresh_hight(left);
            ++srr_number;
            return left;
        }
        else
        {
            return head;
        }
    }
    else
    {
        return head;
    }
}

// Большое левое вращение
template <typename T>
Element<T>* AVLTree<T>::big_left_rotate(Element<T>* head)
{
    if (head != NULL)
    {
        if ((*(head)).right != NULL)
        {
            (*(head)).right = small_right_rotate((*(head)).right);
            ++blr_number;
            --srr_number;
            --slr_number;
            return small_left_rotate(head);
        }
        else
        {
            return head;
        }
    }
    else
    {
        return head;
    }
}

// Большое правое вращение
template <typename T>
Element<T>* AVLTree<T>::big_right_rotate(Element<T>* head)
{
    if (head != NULL)
    {
        if ((*(head)).left != NULL)
        {
            (*(head)).left = small_left_rotate((*(head)).left);
            ++brr_number;
            --srr_number;
            --slr_number;
            return small_right_rotate(head);
        }
        else
        {
            return head;
        }
    }
    else
    {
        return head;
    }
}

// Балансировка дерева head
template <typename T>
Element<T>* AVLTree<T>::balance(Element<T>* head)
{
    if (diff(head) > 1)
    {
        if (diff((*(head)).right) > 0)
        {
            return small_left_rotate(head);
        }
        else
        {
            return big_left_rotate(head);
        }
    }
    else
    if (diff(head) < -1)
    {
        if (diff((*(head)).left) > 0)
        {
            return big_right_rotate(head);
        }
        else
        {
            return small_right_rotate(head);
        }
    }
    else
    {
        return head;
    }
}

// Осуществляет вставку элемента в дерево
template <typename T>
void AVLTree<T>::insert(const T& value, const int& key)
{
    vector<Element<T>**> used_vertexes;
    Element<T>** actual = &root;
    while (*(actual) != NULL)
    {
        used_vertexes.push_back(actual);
        actual = next(key, *(actual));
    }
    *(actual) = new Element<T>(value, key);
    for (int i = used_vertexes.size() - 1; i >= 0; --i)
    {
        refresh_hight(*(used_vertexes[i]));
        *(used_vertexes[i]) = balance(*(used_vertexes[i]));
    }
}

// Возвращают кол-во поворотов данного типа
template <typename T>
int AVLTree<T>::return_slr()
{
    return slr_number;
}

template <typename T>
int AVLTree<T>::return_srr()
{
    return srr_number;
}

template <typename T>
int AVLTree<T>::return_blr()
{
    return blr_number;
}

template <typename T>
int AVLTree<T>::return_brr()
{
    return brr_number;
}

template <typename T>
void  AVLTree<T>::del()
{
    del_tree(root);
    blr_number = 0;
    brr_number = 0;
    slr_number = 0;
    srr_number = 0;
    root = NULL;
}

#endif
