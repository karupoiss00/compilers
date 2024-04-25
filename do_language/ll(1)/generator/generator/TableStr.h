#pragma once
#include <string>
#include <set>
#include <optional>

struct TableStr
{
	std::string symbol;
	std::set<std::string> directionSymbols;
	bool shift = false;
	bool error = false;
	std::optional<unsigned int> pointer;
	bool stack = false;
	bool end = false;
};