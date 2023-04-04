#pragma once
#include <string>
#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>
#include "enums.h"
#include "structures.h"
#include "inputValidation.h"
#include "workWithDB.h"

bool ValidateDate(std::wstring& date);

void ConvertDateToSQLiteFormat(std::wstring& date);

void ConvertDateToOutputFormat(std::wstring& date);

int DateInput(std::wstring& date);

void PrintGasBrands(std::vector<std::wstring>& listOfBrands);

int BrandIDInput(int* brandID);

template<typename T>
int NumberInput(T* number);

template<typename T>
int NumberInput(T* number) { // Ручной ввод цифр и их проверка
    int userChoice;
    if (std::cin.fail() || !(std::cin >> *number).good() || *number <= 0) {
        std::cerr << "Введено некорректное значение." << std::endl;
        system("pause");
        std::cin.ignore(INT_MAX, '\n');
        std::cin.clear();
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: {
            return ErrorInNumberInput;
        }
        case GoBackToMainMenuMenuItem: {
            return GoBack;
        }
        }
    }
    std::cin.ignore(INT_MAX, '\n');
    std::cin.clear();
    return NoError;
}

int ManualInput(record& rec);

int ManualInput(std::wstring& gasBrand);

bool FirstDateIsEarlier(std::wstring firstDate, std::wstring secondDate);

int InputTwoDates(std::wstring& firstDate, std::wstring& secondDate);