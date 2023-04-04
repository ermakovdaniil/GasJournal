﻿// Лабораторная работа № 2.
// Вариант 5.
// По данным, имеющимся в журнале покупок бензина, напечатайте
// разнообразную контрольную статистику, показывающую водителю, 
// во что обходится эксплуатация автомобиля. 
// Исходные данные о каждой покупке — это дата, марка бензина,
// показание счетчика пройденного пути, цена одного литра, 
// сколько литров куплено и общая стоимость.
// Выводимая информация должна повторять исходную и, кроме того,
// включать в себя такие показатели, как пробег между заправками, 
// пробег на один литр, стоимость пробега в один километр, стоимость одного
// галлона, стоимость одного дня, время расходования одного галлона.
// Все указанные показатели следует получать для каждой заправки и усреднять
// двумя способами: за небольшой срок и за все время наблюдений.
// Кроме того, соберите данные по каждой марке бензина и напечатайте
// соответствующие средние значения.
// Не ограничивайте число различных марок.

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "userInterface.h"
#define NOMINMAX

using namespace std;

int main() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 1350, 400, TRUE);
    system("color F0");
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Greeting();
    while (true) {
        Menu();
    }
}