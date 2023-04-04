#include "inputValidation.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std;

void MenuInputCheck(int* userChoice, const int min, const int max) { // �������� ������� �����. ��������� ������� ������ �����
    while (cin.fail() || !(cin >> *userChoice).good() || *userChoice < min || *userChoice > max) { // ���� ���� ������������ �� �������� ������ ��� ��������� ��� �������� ������
        cin.clear();
        cout << endl;
        cerr << "������� ������������ ��������.";
        cout << endl;
        cout << "������� ��������: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void PrintErrorMenu() { // ����� ���������������� ���� ��� ������������� ������
    system("cls");
    cout << "\t��� �� ������ �������?" << endl;
    cout << "1. ���� ������ ������." << endl;
    cout << "2. ����� � ������� ����." << endl;
    cout << endl;
    cout << "�������� ����� ����: ";
}