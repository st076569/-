/*
(20 баллов)
Построить структуру данных дерево поиска (без добавления/удаления).
Реализовать конструктор, деструктор, обращение по ключу (operator[]),
выписывание в отсортированном порядке (operator<<), определение высоты,
глубины элементов, размера дерева.
(сделать задачу в полиморфном стиле)
*/

#include "functions.h"

int main()
{
    BinarySearchTree tree1;
    cin >> tree1;       // Читаем tree1
    allOutput(tree1);   // Выводим все по tree1
    BinarySearchTree tree2(tree1);
    allOutput(tree2);   // Выводим все по tree2
    cin >> tree2;       // Вводим заново tree2
    allOutput(tree2);   // Выводим все по tree2
    tree1 = tree2;      // Присваиваем новое значение
    allOutput(tree1);   // Выводим все по tree1
    return 0;
}