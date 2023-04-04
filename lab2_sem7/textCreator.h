#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "enums.h"
#include "structures.h"

void CreateResultJournal(std::vector<std::wstring>& createdText, const std::vector<record>& recs);

void CreateInitialDataJournal(std::vector<std::wstring>& createdText, const std::vector<record>& recs);

void CreateResultGasBrands(std::vector<std::wstring>& createdText, const std::vector<std::wstring>& listOfGasBrands);

void CreateInitialDataGasBrands(std::vector<std::wstring>& createdText, const std::vector<std::wstring>& listOfGasBrands);

void CreateAverageBetweenRefuelingResult(std::vector<std::wstring>& createdText, const averageBetweenRefueling& abr, std::wstring& firstDate, std::wstring& secondDate);

void CreateBrandsStatsResult(std::vector<std::wstring>& createdText, const std::vector<gasBrandStats>& gbs);

void CreateTextFile(std::vector<std::wstring>& createdText, const int* userChoice);