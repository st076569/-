// �������� ������� ���������� �������, ������������ ������������ ���������� ������ ��������� �� ��������
#include <iostream>
#include <ctime>
using namespace std;

void Sort_array (int* a0, int n)       //��������� ���������� ������� �� ����������� (�������)
{
  bool sign = false;
  int temp = 0;
  do 
  {
    sign = false;
    for (int i = 0; i < n; i++) {
      if (a0[i] > a0[i+1]) {
        sign = true;
        temp = a0[i];
        a0[i] = a0[i+1];
        a0[i+1] = temp;
      }
    }
  }
  while (sign);
}

void In_array (int* a0, int n)        // ���������� ������� ���������� �������
{
  srand (time (0));
  for (int* p = a0; p <= a0+n; p++) 
  {
    *p = 1 + rand() % 500;
  }
}

void Out_array (int* a0, int n)       // ����� ������� �� �����
{
  for (int* p = a0; p <= a0+n; p++) 
  {
    cout << *p << " ";  
  }
  cout << endl;
}

int main () {
  int a[20];
   In_array(a,19);	// ��������� ������
   Out_array(a,19);	// ������� ����������������� ������
   Sort_array(a,19);	// ���������
   Out_array(a,19);	// ������� ��������������� ������
  return 0;
}