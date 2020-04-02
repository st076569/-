/*
(20 баллов)
Дан массив, содержащий перестановку чисел от 0 до N.
Вычислить ожидаемое число поворотов каждого типа при добавлении этого
массива в пустое авл дерево (провести численный эксперимент)
*/

#include "functions.h"

// Возвращает true с вероятностью chance
bool have_action(const double& chance)
{
    return ((double)rand() / RAND_MAX) <= chance;
}

// Создает транспозицию элементов
void create_transposition(int* array, int& arrayNum)
{
    int actual = 0, j = 0;
    for (int i = 0; i < arrayNum; i++)
    {
        array[i] = -1;
    }
    while (actual < arrayNum)
    {
        if (array[j] == -1 && have_action((double) 1 / (arrayNum - actual)))
        {
            array[j] = actual;
            actual++;
        }
        ++j;
        j %= arrayNum;
    }
}

// Выводит среднее значение по всем величинам
void print_average_stat(const int& number)
{
    AVLTree<int> tree;
    float slr = 0, srr = 0, blr = 0, brr = 0;
    int count = number / 10;
    for (int i = 0; i < count; ++i)
    {
        tree.del();
        fill_tree(number, tree, 1);
        slr += tree.return_slr();
        srr += tree.return_srr();
        blr += tree.return_blr();
        brr += tree.return_brr();
    }
    cout << " [ Average number ]" << endl;
    cout << " > number : " << number << endl;
    cout << " > blr : " << blr / count << endl;
    cout << " > brr : " << brr / count << endl;
    cout << " > slr : " << slr / count << endl;
    cout << " > srr : " << srr / count << endl;
    cout << " [ end ]" << endl;
}
