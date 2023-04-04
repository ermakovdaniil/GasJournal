#include "workWithDB.h"
#include "manualInput.h"

using namespace std;

void CreateConnection(const wstring& filename, sqlite3* db) { // Открытие базы данных
    char* zErrMsg = 0;
    int rc = sqlite3_open16(filename.c_str(), &db);
    if (rc != SQLITE_OK) {
        cout << "Ошибка: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
    }
}

void GetJournalRecords(vector<record>& list, const wstring& filename) { // Запрос к базе данных на получение записей журнала заправки
    sqlite3* db;
    sqlite3_open16(filename.c_str(), &db);
    wstring sql = L"SELECT journal.id, journal.date, journal.brandID, gasBrands.brand, journal.mileage, journal.price, journal.amount, journal.total FROM journal INNER JOIN gasBrands ON journal.brandID = gasBrands.id;";
    sqlite3_stmt* stmt;
    int err = sqlite3_prepare16_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (err != SQLITE_OK) {
        cout << "Ошибка: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        record rec;
        rec.id = sqlite3_column_int(stmt, 0);
        rec.date = (LPCTSTR)sqlite3_column_text16(stmt, 1);
        rec.brandID = sqlite3_column_int(stmt, 2);
        rec.gasBrand = (LPCTSTR)sqlite3_column_text16(stmt, 3);
        rec.mileage = sqlite3_column_double(stmt, 4);
        rec.price = sqlite3_column_double(stmt, 5);
        rec.amount = sqlite3_column_double(stmt, 6);
        rec.total = rec.price * rec.amount;
        list.push_back(rec);
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return;
}

void GetGasBrands(vector<wstring>& listOfBrands, const wstring& filename) {
    sqlite3* db;
    sqlite3_open16(filename.c_str(), &db);
    wstring query = L"SELECT brand FROM gasBrands";
    sqlite3_stmt* stmt;
    int err = sqlite3_prepare16_v2(db, query.c_str(), -1, &stmt, NULL);
    if (err != SQLITE_OK) {
        cout << "Ошибка: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        wstring gasBrand = (LPCTSTR)sqlite3_column_text16(stmt, 0);
        listOfBrands.push_back(gasBrand);  
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return;
}

void GetID(int* id, const wstring& query, const wstring& filename) {
    sqlite3* db;
    sqlite3_open16(filename.c_str(), &db);
    sqlite3_stmt* stmt;
    int err = sqlite3_prepare16_v2(db, query.c_str(), -1, &stmt, NULL);
    if (err != SQLITE_OK) {
        cout << "Ошибка: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        *id = sqlite3_column_int(stmt, 0);
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return;
}

void AddRecord(wstring& query, const wstring& filename) {
    sqlite3* db;
    sqlite3_open16(filename.c_str(), &db);
    sqlite3_stmt* stmt;
    int err = sqlite3_prepare16_v2(db, query.c_str(), -1, &stmt, NULL);
    if (err != SQLITE_OK) {
        cout << "Ошибка: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        sqlite3_bind_text16(stmt, 1, "record", -1, NULL);
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return;
}

void GetAverageBetweenRefueling(averageBetweenRefueling& abr, wstring& firstDate, wstring& secondDate, const wstring& filename) {
    sqlite3* db;
    sqlite3_open16(filename.c_str(), &db);
    wstring query = L"SELECT MAX(mileage) - MIN(mileage), "
        "(MAX(mileage) - MIN(mileage)) / SUM(amount), "
        "(MAX(mileage) - MIN(mileage)) / SUM(total), "
        "AVG(price), "
        "SUM(total) / (julianday('" + secondDate + L"') - julianday('" + firstDate + L"')), "
        "(MAX(mileage) - MIN(mileage)) / (julianday('" + secondDate + L"') - julianday('" + firstDate + L"')) / 24 FROM journal "
        "WHERE date BETWEEN '" + firstDate + L"' AND '" + secondDate + L"';";
    sqlite3_stmt* stmt;
    int err = sqlite3_prepare16_v2(db, query.c_str(), -1, &stmt, NULL);
    if (err != SQLITE_OK) {
        cout << "Ошибка: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        abr.mileage = sqlite3_column_double(stmt, 0);
        abr.mileagePerLiter = sqlite3_column_double(stmt, 1);
        abr.pricePerKm = sqlite3_column_double(stmt, 2);
        abr.price = sqlite3_column_double(stmt, 3);
        abr.pricePerTime = sqlite3_column_double(stmt, 4);
        abr.timePerLiter = sqlite3_column_double(stmt, 5);
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return;
}

void GetGasBrandStats(vector<gasBrandStats>& gbs, const wstring& filename) {
    sqlite3* db;
    sqlite3_open16(filename.c_str(), &db);
    wstring query = L"SELECT gasBrands.brand, "
        "MAX(mileage) - MIN(mileage), "
        "(MAX(mileage) - MIN(mileage)) / SUM(amount), "
        "(MAX(mileage) - MIN(mileage)) / SUM(total), "
        "AVG(price), "
        "SUM(total) / (julianday(MAX(date)) - julianday(MIN(date))), "
        "(MAX(mileage) - MIN(mileage)) / (julianday(MAX(date)) - julianday(MIN(date))) / 24 FROM journal "
        "JOIN gasBrands ON gasBrands.id = journal.brandID "
        "GROUP BY gasBrands.brand "
        "HAVING COUNT(gasBrands.brand) > 1;";
    sqlite3_stmt* stmt;
    int err = sqlite3_prepare16_v2(db, query.c_str(), -1, &stmt, NULL);
    if (err != SQLITE_OK) {
        cout << "Ошибка: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        gasBrandStats tempGbs;
        tempGbs.gasBrand = (LPCTSTR)sqlite3_column_text16(stmt, 0);
        tempGbs.mileage = sqlite3_column_double(stmt, 1);
        tempGbs.mileagePerLiter = sqlite3_column_double(stmt, 2);
        tempGbs.pricePerKm = sqlite3_column_double(stmt, 3);
        tempGbs.price = sqlite3_column_double(stmt, 4);
        tempGbs.pricePerTime = sqlite3_column_double(stmt, 5);
        tempGbs.timePerLiter = sqlite3_column_double(stmt, 6);
        gbs.push_back(tempGbs);
    }
    sqlite3_reset(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return;
}