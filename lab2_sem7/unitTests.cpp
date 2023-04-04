#include "unitTests.h"
#include <cmath>
#include <iomanip>
using namespace std;

int RunValidationTests() {
#pragma region ValidateDateTest1
    int errorCode = NoError;
    wstring date = L"01/02/2000";
    bool actual = ValidateDate(date);
    bool expected = true;
    if (actual != expected) {
        cout << "Тест №1 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
#pragma endregion
#pragma region ValidateDateTest2
    date = L"101/202/000";
    actual = ValidateDate(date);
    expected = false;
    if (actual != expected) {
        cout << "Тест №2 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
#pragma endregion
    return errorCode;
}

int RunDateConvertTests() {
#pragma region DateConvertTest1
    int errorCode = NoError;
    wstring actual = L"01/02/2000";
    wstring expected = L"2000-02-01";
    ConvertDateToSQLiteFormat(actual);
    if (actual != expected) {
        cout << "Тест №3 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
#pragma endregion
#pragma region ConvertDateToOutputFormat
    actual = L"2000-02-01";
    expected = L"01/02/2000";
    ConvertDateToOutputFormat(actual);
    if (actual != expected) {
        cout << "Тест №4 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
#pragma endregion
    return errorCode;
}

int RunGetJournalRecordsTest() {
    int errorCode = NoError;
    bool success = false;
    vector<record> actual;
    GetJournalRecords(actual, L"testDB.db");
    vector<record> expected = {
        { 1, L"2022-10-05", 1, L"Лукойл", 24370, 40.15, 10, 401.5 },
        { 2, L"2022-10-06", 2, L"Роснефть", 24470.5, 50.21, 10, 521.1 },
        { 3, L"2022-10-07", 3, L"Газпромнефть", 24570, 60.05, 15, 900.75 },
        { 4, L"2022-10-08", 1, L"Лукойл", 24670.9, 40.97, 20, 819.4 } };
    for (int i = 0; i < expected.size(); i++) {
        if (actual[i] == expected[i]) {
            success = true;
        }
        else {
            success = false;
        }
    }
    if (!success) {
        cout << "Тест №5 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
    return errorCode;
}

int RunGetGasBrandsTest() {
    int errorCode = NoError;
    bool success = false;
    vector<wstring> actual;
    GetGasBrands(actual, L"testDB.db");
    vector<wstring> expected = { L"Лукойл", L"Роснефть", L"Газпромнефть", L"Татнефть", L"Shell", L"ПТК" };
    for (int i = 0; i < expected.size(); i++) {
        if (actual[i] == expected[i]) {
            success = true;
        }
        else {
            success = false;
        }
    }
    if (!success) {
        cout << "Тест №6 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
    return errorCode;
}

int RunGetIDTest() {
    int errorCode = NoError;
    int actual;
    wstring query = L"SELECT id FROM gasBrands WHERE brand = 'Роснефть';";
    GetID(&actual, query, L"testDB.db");
    int expected = 2;
    if (actual != expected) {
        cout << "Тест №7 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
    return errorCode;
}

int RunGetAverageBetweenRefuelingTest() {
    int errorCode = NoError;
    bool success = false;
    averageBetweenRefueling actual;
    wstring firstDate = L"2022-10-05";
    wstring secondDate = L"2022-10-08";
    GetAverageBetweenRefueling(actual, firstDate, secondDate, L"testDB.db");
    averageBetweenRefueling expected = { 
        300.90000000000146,
        5.4709090909091174,
        0.11385866994607945,
        47.844999999999999,
        880.91666666666663,
        4.1791666666666867 };
    if (actual == expected) {
        success = true;
    }

    if (!success) {
        cout << "Тест №8 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
    return errorCode;
}

int RunGetGasBrandStatsTest() {
    int errorCode = NoError;
    bool success = false;
    vector<gasBrandStats> actual;
    GetGasBrandStats(actual, L"testDB.db");
    vector<gasBrandStats> expected = { 
        { L"Лукойл", 
        300.90000000000146, 
        10.030000000000049, 
        0.24645753132934839, 
        40.560000000000002, 
        406.96666666666670, 
        4.1791666666666867 } };
    for (int i = 0; i < expected.size(); i++) {
        if (actual[i] == expected[i]) {
            success = true;
        }
        else {
            success = false;
        }
    }
    if (!success) {
        cout << "Тест №9 провалился." << endl;
        cout << endl;
        errorCode = TestError;
    }
    return errorCode;
}

void RunTests() {
    int errorCode = NoError;
    errorCode += RunValidationTests();
    errorCode += RunDateConvertTests();
    errorCode += RunGetJournalRecordsTest();
    errorCode += RunGetGasBrandsTest();
    errorCode += RunGetIDTest();
    errorCode += RunGetAverageBetweenRefuelingTest();
    errorCode += RunGetGasBrandStatsTest();
    if (errorCode == NoError) {
        cout << "Тестирование прошло успешно." << endl;
        cout << endl;
        system("pause");
    }
    else {
        cerr << "Тестирование провалилось." << endl;
        cout << "Возможные причины ошибки: " << endl;
        cout << "\t* Неверно работает функция" << endl;
        cout << "\t* Неверно введены исходные данные" << endl;
        cout << "\t* Неверно введены ожидаемые данные" << endl;
        cout << endl;
        system("pause");
    }
}