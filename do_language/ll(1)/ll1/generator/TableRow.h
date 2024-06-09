#pragma once
#include <string>
#include <set>
#include <optional>

struct TableRow
{
	std::string symbol;
	std::set<std::string> directionSymbols; /*направл€ющие символы*/
	bool shift = false; /*сдвиг*/
	bool error = false; /*ошибка*/
	std::optional<size_t> pointer; /*указатель*/
	bool stack = false; /*заносить в стек или нет*/
	bool end = false; /*конец разбора*/
};