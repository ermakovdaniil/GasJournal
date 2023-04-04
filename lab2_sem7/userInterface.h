#pragma once
#include <vector>
#include <string>
#include "enums.h"
#include "structures.h"
#include "inputValidation.h"
#include "manualInput.h"
#include "fileSystem.h"
#include "workWithDB.h"
#include "textCreator.h"
#include "unitTests.h"

void Greeting();

void PrintMenu();

void PrintInputMenu();

void PrintCreateTextFile();

void PrintYesNoMenu(const std::string& msg);

void PrintJournal(const std::vector<record>& records);

void PrintAverageBetweenRefueling(const averageBetweenRefueling& abr, std::wstring& firstDate, std::wstring& secondDate);

void PrintGasBrandStats(const std::vector<gasBrandStats>& gbs);

void PrintWarningForJournalFile();

void PrintWarningForGasBrandsFile();

void Menu();

template<typename T>
int Input(std::vector<T>& data);

template<typename T>
int Input(std::vector<T>& data) { // Ввод данных
    int userChoice;
    int errorCode;
    PrintInputMenu();
    MenuInputCheck(&userChoice, ManualInputMenuItem, GoBackInputMenuItem);
    switch (userChoice) {
    case ManualInputMenuItem: {
        T rec;
        errorCode = ManualInput(rec);
        data.push_back(rec);
        break;
    }
    case FileInputMenuItem: {
        errorCode = FileInput(data);
        break;
    }
    case GoBackInputMenuItem: {
        return GoBack;
        break;
    }
    }
    return NoError;
}