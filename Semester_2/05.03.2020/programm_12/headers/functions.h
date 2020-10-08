/*
(20 баллов)
Построить структуру данных дерево поиска (без добавления/удаления).
Реализовать конструктор, деструктор, обращение по ключу (operator[]),
выписывание в отсортированном порядке (operator<<), определение высоты,
глубины элементов, размера дерева.
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int error = -1;

// Вспомогательный элемент для записи входных данных
struct InputElement
{
    int value;
    unsigned int key;
    InputElement();
};

// Элемент дерева
struct Element
{
    int value;
    unsigned int key;
    Element* left;
    Element* right;
    Element();
};

// Дерево поиска
struct BinarySearchTree
{
    Element* head;  // Корень
  private:
    int max_depth;
    int max_width;
  public:
    // Конструктор, деструктор
    BinarySearchTree();
    ~BinarySearchTree();
    // Методы по заданию
    int operator[](const unsigned int num);
    int height();
    int width();
    int depth(unsigned int num);
    // Вспомогательные методы
    void fill_tree(int num, InputElement* array);
    void delete_tree(Element* start);
    void find_max_depth(Element* start, int actual_depth, int& max_depth);
    void find_max_width(Element* start, int actual_depth, int* array);
};

void read_tree(int& num, InputElement** array);
void sort_output(Element* start, ostream& os);
ostream& operator<<(ostream& os, const BinarySearchTree& bst);
    
#endif
