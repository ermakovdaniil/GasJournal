#include "userInterface.h"

using namespace std;

void Greeting() { // Приветсвие
    system("cls");
    cout << "Лабораторная работа №1" << endl;
    cout << "Вариант 5" << endl;
    cout << endl;
    cout << "Данная программа реализует работу с журналом заправок." << endl;
    cout << "Ввод данных можно осуществить вручную или открыв файл формата .txt." << endl;
    cout << "В программе реализованы функции сохранения исходных данных и" << endl;
    cout << "результатов работы программы в файл формата .txt." << endl;
    cout << endl;
    cout << "Автор: Ермаков Даниил" << endl;
    cout << "Группа: 494" << endl;
    cout << endl;
    system("pause");
}

void PrintMenu() { // Вывод меню
    system("cls");
    cout << "\tГЛАВНОЕ МЕНЮ" << endl;
    cout << "Выберите вариант:" << endl;
    cout << "1. Просмотр журнала покупок бензина." << endl;
    cout << "2. Добавление записи в журнал." << endl;
    cout << "3. Добавление марки бензина." << endl;
    cout << "4. Создание текстовых файлов с данными." << endl;
    cout << "5. Просмотр средних показателей между заправками." << endl;
    cout << "6. Просмотр средних показателей по марке бензина." << endl;
    cout << "7. Запустить модульное тестирование." << endl;
    cout << "8. Вывод информации о программе и авторе." << endl;
    cout << "9. Выход из программы." << endl;
    cout << endl;
    cout << "Выберите пункт меню: ";
}

void PrintInputMenu() { // Вывод вспомогательного меню с выбором ввода
    system("cls");
    cout << "1. Ввод данных вручную." << endl;
    cout << "2. Ввод данных из файла." << endl;
    cout << "3. Выход в главное меню." << endl;
    cout << endl;
    cout << "Выберите пункт меню: ";
}

void PrintCreateTextFile() { // Вывод меню с пунктами создания файлов
    system("cls");
    cout << "Выберите вариант:" << endl;
    cout << "1. Сохранить журнал заправок." << endl;
    cout << "2. Сохранить исходные данные журнала." << endl;
    cout << "3. Сохранить список марок бензина." << endl;
    cout << "4. Сохранить исходные данные списка марок бензина." << endl;
    cout << "5. Выход в главное меню." << endl;
    cout << endl;
    cout << "Выберите пункт меню: ";
}

void PrintYesNoMenu(const string& msg) { // Вывод вспомогательного меню с выбором «Да» и «Нет»
    cout << msg << endl;
    cout << "1 - Да | 2 - Нет" << endl;
    cout << endl;
    cout << "Выбор: ";
}

void PrintJournal(const vector<record>& records) { // Вывод исходных данных
    system("cls");
    cout << "+ ----- + ---------- + ----------------- + ---------- + ------------------ + ---------------- + ----------- +" << endl;
    cout << "| НОМЕР |    ДАТА    |   МАРКА БЕНЗИНА   | ПРОБЕГ, КМ | ЦЕНА ЗА ЛИТР, РУБ. | КОЛИЧЕСТВО, ЛИТР | СУММА, РУБ. |" << endl;
    cout << "+ ----- + ---------- + ----------------- + ---------- + ------------------ + ---------------- + ----------- +" << endl;
    for (int i = 0; i < records.size(); i++) {
        wstring wstr(records[i].date.begin(), records[i].date.end());
        ConvertDateToOutputFormat(wstr);
        wcout << "|" << left << setw(7) << records[i].id <<
            "|" << left << setw(12) << wstr <<
            "|" << left << setw(19) << records[i].gasBrand <<
            "|" << left << setw(12) << fixed  << setprecision(2) << records[i].mileage <<
            "|" << left << setw(20) << fixed << setprecision(2) << records[i].price <<
            "|" << left << setw(18) << fixed << setprecision(2) << records[i].amount <<
            "|" << left << setw(13) << fixed << setprecision(2) << records[i].total << "|" << endl;
    }
    cout << "+ ----- + ---------- + ----------------- + ---------- + ------------------ + ---------------- + ----------- +" << endl;
    cout << endl;
    system("pause");
}

