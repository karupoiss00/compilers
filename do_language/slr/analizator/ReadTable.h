#pragma once
#include <string>
#include <fstream>
#include <sstream>

#include "Table.h"
#include "StringHelpers.h"

Table ReadTable(const std::string& tableFileName);
std::set<std::string> GetSymbols(const std::string& str, std::map<size_t, std::string>& numOfColumns);
TableStr ReadTableStr(const std::string& str, const std::map<size_t, std::string>& numOfColumns);
std::vector<Symbol> GetState(const std::string& str);
size_t StringToSizeT(const std::string& str);