#pragma once
#include <fstream>

#include "Table.h"

void PrintNamesOfColumns(const Table& table, std::ostream& output);

void PrintSymbols(const std::vector<Symbol>& symbols, std::ostream& output);

void PrintNextSymbols(const TableStr& str, const std::set<std::string>& symbols, std::ostream& output);

void PrintTestTable(const Table& table);