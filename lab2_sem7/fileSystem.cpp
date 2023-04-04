#include "fileSystem.h"
#include <Windows.h>

#ifdef max
#undef max
#endif

using namespace std::experimental::filesystem;
using namespace std;

void PrintAdditionalMenu() { // ��������������� ����, ���� � ���� ���������� ����� ��� ��������� ��� ������������ ����
    system("cls");
    cout << "������ ���� ��� ����������." << endl;
    cout << endl;
    cout << "\t��� �� ������ �������?" << endl;
    cout << "1. ���������� �����." << endl;
    cout << "2. �������� ������ �����." << endl;
    cout << "3. ����� � ������� ����." << endl;
    cout << endl;
    cout << "�������� ����� ����: ";
}

bool IsPathIncorrect(const string& path, const int context) { // �������� �� ������������� ������������ ������ �/��� ����������������� ���
    error_code ec;
    if (context == SaveContext) { // ���� �������� �������� � ������ ����������
        if (ifstream(path)) {
            if (!is_regular_file(path, ec)) {
                return true;
            }
            return false;
        }
        ofstream fout(path, ofstream::_Noreplace);
        if (!is_regular_file(path, ec)) {
            return true;
        }
        if (!fout) {
            fout.close();
            return true;
        }
        fout.close();
        remove(path);
    }
    else { // ���� �������� �������� � ������ ��������
        if (!ifstream(path)) {
            return true;
        }
        if (!is_regular_file(path, ec)) {
            return true;
        }
        ifstream fin(path);
        if (!fin) {
            fin.close();
            return true;
        }
        fin.close();
    }
    return false;
}

bool IsReadOnly(const string& path) { // �������� ����� �� ������� "������ ��� ������"
    WIN32_FIND_DATAA findData;
    LPCSTR name = path.c_str();
    FindFirstFileA(name, &findData);
    FindFirstFileA(name, &findData);
    if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) {
        return true;
    }
    else {
        return false;
    }
}

int CheckPath(const string& path, const int context) { // �������� ���� � �����
    int userChoice;
    if (IsPathIncorrect(path, context) || IsReadOnly(path)) { // �������� �� ���������� ���� � ��� �����
        if (IsPathIncorrect(path, context)) { // ���� ���� �����������
            cerr << "������������ �������� ���� ��� ����� �����." << endl;
            cout << endl;
            system("pause");
        }
        if (IsReadOnly(path)) { // ���� ���� "������ ��� ������"
            cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
            cout << endl;
            system("pause");
        }
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
            return ErrorInPathInput;
        }
        case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
            return GoBack;
        }
        }
    }
    return NoError;
}

int CheckData(vector<wstring>& data, const vector<wstring>& text) { // �������� ������, ���������� � �����
    int userChoice;
    if (text.empty()) {
        cerr << "� ����� ������������ ������." << endl;
        cout << endl;
        system("pause");
        PrintErrorMenu();
        MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
        switch (userChoice) {
        case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
            return ErrorInFileData;
        }
        case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
            return GoBack;
        }
        }
    } 
    else {
        data = text;
    }
    return NoError;
}

bool CheckRecordVector(vector<wstring> rec) { // �������� ������, ���������� � �����
    if (!ValidateDate(rec[0])) {
        return false;
    }
    vector<wstring> listOfBrands;
    GetGasBrands(listOfBrands, L"gasDB.db");
    if (!(find(listOfBrands.begin(), listOfBrands.end(), rec[1]) != listOfBrands.end())) {
        return false;
    }
    for (int i = 2; i < rec.size(); i++) {
        for (char const& c : rec[i]) {
            if (isdigit(c) == 0) return false;
        }
        if (stod(rec[i]) <= 0) {
            return false;
        }
    }
    return true;
}

