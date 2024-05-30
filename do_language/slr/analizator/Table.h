#pragma once
#include <vector>
#include <string>
#include <optional>
#include <map>
#include <set>

#include "Symbol.h"

const std::string END_SYMBOL_IN_TABLE = "R";

struct TableStr
{
	std::vector<Symbol> symbols;
	std::map<std::string, std::vector<Symbol>> nextSymbols;
};

struct Table
{
	std::set<std::string> symbols;
	std::vector<TableStr> strings;
};