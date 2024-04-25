#pragma once
#include <string>
#include <set>
#include <optional>

struct TableRow
{
	std::string symbol;
	std::set<std::string> directionSymbols;
	bool shift = false;
	bool error = false;
	std::optional<size_t> pointer;
	bool stack = false;
	bool end = false;
};