#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestlab2sem7
{
    TEST_CLASS(UnitTestlab2sem7)
    {
    public:
#pragma region ValidateDateTests
        TEST_METHOD(ValidateDateTest1)
        {
            wstring date = L"01/02/2000";
            bool actual = ValidateDate(date);
            bool expected = true;
            Assert::IsTrue(actual == expected);
        }
        TEST_METHOD(ValidateDateTest2)
        {
            wstring date = L"101/202/000";
            bool actual = ValidateDate(date);
            bool expected = false;
            Assert::IsTrue(actual == expected);
        }
#pragma endregion

#pragma region workWithDBTests
        TEST_METHOD(GetJournalRecordsTest)
        {
            bool success = true;
            vector<record> actual;
            GetJournalRecords(actual, L"testDB.db");
            vector<record> expected = {
                {1, L"05/10/2022", 1, L"Лукойл", 24370, 40, 10, 400},
                {2, L"06/10/2022", 2, L"Роснефть", 24470, 50, 10, 500},
                {3, L"07/10/2022", 3, L"Газпромнефть", 24570, 60, 10, 600},
                {4, L"08/10/2022", 1, L"Лукойл", 24670, 50, 20, 1000} };
            for (int i = 0; i < expected.size(); i++) {
                if (actual[i] == expected[i]) {
                    success = true;
                }
                else {
                    success = false;
                }
            }
            Assert::IsTrue(success);
        }
        TEST_METHOD(GetGasBrandsTest)
        {
            bool success = true;
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
            Assert::IsTrue(success);
        }
        TEST_METHOD(GetIDTest)
        {
            int actual;
            wstring query = L"SELECT id FROM gasBrands WHERE brand = 'Роснефть';";
            GetID(&actual, query, L"testDB.db");
            int expected = 2;
            Assert::IsTrue(actual == expected);
        }
        TEST_METHOD(GetAverageBetweenRefuelingTest)
        {
            bool success = true;
            averageBetweenRefueling abr;
            wstring firstDate = L"05/10/2022";
            wstring secondDate = L"08/10/2022";
            GetAverageBetweenRefueling(abr, firstDate, secondDate, L"testDB.db");
            averageBetweenRefueling actual;
            // TODO: добавить
            averageBetweenRefueling expected = {  };
            if (actual == expected) {
                success = true;
            }
            else {
                success = false;
            }
            Assert::IsTrue(success);
        }
        TEST_METHOD(GetGasBrandStatsTest)
        {
            bool success = true;
            vector<gasBrandStats> actual;
            GetGasBrandStats(actual, L"testDB.db");
            // TODO: добавить
            vector<gasBrandStats> expected = {  };
            for (int i = 0; i < expected.size(); i++) {
                if (actual[i] == expected[i]) {
                    success = true;
                }
                else {
                    success = false;
                }
            }
            Assert::IsTrue(success);
        }
#pragma endregion
    };
}