void PrintAverageBetweenRefueling(const averageBetweenRefueling& abr, wstring& firstDate, wstring& secondDate) { // Вывод в консоль средних показателей по заправкам
    system("cls");
    ConvertDateToOutputFormat(firstDate);
    ConvertDateToOutputFormat(secondDate);
    wcout << L"C " << firstDate << L" по " << secondDate << L" в среднем на заправку вышло:" << endl; 
    cout << "+ ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +" << endl;
    cout << "| ПРОБЕГ, КМ | ПРОБЕГ НА ЛИТР, КМ | СТОИМОСТЬ НА 1 КМ, РУБ. | СТОИМОСТЬ ЛИТРА, РУБ. | СТОИМОСТЬ ДНЯ, РУБ. | ВРЕМЯ РАСХОДОВАНИЯ ЛИТРА, МИН. |" << endl;
    cout << "+ ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +" << endl;
    cout << "|" << left << setw(12) << fixed << setprecision(2) << abr.mileage <<
        "|" << left << setw(20) << fixed << setprecision(2) << abr.mileagePerLiter <<
        "|" << left << setw(25) << fixed << setprecision(2) << abr.pricePerKm <<
        "|" << left << setw(23) << fixed << setprecision(2) << abr.price <<
        "|" << left << setw(21) << fixed << setprecision(2) << abr.pricePerTime <<
        "|" << left << setw(32) << fixed << setprecision(2) << abr.timePerLiter << "|" << endl;
    cout << "+ ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +" << endl;
    cout << endl;
}

void PrintGasBrandStats(const vector<gasBrandStats>& gbs) { // Вывод в консоль средних показателей марок бензина
    system("cls");
    cout << "\t\tСрдение показатели по маркам бензина" << endl;
    cout << "+ ----------------- + ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +" << endl;
    cout << "|   МАРКА БЕНЗИНА   | ПРОБЕГ, КМ | ПРОБЕГ НА ЛИТР, КМ | СТОИМОСТЬ НА 1 КМ, РУБ. | СТОИМОСТЬ ЛИТРА, РУБ. | СТОИМОСТЬ ДНЯ, РУБ. | ВРЕМЯ РАСХОДОВАНИЯ ЛИТРА, МИН. |" << endl;
    cout << "+ ----------------- + ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +" << endl;
    for (int i = 0; i < gbs.size(); i++) {
        wcout << "|" << left << setw(19) << gbs[i].gasBrand <<
            "|" << left << setw(12) << fixed << setprecision(2) << gbs[i].mileage <<
            "|" << left << setw(20) << fixed << setprecision(2) << gbs[i].mileagePerLiter <<
            "|" << left << setw(25) << fixed << setprecision(2) << gbs[i].pricePerKm <<
            "|" << left << setw(23) << fixed << setprecision(2) << gbs[i].price <<
            "|" << left << setw(21) << fixed << setprecision(2) << gbs[i].pricePerTime <<
            "|" << left << setw(32) << fixed << setprecision(2) << gbs[i].timePerLiter << "|" << endl;
    }
    cout << "+ ----------------- + ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +" << endl;
    cout << endl;
}

void PrintWarningForJournalFile() { // Вывод в консоль сообщения о данных, которые должны находиться в файле с исходными данными
    system("cls");
    cout << "Внимание! В файле должна быть как минимум 1 строка." << endl;
    cout << "Строка должна содержать данные в строго заданном порядке через пробел:" << endl;
    cout << "ДАТА МАРКА-БЕНЗИНА ПРОБЕГ ЦЕНА-ЗА-ЛИТР КОЛИЧЕСТВО СУММА" << endl;
    cout << endl;
    system("pause");
}

void PrintWarningForGasBrandsFile() { // Вывод в консоль сообщения о данных, которые должны находиться в файле с исходными данными
    system("cls");
    cout << "Внимание! В файле должна быть как минимум 1 строка." << endl;
    cout << endl;
    system("pause");
}

int AddGasBrands() { // Добавление марку бензина
    vector<wstring> listOfBrands;
    PrintWarningForGasBrandsFile();
    int errorCode = Input(listOfBrands);
    for (int i = 0; i < listOfBrands.size(); i++) {
        wstring query = L"INSERT INTO gasBrands(brand) VALUES ('" + listOfBrands[i] + L"');";
        AddRecord(query, L"gasDB.db");
    }
    return errorCode;
}

