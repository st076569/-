/*
(20 баллов)
Построить структуру данных дерево поиска (без добавления/удаления).
Реализовать конструктор, деструктор, обращение по ключу (operator[]),
выписывание в отсортированном порядке (operator<<), определение высоты,
глубины элементов, размера дерева.
(сделать задачу в полиморфном стиле)
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef int keyType;    // Тип ключа
typedef int valueType;  // Тип значения элемента

// Элемент дерева
struct Element
{
    valueType value;
    keyType key;
    Element* left;
    Element* right;
    // Конструктор
    Element();
};

// Дерево поиска
struct BinarySearchTree
{
    Element* head;  // Корень
    int max_depth;  // Высота дерева
    int max_width;  // Ширина дерева

    // Конструкторы, деструктор
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& bst);
    ~BinarySearchTree();
    // Перегрузка операторов
    BinarySearchTree& operator=(const BinarySearchTree& bst);
    int operator[](const keyType key_num);
    // Методы по заданию
    int height();
    int width();
    int depth(keyType key_num);
    // Вспомогательные методы
    void delete_tree(Element* start);
    void find_max_depth(Element* start, int actual_depth, int& max_depth);
    void find_max_width(Element* start, int actual_depth, int* array);
    void copy_bst(Element** assignable_head, Element* copied_head);
};

// Вспомогательные функции
void allOutput(BinarySearchTree& bst);
void output(Element* start, ostream& os);
void input(Element* start, istream& is);
// Перегрузка операторов ввода и вывода
ostream& operator<<(ostream& os, const BinarySearchTree& bst);
istream& operator>>(istream& is, BinarySearchTree& bst);
    
#endif
