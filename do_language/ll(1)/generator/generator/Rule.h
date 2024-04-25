#pragma once
#include <string>
#include <vector>
#include <set>

const std::string EMPTY_SYMBOL = "e";
const std::string END_SYMBOL = "#";

struct Rule
{
    std::string nonTerminal;
    std::vector<std::string> rightPart;
    std::set<std::string> directionSymbols;
};

bool IsNonTerminal(const std::string& str, const std::vector<Rule>& rules)
{
	for (const Rule rule : rules)
	{
		if (rule.nonTerminal == str)
		{
			return true;
		}
	}

	return false;
}