int AddJournalRecords() { // Добавление записи в журнал заправок
    vector<record> recs;
    PrintWarningForJournalFile();
    int errorCode = Input(recs);
    for (int i = 0; i < recs.size(); i++) {
       wstring query = L"INSERT INTO journal(date, brandID, mileage, price, amount, total) VALUES ('" +
            recs[i].date + L"', '" + to_wstring(recs[i].brandID) + L"', '" + to_wstring(recs[i].mileage) + L"', '" +
            to_wstring(recs[i].price) + L"', '" + to_wstring(recs[i].amount) + L"', '" + to_wstring(recs[i].total) + L"');";
        AddRecord(query, L"gasDB.db");
    }
    return errorCode;
}

void Menu() { // Главное меню
    int userChoice;
    int errorCode = GoBack;
    vector<wstring> createdText;
    averageBetweenRefueling abr;
    vector<gasBrandStats> gbs;
    wstring firstDate;
    wstring secondDate;
    do {
        PrintMenu();
        MenuInputCheck(&userChoice, ShowJournalMenuItem, ExitMenuItem);
        cout << endl;
        switch (userChoice) {
        case ShowJournalMenuItem: { // Просмотр записей в журнале заправок
            vector<record> recs;
            GetJournalRecords(recs, L"gasDB.db");
            PrintJournal(recs);
            break;
        }
        case AddRecordMenuItem: { // Добавление записи в журнал
            errorCode = AddJournalRecords();
            break;
        }
        case AddGasBrandMenuItem: { // Добавление марки бензина
            errorCode = AddGasBrands();
            break;
        }
        case CreateTextFileMenuItem: { // Создание текстовых файлов
            PrintCreateTextFile();
            MenuInputCheck(&userChoice, SaveJournalResultMenuItem, GoBackSaveMenuItem);
            if (userChoice == GoBackSaveMenuItem) {
                continue;
            }
            CreateTextFile(createdText, &userChoice);
            errorCode = SaveFile(createdText);
            break;
        }
        case ShowAverageBetweenRefuelingMenuItem: { // Просмотр средних значений по заправкам
            errorCode = InputTwoDates(firstDate, secondDate);
            if (userChoice == GoBack) {
                continue;
            }
            GetAverageBetweenRefueling(abr, firstDate, secondDate, L"gasDB.db");
            PrintAverageBetweenRefueling(abr, firstDate, secondDate);
            break;
        }
        case ShowGasBrandsStatsMenuItem: { // Просмотр средних значений по ммаркам бензина
            GetGasBrandStats(gbs, L"gasDB.db");
            PrintGasBrandStats(gbs);
            errorCode = NoError;
            break;
        }
        case RunTestsMenuItem: { // Запуск модульного тестирования
            RunTests();
            break;
        }
        case ShowInfoMenuItem: { // Вывод информации о программе и авторе
            Greeting();
            break;
        }
        case ExitMenuItem: { // Выход из программы
            cout << "Программа завершена." << endl;
            exit(0);
        }
        }
        if (userChoice == AddRecordMenuItem || userChoice == AddGasBrandMenuItem) {
            if (errorCode == GoBack) {
                continue;
            }
            cout << "Запись успешно добавлена." << endl;
            cout << endl;
            system("pause");
        }
        if (userChoice == ShowAverageBetweenRefuelingMenuItem || userChoice == ShowGasBrandsStatsMenuItem) {
            if (errorCode == GoBack) {
                continue;
            }
            int choice;
            PrintYesNoMenu("Сохранить результат в файл?");
            MenuInputCheck(&choice, Yes, No);
            switch (choice) {
            case Yes: {
                switch (userChoice) {
                case ShowAverageBetweenRefuelingMenuItem: {
                    CreateAverageBetweenRefuelingResult(createdText, abr, firstDate, secondDate);
                    break;
                }
                case ShowGasBrandsStatsMenuItem: {
                    CreateBrandsStatsResult(createdText, gbs);
                    break;
                }
                }
                errorCode = SaveFile(createdText);
                if (errorCode == GoBack) {
                    continue;
                }
                break;
            }
            case No: { break; }
            }
        }
    } while (errorCode != NoError);
}