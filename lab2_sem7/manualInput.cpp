#include "manualInput.h"
#include <sstream>
#include <ctime>
#ifdef max
#undef max
#endif

using namespace std;
bool ValidateDate(wstring& date) { // Проверка даты
    wistringstream wis(date);
    int day;
    int month;
    int year;
    wchar_t delimiter = '/';
    if (wis >> setw(2) >> setfill(L'0') >> day >>  delimiter >> setw(2) >> setfill(L'0') >> month >> delimiter >> year) {
        if (delimiter != '/' || to_string(day).length() > 2 || to_string(month).length() > 2 || to_string(year).length() != 4) {
            return false;
        }
        struct tm t = { 0 };
        t.tm_mday = day;
        t.tm_mon = month - 1;
        t.tm_year = year - 1900;
        t.tm_isdst = -1;
        time_t res = mktime(&t);
        if (res < 0) {
            return false;
        }
        else {
            return true;
        }
    }
    return false;
}

void ConvertDateToSQLiteFormat(wstring& date) { // Конвертация даты к формату базы данных
    wistringstream wis(date);
    int day;
    int month;
    int year;
    wchar_t delimiter = '/';
    wis >> setw(2) >> setfill(L'0') >> day >> delimiter >> setw(2) >> setfill(L'0') >> month >> delimiter >> year;
    delimiter = '-';
    wstring temp;
    wostringstream wos(temp);
    wos << year << delimiter << setw(2) << setfill(L'0') << month << delimiter << setw(2) << setfill(L'0') << day;
    date = wos.str();
    int a = 0;
}

void ConvertDateToOutputFormat(wstring& date) { // Конвертация даты к формату для вывода
    wistringstream wis(date);
    int day;
    int month;
    int year;
    wchar_t delimiter = '-';
    wis >> year >> delimiter >> setw(2) >> setfill(L'0') >> month >> delimiter >> setw(2) >> setfill(L'0') >> day;
    delimiter = '/';
    wstring temp;
    wostringstream wos(temp);
    wos << setw(2) << setfill(L'0') << day << delimiter << setw(2) << setfill(L'0') << month << delimiter << year;
    date = wos.str();
    int a = 0;
}

int DateInput(wstring& date) { // Ручной ввод даты
    int userChoice;
    system("cls");
    cout << "Дата должна иметь формат: ДД/ММ/ГГГГ" << endl;
    cout << "Введите дату : " << endl;
    getline(wcin, date);
    if (!ValidateDate(date)) {
        cerr << "Введено некорректное значение." << endl;
        system("pause");
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: {
            return ErrorInDateInput;
        }
        case GoBackToMainMenuMenuItem: {
            return GoBack;
        }
        }
    }
    return NoError;
}

void PrintGasBrands(vector<wstring>& listOfBrands) { // Вывод списка марок бензина
    for (int i = 0; i < listOfBrands.size(); i++) {
        wcout << i + 1 << L". " << listOfBrands[i] << endl;
    }
    cout << endl;
}

int BrandIDInput(int* brandID) { // Выбор марки бензина и его проверка
    int userChoice;
    vector<wstring> listOfBrands;
    system("cls");
    cout << "Выберите марку бензина: " << endl;
    cout << endl;
    GetGasBrands(listOfBrands, L"gasDB.db");
    PrintGasBrands(listOfBrands);
    cout << "Выбор: ";
    if (cin.fail() || !(cin >> userChoice).good() || userChoice < 1 || userChoice > listOfBrands.size()) {
        cerr << "Введено некорректное значение." << endl;
        system("pause");
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: {
            return ErrorInGasBrandInput;
        }
        case GoBackToMainMenuMenuItem: {
            return GoBack;
        }
        }
    }
    else {
        wstring query = L"SELECT id FROM gasBrands WHERE brand = '" + listOfBrands[userChoice - 1] + L"';";
        GetID(brandID, query, L"gasDB.db");
    }
    return NoError;
}

int ManualInput(record& rec) { // Ручной ввод данных для записи журнала
    int errorCode = NoError;
    do {
        cin.ignore();
        errorCode = DateInput(rec.date);
        if (errorCode == GoBack) {
            return GoBack;
        }
    } while (errorCode != NoError);
    ConvertDateToSQLiteFormat(rec.date);
    do {
        errorCode = BrandIDInput(&(rec.brandID));
        if (errorCode == GoBack) {
            return GoBack;
        }
    } while (errorCode != NoError);

    do {
        system("cls");
        cout << "Введите пробег, км : ";
        errorCode = NumberInput(&(rec.mileage));
        if (errorCode == GoBack) {
            return GoBack;
        }
    } while (errorCode != NoError);

    do {
        system("cls");
        cout << "Введите цену за литр, руб. : ";
        errorCode = NumberInput(&(rec.price));
        if (errorCode == GoBack) {
            return GoBack;
        }
    } while (errorCode != NoError);

    do {
        system("cls");
        cout << "Введите количество литров : ";
        errorCode = NumberInput(&(rec.amount));
        if (errorCode == GoBack) {
            return GoBack;
        }
    } while (errorCode != NoError);
    rec.total = rec.amount * rec.price;
    return NoError;
}

int ManualInput(wstring& gasBrand) { // Ручной ввод марки бензина
    system("cls");
    int userChoice;
    cout << "Укажите название марки бензина: ";
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    getline(wcin, gasBrand);
    if (gasBrand == L"" || gasBrand == L"\t" || gasBrand == L"\n") {
        cerr << "Вы не ввели символ для поиска." << endl;
        system("pause");
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: {
            return ErrorInGasBrandInput;
        }
        case GoBackToMainMenuMenuItem: {
            return GoBack;
        }
        }
    }
    return NoError;
}

bool FirstDateIsEarlier(wstring firstDate, wstring secondDate) { // Сравнение дат
    replace(firstDate.begin(), firstDate.end(), '/', '-');
    replace(secondDate.begin(), secondDate.end(), '/', '-');
    if (firstDate > secondDate) {
        return true;
    }
    return false;
}

int InputTwoDates(wstring& firstDate, wstring& secondDate) { // Ввод двух дат
    int userChoice;
    int errorCode = NoError;
    do {
        do {
            cin.ignore();
            errorCode = DateInput(firstDate);
            switch (errorCode) {
            case ErrorInDateInput: {
                continue;
                break;
            }
            case GoBackToMainMenuMenuItem: {
                return GoBack;
            }
            }
        } while (errorCode != NoError);
        do {
            errorCode = NoError;
            errorCode = DateInput(secondDate);
            switch (errorCode) {
            case ErrorInDateInput: {
                continue;
                break;
            }
            case GoBackToMainMenuMenuItem: {
                return GoBack;
            }
            }
        } while (errorCode != NoError);
        if (FirstDateIsEarlier(firstDate, secondDate)) {
            cerr << "Вторая дата не должна быть раньше первой." << endl;
            system("pause");
            PrintErrorMenu();
            MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
            switch (userChoice) {
            case EnterDataAgainMenuItem: {
                errorCode = ErrorInDateInput;
                break;
            }
            case GoBackToMainMenuMenuItem: {
                return GoBack;
            }
            }
        }
        ConvertDateToSQLiteFormat(firstDate);
        ConvertDateToSQLiteFormat(secondDate);
    } while (errorCode != NoError);
    return NoError;
}