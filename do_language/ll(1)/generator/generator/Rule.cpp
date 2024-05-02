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