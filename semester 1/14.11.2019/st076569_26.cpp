// Реализовать алгоритм Нидлмана-Вунша

#include <iostream>
#include <cstring>
using namespace std;

enum Transition {Left, Leftup, Up};

struct Element		// Элемент двумерного массива
{
    int value;
    Transition shift;
};

void Read_information(int& match, int& mismatch, int& gap, string& s1, string& s2)
{
    cout << "<<<<<<<<<<<<<<<< Input >>>>>>>>>>>>>>>>" << endl;
    cout << " > Enter the sequence of nitrogenous bases." << endl;
    cout << "+---------------------------+" << endl;
    cout << "| Example                   |" << endl;
    cout << "| 1) : ACGTCATCA            |" << endl;
    cout << "| 2) : TAGTGTCA             |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "1) : ";
    cin >> s1;
    cout << "2) : ";
    cin >> s2;
    cout << " > Enter the cost of matching, mismatch and gap." << endl;
    cout << "+---------------------------+" << endl;
    cout << "| Example                   |" << endl;
    cout << "| 1) Matching cost    : 1   |" << endl;
    cout << "| 2) Mismatching cost : -1  |" << endl;
    cout << "| 3) Gap cost         : -1  |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "1) Matching cost    : ";
    cin >> match;
    cout << "2) Mismatching cost : ";
    cin >> mismatch;
    cout << "3) Gap cost         : ";
    cin >> gap;
}

int G(int i, int j, string s1, string s2, int match, int mis)	// Проверка на совпадение, ход по диагонали
{
    if (s1[i - 1] == s2[j - 1])
    {
        return match;
    } else
    {
        return mis;
    }
}

void Optimal_alignment(int match, int mis, int gap, string s1, string s2)
{
    int s1_len = s1.length(), s2_len = s2.length();
    int max_value = 0;
    Element array[s2_len + 1][s1_len + 1];
  // <<<<<<<< Заполнение массива >>>>>>>>
    array[0][0].value = 0;
    for (int i = 1; i <= s1_len; i++)
    {
        array[0][i].value = array[0][i - 1].value + gap;
        array[0][i].shift = Left;
    }
    for (int j = 1; j <= s2_len; j++)
    {
        array[j][0].value = array[j - 1][0].value + gap;
        array[j][0].shift = Up;
    }
    for (int i = 1; i <= s1_len; i++)
    {
        for (int j = 1; j <= s2_len; j++)
        {
            max_value = array[j - 1][i - 1].value + G(i,j,s1,s2,match,mis);
            array[j][i].shift = Leftup;
            if (max_value < array[j][i - 1].value)
            {
                max_value = array[j][i - 1].value + gap;
                array[j][i].shift = Left;
            }
            if (max_value < array[j - 1][i].value)
            {
                max_value = array[j - 1][i].value + gap;
                array[j][i].shift = Up;
            }
            array[j][i].value = max_value;
        }
    }
  // <<<<<<<< Обратный ход по массиву >>>>>>>>
    string a1 = " ", a2 = " ", temp;
    int i = s1_len, j = s2_len;
    while (i != 0 || j != 0)
    {
        switch(array[j][i].shift)
        {
            case Left:
                temp = s1[i - 1];
                a1.insert(0, temp);
                a2.insert(0, "-");
                i--;
                break;
            case Up:
                temp = s2[j - 1];
                a2.insert(0, temp);
                a1.insert(0, "-");
                j--;
                break;
            case Leftup:
                temp = s1[i - 1];
                a1.insert(0, temp);
                temp = s2[j - 1];
                a2.insert(0, temp);
                i--;
                j--;
                break;
        }
    }
  // <<<<<<<< Вывод результата >>>>>>>>
    cout << "<<<<<<<<<<<<<<<< Answer >>>>>>>>>>>>>>>>" << endl;
    cout << "Maximum profit : " << array[s2_len][s1_len].value << endl;
    cout << "Optimal alignment" << endl;
    cout << "1) : " << a1 << endl;
    cout << "2) : " << a2 << endl;
    cout << "+---------------------------+" << endl;
    cout << "| Example                   |" << endl;
    cout << "| 1) Maximum profit : 3     |" << endl;
    cout << "| Optimal alignment         |" << endl;
    cout << "| 1) : -ACGTCATCA           |" << endl;
    cout << "| 2) : TA-GTG-TCA           |" << endl;
    cout << "+---------------------------+" << endl;
}

int main()
{
    int match = 0, mismatch = 0, gap = 0;
    string s1, s2;
    Read_information(match,mismatch,gap,s1,s2);
    Optimal_alignment(match,mismatch,gap,s1,s2);
    system("Pause");
    return 0;
}