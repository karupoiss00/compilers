#include "Rule.h"

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

std::optional<size_t> GetIndexOfNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal)
{
	for (size_t i = 0; i < rules.size(); i++)
	{
		if (rules[i].nonTerminal == nonTerminal)
		{
			return i;
		}
	}

	return std::nullopt;
}