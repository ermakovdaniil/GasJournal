#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <atlbase.h>
#include <atlconv.h>
#include "sqlite3.h"
#include "structures.h"

void CreateConnection(const std::wstring& filename, sqlite3* db);

void GetJournalRecords(std::vector<record>& list, const std::wstring& filename);

void GetGasBrands(std::vector<std::wstring>& listOfBrands, const std::wstring& filename);

void GetID(int* id, const std::wstring& query, const std::wstring& filename);

void AddRecord(std::wstring& query, const std::wstring& filename);

void GetAverageBetweenRefueling(averageBetweenRefueling& abr, std::wstring& firstDate, std::wstring& secondDate, const std::wstring& filename);

void GetGasBrandStats(std::vector<gasBrandStats>& gbs, const std::wstring& filename);