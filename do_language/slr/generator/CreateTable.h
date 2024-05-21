#pragma once
#include <iostream>

#include "Table.h"
#include "Rule.h"
#include "GetDirectionSymbols.h"

#include "CreateTable.h"

void AddSymbolsFromRightPart(const Rule& rule, std::set<std::string>& symbols);

std::set<std::string> GetAllSymbols(const std::vector<Rule>& grammar);

void AddDirectionSymbols(TableStr& str, const std::vector<Symbol>& directionSymbols);

void AddEndDirectionSymbols(TableStr& str, const std::vector<Symbol>& directionSymbols, size_t numOfRule);

bool HasStateInTable(const std::vector<TableStr>& tableStrs, const std::vector<Symbol>& symbolsOfState);

void AddInfoInString(TableStr& str, const std::vector<Symbol>& symbols, const std::vector<Rule>& grammar);

void AddNewStrings(Table& table, const size_t numOfStr, const std::vector<Rule>& grammar);

Table CreateTable(const std::vector<Rule>& grammar);