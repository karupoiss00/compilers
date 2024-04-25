#pragma once
#include <ostream>
#include <vector>

#include "TableRow.h"

void PrintDirectionSymbols(const TableRow& tableStr, std::ostream& outputFile);

void PrintBoolValue(const bool value, std::ostream& outputFile);

void PrintPointer(const std::optional<size_t> pointer, std::ostream& outputFile);

void PrintTable(const std::vector<TableRow>& table, std::ostream& outputFile);