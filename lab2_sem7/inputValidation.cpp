#include "inputValidation.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std;

void MenuInputCheck(int* userChoice, const int min, const int max) { // Проверка ручного ввода. Позволяет вводить только числа
    while (cin.fail() || !(cin >> *userChoice).good() || *userChoice < min || *userChoice > max) { // Если ввод пользователя не является цифрой или находится вне заданных границ
        cin.clear();
        cout << endl;
        cerr << "Введено некорректное значение.";
        cout << endl;
        cout << "Введите значение: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void PrintErrorMenu() { // Вывод вспомогательного меню при возникновении ошибки
    system("cls");
    cout << "\tЧто вы хотите сделать?" << endl;
    cout << "1. Ввод данных заново." << endl;
    cout << "2. Выход в главное меню." << endl;
    cout << endl;
    cout << "Выберите пункт меню: ";
}