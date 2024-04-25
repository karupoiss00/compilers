#pragma once
#include "Rule.h"
#include "TableStr.h"
#include "GetDirectionSymbols.h"

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

std::optional<unsigned int> GetIndexOfNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal)
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

void AddNonterminals(const std::vector<Rule>& rules, std::vector<TableStr>& table)
{
	for (const Rule& rule : rules)
	{
		TableStr tableStr;
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

void AddOtherTableStrFromRightPart(const std::vector<Rule>& rules, std::vector<TableStr>& table, const Rule& rule)
{
	for (size_t i = 0; i < rule.rightPart.size(); i++)
	{
		const std::string& rightSymbol = rule.rightPart[i];
		TableStr tableStr;
		tableStr.symbol = rightSymbol;
		bool isNonTerminal = IsNonTerminal(rightSymbol, rules);
		tableStr.shift = !isNonTerminal;
		tableStr.error = true;
		if (isNonTerminal)
		{
			tableStr.directionSymbols = DefineNonTerminalDirectionSymbols(rightSymbol, rules);
			tableStr.shift = false;
			tableStr.stack = GetCountOfIdenticalNonterminals(rules, rightSymbol) > 1;
			tableStr.end = false;
			tableStr.pointer = GetIndexOfNonterminal(rules, rightSymbol);
		}
		else
		{
			std::set<std::string> directionSymbols = GetTerminalDirectionSymbols(rules, rightSymbol, rule.nonTerminal);
			tableStr.directionSymbols.insert(directionSymbols.begin(), directionSymbols.end());
			tableStr.end = rightSymbol == END_SYMBOL;
			tableStr.shift = rightSymbol != END_SYMBOL;
			bool isEndOfRule = i == rule.rightPart.size() - 1;
			if (!isEndOfRule)
			{
				tableStr.pointer = table.size() + 1;
			}
		}
		table.push_back(tableStr);
	}
}

std::vector<TableStr> CreateTable(const std::vector<Rule>& rules)
{
	std::vector<TableStr> table;

	AddNonterminals(rules, table);
	for (size_t i = 0; i < rules.size(); i++)
	{
		table[i].pointer = table.size();
		table[i].error = !HasNonTerminal(i + 1, rules, rules[i].nonTerminal);
		AddOtherTableStrFromRightPart(rules, table, rules[i]);
	}

	return table;
}