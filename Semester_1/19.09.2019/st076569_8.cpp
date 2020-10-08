// Реализовать структуру String для работы со строками. Структура должна удовлетворять правилу Трех 
// и содержать методы поиска подстроки и конкатенации(как оператор+).

#include <iostream>
using namespace std;

struct String			// Структура для работы со строками
{
  int count;
  char* str = nullptr;
    String(char* c)		// Конструктор (вспомогательный)
    {
        count = 256;
        str = new char[count];
        for (int i = 0; c[i] != '\0' && i < count; i++) 
        {
          str[i] = c[i];
          if (c[i + 1] == '\0' || i + 1 == count)
          {
            str[i + 1] = '\0';
          }
        }
    }
    String()			// Конструктор по умолчанию
    {
      count = 256;
      str = new char[count];
    }
    String(const String& s)	// Конструктор копий
    {
      count = 256;
        str = new char[count];
        for (int i = 0; i <= count; i++)
        {
          str[i] = s.str[i];
        }
    }
    ~String()			// Деструктор
    {
        delete[] str;
    }
    void out_str();		// Вывод строки на экран (вспомогательный)
    int substring(String s);	// Функция поиска подстроки
    String operator+=(String s)	// Перегрузка +=
    {
      int n;
        for (n = 0; str[n] != '\0'; n++);
        for (int i = n; s.str[i - n] != '\0'; i++)
        {
          str[i] = s.str[i - n];
          if (s.str[i - n + 1] == '\0')
          {
            str[i + 1] = '\0';
          }
        }   
        return *this;
    }
    String operator=(String s)	// Перегрузка =
    {
        for (int i = 0; s.str[i] != '\0'; i++)
        {
          str[i] = s.str[i];
          if (s.str[i + 1] == '\0')
          {
            str[i + 1] = '\0';
          }
        }   
        return *this;
    }
};

void String::out_str()
{
    for (int i = 0; str[i] != '\0'; cout << str[i++]);
}

String operator+(String s1, String s2)	// Перегрузка +
{
    s1 += s2; 
    return s1;
}

bool match(char* c, String s)		// Функция проверки совпадения подстроки (s) с основной строкой,
{					// начиная с элемента (с) основной строки
  bool m = true;
  int i;
    for (i = 0; s.str[i] != '\0' && c[i] != '\0'; i++)
    {
      if (s.str[i] != c[i]) 
      {
        m = false;
      }
    }
    if (c[i] == '\0' && c[i] != s.str[i]) 
    {
      m = false;
    }
    return m;
}

int String::substring(String s)		// Функция поиска подстроки
{					// -1 (если подстроки нет) или номер символа, с которого начинается подстрока 
  int n = -1; 
    for (int i = 0; str[i] != '\0' && n == -1; i++)
    {
      if (match(str + i, s)) 
      {
        n = i + 1;
      } 
    }
    return n;
}

int main ()
{					// Примеры работы
  char name1[256] = {"Hello, World!"};
  char name2[256] = {", Wor"};
  char name3[256] = {"Hello"};
  String s1(name1);
  String s2(name2);
  String s3(name3);
    s1.out_str();			// Вывод всех строк
     cout << endl;
    s2.out_str();
     cout << endl;
    s3.out_str();
     cout << endl << s1.substring(s2);	// Поиск s2 в s1
     cout << endl << s1.substring(s3);	// Поиск s3 в s1
     cout << endl;
    s2 = s1 + s3;
    s2.out_str();
     cout << endl;
    s3 += s1;
    s3.out_str();
     cout << endl << s1.substring(s2);	// Поиск s2 в s1
    return 0;
}