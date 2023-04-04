#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#include <string>
#include <vector>
#include <time.h>
#include <iostream>
#include <algorithm>
#include "enums.h"
#include "structures.h"
#include "manualInput.h"
#include "workWithDB.h"

void PrintAdditionalMenu();

bool IsPathIncorrect(const std::string& path, const int context);

bool IsReadOnly(const std::string& path);

int CheckPath(const std::string& path, const int context);

int CheckData(std::vector<std::wstring>& data, const std::vector<std::wstring>& text);

bool CheckRecordVector(std::vector<std::wstring> rec);

int CheckData(std::vector<record>& data, std::vector<std::wstring>& text);

void PrintTextInFile(const std::vector<std::wstring>& text, const std::string& path);

void ReadFromFile(std::vector<std::wstring>& text, const std::string& path);

int SaveFile(const std::vector<std::wstring>& text);

template<typename T>
int FileInput(std::vector<T>& data) { // Чтение данных из файла и их проверка
    std::string path = "";
    std::vector<std::wstring> text;
    text.clear();
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        std::cout << "Введите путь к файлу: ";
        std::cin.ignore();
        getline(std::cin, path);
        errorCode = CheckPath(path, InputContext);
        switch (errorCode) {
        case NoError: {
            ReadFromFile(text, path);
            errorCode = CheckData(data, text);
            switch (errorCode) {
            case ErrorInFileData: {
                continue;
                break;
            }
            case GoBack: {
                return GoBack;
            }
            }
            break;
        }
        case ErrorInPathInput: {
            continue;
            break;
        }
        case GoBack: {
            return GoBack;
        }
        }
    } while (errorCode != NoError);
    return NoError;
}