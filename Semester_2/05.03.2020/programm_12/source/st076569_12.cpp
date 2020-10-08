/*
(20 баллов)
Построить структуру данных дерево поиска (без добавления/удаления).
Реализовать конструктор, деструктор, обращение по ключу (operator[]),
выписывание в отсортированном порядке (operator<<), определение высоты,
глубины элементов, размера дерева.
*/

#include "functions.h"

int main()
{
    BinarySearchTree tree;
    InputElement* inputArray = NULL;
    int key = 0, size = 0;
    
    read_tree(size, &inputArray);       // Читаем входные данные
    tree.fill_tree(size, inputArray);   // Записываем в дерево
    cout << endl;
    cout << " > Height  : " << tree.height() << endl;   // Высота дерева
    cout << " > Width   : " << tree.width() << endl;    // Ширина дерева
    cout << endl;
    
    do  // Запрос ключа
    {
        cout << " > Write down key : ";
        cin >> key;
    }
    while (key < 0);
    
    cout << endl;
    cout << " > tree[" << key << "] = " << tree[key] << endl;               // Значение элемента по данному ключу
    cout << " > tree.depth(" << key << ") = " << tree.depth(key) << endl;   // Глубина элемента по данному ключу
    cout << endl;
    cout << tree << endl;   // Вывод элементов на экран в порядке возрастания значений ключей
    
    delete[] inputArray;
    return 0;
}