int CheckData(vector<record>& data, vector<wstring>& text) { // ��������� ������ �� ���������
    int userChoice;
    vector<wstring> recAsString;
    for (int i = 0; i < text.size(); i++) {
        recAsString.clear();
        const wchar_t separator = ' ';
        size_t start;
        size_t end = 0;
        while ((start = text[i].find_first_not_of(separator, end)) != std::string::npos) {
            end = text[i].find(separator, start);
            recAsString.push_back(text[i].substr(start, end - start));
        }
        if (text.empty() || recAsString.size() != 6 || !CheckRecordVector(recAsString)) {
            if (text.empty()) {
                cerr << "� ����� ������������ ������." << endl;
            }
            if (!CheckRecordVector(recAsString)) {
                cerr << "� ����� ������� ����������� ������." << endl;
            }
            cout << endl;
            system("pause");
            PrintErrorMenu();
            MenuInputCheck(&userChoice, EnterDataAgainMenuItem, GoBackToMainMenuMenuItem);
            switch (userChoice) {
            case EnterDataAgainMenuItem: { // ������� � ������ ���� ������
                return ErrorInFileData;
            }
            case GoBackToMainMenuMenuItem: { // ������� ����� � ������� ����
                return GoBack;
            }
            }
        }
        else {
            int brandID;
            wstring query = L"SELECT id FROM gasBrands WHERE brand = '" + recAsString[1] + L"';";
            GetID(&brandID, query, L"gasDB.db");
            record rec;
            rec.date = recAsString[0];
            rec.brandID = brandID;
            ConvertDateToSQLiteFormat(recAsString[1]);
            rec.gasBrand = recAsString[1];
            rec.mileage = stod(recAsString[2]);
            rec.mileage = ceil(rec.mileage * 100.0) / 100.0;
            rec.price = stod(recAsString[3]);
            rec.price = ceil(rec.price * 100.0) / 100.0;
            rec.amount = stod(recAsString[4]);
            rec.amount = ceil(rec.amount * 100.0) / 100.0;
            rec.total = stod(recAsString[5]);
            rec.total = ceil(rec.total * 100.0) / 100.0;
            data.push_back(rec);
        }
    }
    return NoError;
}

void ReadFromFile(vector<wstring>& text, const string& path) { // ������ ������ �� �����
    wifstream wfin(path);
    wfin.seekg(0, ios::beg);
    wfin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
    wstring temp;
    while (!wfin.eof()) { // ������ �����    
        temp.clear();
        while (getline(wfin, temp)) {
            text.push_back(temp);
        }
    }
    wfin.close();
}

void PrintTextInFile(const vector<wstring>& text, const string& path) { // ������ ������ � ����
    ofstream fout(path, ofstream::trunc);
    for (int i = 0; i < text.size(); i++) {
        if (i == text.size() - 1) {
            fout << text[i];
        }
        else {
            fout << text[i] << endl;
        }
    }
}

int SaveFile(const vector<wstring>& text) { // ������� ��� �������� ������ � ������������ ��� ���������� �������
    int userChoice;
    string path = "";
    int errorCode = ErrorInPathInput;
    do {
        system("cls");
        cout << "������� ���� � �����: ";
        cin.ignore();
        getline(cin, path);
        errorCode = CheckPath(path, SaveContext);
        switch (errorCode) {
        case ErrorInPathInput: {
            continue;
            break;
        }
        case GoBack: {
            return GoBack;
        }
        }
        if (ifstream(path)) { // ���� ���� ����������
            PrintAdditionalMenu(); // ����� ���������������� ����
            MenuInputCheck(&userChoice, RewriteMenuItem, GoBackAdditionalSaveMenuItem);
            switch (userChoice) {
            case RewriteMenuItem: { // ������� � �����������
                PrintTextInFile(text, path);
                break;
            }
            case CreateNewFileMenuItem: { // ������� � ��������� ������ �����
                errorCode = ErrorInPathInput;
                continue;
                break;
            }
            case GoBackAdditionalSaveMenuItem: { // ����� � ������� ����
                return GoBack;
            }
            }
        }
        else { // ���� ���� �� ����������
            PrintTextInFile(text, path);
        }
        cout << endl;
        cout << "������ ������� ���������." << endl;
        cout << endl;
        system("pause");
    } while (errorCode != NoError);
    return NoError;
}