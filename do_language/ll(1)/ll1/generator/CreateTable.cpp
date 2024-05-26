#include "CreateTable.h"

bool HasNonTerminal(size_t beginIndex, const std::vector<Rule>& rules, const std::string& nonTerminalName)
{
	for (size_t i = beginIndex; i < rules.size(); i++)
	{
		if (rules[i].nonTerminal == nonTerminalName)
		{
			return true;
		}
	}

	return false;
}

int GetCountOfIdenticalNonterminals(const std::vector<Rule>& rules, const std::string& nonTerminal)
{
	int countOfNonterminals = 0;

	for (const Rule& rule : rules)
	{
		if (rule.nonTerminal == nonTerminal)
		{
			countOfNonterminals++;
		}
	}

	return countOfNonterminals;
}

void AddNonterminals(const std::vector<Rule>& rules, std::vector<TableRow>& table)
{
	for (const Rule& rule : rules)
	{
		TableRow tableStr;
		tableStr.symbol = rule.nonTerminal;
		tableStr.directionSymbols = rule.directionSymbols;
		table.push_back(tableStr);
	}
}

std::set<std::string> GetTerminalDirectionSymbols(const std::vector<Rule>& rules, const std::string& terminalName, const std::string& nonTerminalName)
{
	std::set<std::string> directionSymbols;
	if (terminalName == EMPTY_SYMBOL)
	{
		return DefineDirectionSymbolsAfterNonTerminal(nonTerminalName, rules);
	}

	return { terminalName };
}

void AddOtherTableStrFromRightPart(const std::vector<Rule>& rules, std::vector<TableRow>& table, const Rule& rule)
{
	for (size_t i = 0; i < rule.rightPart.size(); i++)
	{
		const std::string& rightSymbol = rule.rightPart[i];
		TableRow tableStr;
		tableStr.symbol = rightSymbol;
		bool isNonTerminal = IsNonTerminal(rightSymbol, rules);
		tableStr.error = true;
		tableStr.end = false;
		if (isNonTerminal)
		{
			tableStr.directionSymbols = DefineNonTerminalDirectionSymbols(rightSymbol, rules);
			tableStr.shift = false;
			tableStr.stack = IsStack(rule, i);
			tableStr.pointer = GetIndexOfNonterminal(rules, rightSymbol);
		}
		else
		{
			std::set<std::string> directionSymbols = GetTerminalDirectionSymbols(rules, rightSymbol, rule.nonTerminal);
			tableStr.directionSymbols.insert(directionSymbols.begin(), directionSymbols.end());
			tableStr.shift = rightSymbol != END_SYMBOL && rightSymbol != EMPTY_SYMBOL;
			tableStr.end = rightSymbol == END_SYMBOL;
			bool isEndOfRule = i == rule.rightPart.size() - 1;
			if (!isEndOfRule)
			{
				tableStr.pointer = table.size() + 1;
			}
		}
		table.push_back(tableStr);
	}
	if (rule.hasEnd && rule.rightPart[rule.rightPart.size() - 1] != END_SYMBOL)
	{
		TableRow tableStr;
		tableStr.directionSymbols.insert(END_SYMBOL);
		tableStr.symbol = END_SYMBOL;
		tableStr.error = true;
		tableStr.shift = true;
		tableStr.end = true;
		table.push_back(tableStr);
	}
}

std::vector<TableRow> CreateTable(const std::vector<Rule>& rules)
{
	std::vector<TableRow> table;

	AddNonterminals(rules, table);
	for (size_t i = 0; i < rules.size(); i++)
	{
		table[i].pointer = table.size();
		table[i].error = !HasNonTerminal(i + 1, rules, rules[i].nonTerminal);
		AddOtherTableStrFromRightPart(rules, table, rules[i]);
	}

	return table;
}

bool IsStack(const Rule& rule, const size_t index)
{
	size_t lastIndex = rule.rightPart.size() - 1;
	if (lastIndex != index)
	{
		return true;
	}
	return rule.hasEnd;
}