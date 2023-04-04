#include "textCreator.h"
#include "workWithDB.h"

using namespace std;

void CreateResultJournal(vector<wstring>& createdText, const vector<record>& recs) { // Создание журнала для сохранения в файл
    createdText.clear();
    wstringstream wss;
    createdText.push_back(L"+ ----- + ---------- + ----------------- + ---------- + ------------------ + ---------------- + ----------- +");
    createdText.push_back(L"| НОМЕР |    ДАТА    |   МАРКА БЕНЗИНА   | ПРОБЕГ, КМ | ЦЕНА ЗА ЛИТР, РУБ. | КОЛИЧЕСТВО, ЛИТР | СУММА, РУБ. |");
    createdText.push_back(L"+ ----- + ---------- + ----------------- + ---------- + ------------------ + ---------------- + ----------- +");
    for (int i = 0; i < recs.size(); i++) {
        wss.str(wstring());
        wstring wstr(recs[i].date.begin(), recs[i].date.end());
        wss << L"|" << left << setw(7) << recs[i].id <<
            L"|" << left << setw(12) << wstr <<
            L"|" << left << setw(19) << recs[i].gasBrand <<
            L"|" << left << setw(12) << fixed << setprecision(2) << recs[i].mileage <<
            L"|" << left << setw(20) << fixed << setprecision(2) << recs[i].price <<
            L"|" << left << setw(18) << fixed << setprecision(2) << recs[i].amount <<
            L"|" << left << setw(13) << fixed << setprecision(2) << recs[i].total << L"|";
        createdText.push_back(wss.str());
    }
    createdText.push_back(L"+ ----- + ---------- + ----------------- + ---------- + ------------------ + ---------------- + ----------- +");
}

void CreateInitialDataJournal(vector<wstring>& createdText, const vector<record>& recs) { // Создание исходных данных журнала для сохранения в файл
    createdText.clear();
    wstringstream wss;
    for (int i = 0; i < recs.size(); i++) {
        wss.str(wstring());
        wss << recs[i].date << L" " << recs[i].brandID << L" " << recs[i].mileage << L" " << recs[i].price << L" " << recs[i].amount << L" " << recs[i].total;
        createdText.push_back(wss.str());
    }
}

void CreateResultGasBrands(vector<wstring>& createdText, const vector<wstring>& listOfGasBrands) { // Создание списка марок бензина для сохранения в файл
    createdText.clear();
    wstringstream wss;
    createdText.push_back(L"Список марок бензина: ");
    for (int i = 0; i < listOfGasBrands.size(); i++) {
        wss.str(wstring());
        wss << i + 1 << L". " << listOfGasBrands[i];
        createdText.push_back(wss.str());
    }
}

void CreateInitialDataGasBrands(vector<wstring>& createdText, const vector<wstring>& listOfGasBrands) { // Создание исходных данных списка марок бензина для сохранения в файл
    createdText.clear();
    for (int i = 0; i < listOfGasBrands.size(); i++) {
        createdText.push_back(listOfGasBrands[i]);
    }
}

void CreateAverageBetweenRefuelingResult(vector<wstring>& createdText, const averageBetweenRefueling& abr, wstring& firstDate, wstring& secondDate) { // Создание таблицы средних значений по заправкам для сохранения в файл
    createdText.clear();
    wstringstream wss;
    wss << L"C " << firstDate << L" по " << secondDate << L" в среднем на заправку вышло:" << endl;
    createdText.push_back(wss.str());
    createdText.push_back(L"+ ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +");
    createdText.push_back(L"| ПРОБЕГ, КМ | ПРОБЕГ НА ЛИТР, КМ | СТОИМОСТЬ НА 1 КМ, РУБ. | СТОИМОСТЬ ЛИТРА, РУБ. | СТОИМОСТЬ ДНЯ, РУБ. | ВРЕМЯ РАСХОДОВАНИЯ ЛИТРА, МИН. |");
    createdText.push_back(L"+ ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +");
    wss.str(wstring());
    wss << L"|" << left << setw(12) << abr.mileage <<
        L"|" << left << setw(20) << fixed << setprecision(2) << abr.mileagePerLiter <<
        L"|" << left << setw(25) << fixed << setprecision(2) << abr.pricePerKm <<
        L"|" << left << setw(23) << fixed << setprecision(2) << abr.price <<
        L"|" << left << setw(21) << fixed << setprecision(2) << abr.pricePerTime <<
        L"|" << left << setw(32) << fixed << setprecision(2) << abr.timePerLiter << L"|" << endl;
    createdText.push_back(wss.str());
    createdText.push_back(L"+ ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +");
}

void CreateBrandsStatsResult(vector<wstring>& createdText, const vector<gasBrandStats>& gbs) { // Создание таблицы средних значений по маркам бензина для сохранения в файл
    createdText.clear();
    wstringstream wss;
    createdText.push_back(L"\t\tСрдение показатели по маркам бензина");
    createdText.push_back(L"+ ----------------- + ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +");
    createdText.push_back(L"|   МАРКА БЕНЗИНА   | ПРОБЕГ, КМ | ПРОБЕГ НА ЛИТР, КМ | СТОИМОСТЬ НА 1 КМ, РУБ. | СТОИМОСТЬ ЛИТРА, РУБ. | СТОИМОСТЬ ДНЯ, РУБ. | ВРЕМЯ РАСХОДОВАНИЯ ЛИТРА, МИН. |");
    createdText.push_back(L"+ ----------------- + ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +");
    for (int i = 0; i < gbs.size(); i++) {
        wss.str(wstring());
        wss << L"|" << left << setw(19) << gbs[i].gasBrand <<
            L"|" << left << setw(20) << fixed << setprecision(2) << gbs[i].mileage <<
            L"|" << left << setw(20) << fixed << setprecision(2) << gbs[i].mileagePerLiter <<
            L"|" << left << setw(25) << fixed << setprecision(2) << gbs[i].pricePerKm <<
            L"|" << left << setw(23) << fixed << setprecision(2) << gbs[i].price <<
            L"|" << left << setw(21) << fixed << setprecision(2) << gbs[i].pricePerTime <<
            L"|" << left << setw(32) << fixed << setprecision(2) << gbs[i].timePerLiter << L"|" << endl;
        createdText.push_back(wss.str());
    }
    createdText.push_back(L"+ ----------------- + ---------- + ------------------ + ----------------------- + --------------------- + ------------------- + ------------------------------ +");
}

void CreateTextFile(vector<wstring>& createdText, const int* userChoice) { // Создание текста для сохранения в файл
    vector<record> recs;
    vector<wstring> listOfGasBrands;
    createdText.clear();
    switch (*userChoice) {
    case SaveJournalResultMenuItem: {
        GetJournalRecords(recs, L"gasDB.db");
        CreateResultJournal(createdText, recs);
        break;
    }
    case SaveJournalInitialDataMenuItem: {
        GetJournalRecords(recs, L"gasDB.db");
        CreateInitialDataJournal(createdText, recs);
        break;
    }
    case SaveGasBrandsResultMenuItem: {
        GetGasBrands(listOfGasBrands, L"gasDB.db");
        CreateResultGasBrands(createdText, listOfGasBrands);
        break;
    }
    case SaveGasBrandsInitialDataMenuItem: {
        GetGasBrands(listOfGasBrands, L"gasDB.db");
        CreateInitialDataGasBrands(createdText, listOfGasBrands);
        break;
    }
    }
}