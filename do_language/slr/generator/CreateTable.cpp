#include "CreateTable.h"

void AddSymbolsFromRightPart(const Rule& rule, std::set<std::string>& symbols)
{
	for (const std::string str : rule.rightPart)
	{
		if (std::find(symbols.begin(), symbols.end(), str) == symbols.end())
		{
			symbols.insert(str);
		}
	}
}

std::set<std::string> GetAllSymbols(const std::vector<Rule>& grammar)
{
	std::set<std::string> symbols;

	for (const Rule& rule : grammar)
	{
		if (std::find(symbols.begin(), symbols.end(), rule.nonTerminal) == symbols.end())
		{
			symbols.insert(rule.nonTerminal);
		}
		AddSymbolsFromRightPart(rule, symbols);
	}

	return symbols;
}

void AddDirectionSymbolsOfNonTerminal()
{}

void AddDirectionSymbols(TableStr& str, const std::vector<Symbol>& directionSymbols, const std::vector<Rule>& grammar)
{
	for (const Symbol& symbol : directionSymbols)
	{
		if (str.nextSymbols.find(symbol.name) != str.nextSymbols.end())
		{
			if (std::find(str.nextSymbols[symbol.name].begin(), str.nextSymbols[symbol.name].end(), symbol) == str.nextSymbols[symbol.name].end())
			{
				str.nextSymbols[symbol.name].push_back(symbol);
			}
		}
		else
		{
			str.nextSymbols[symbol.name] = { symbol };
		}
	}
}

void AddEndDirectionSymbols(TableStr& str, const std::vector<Symbol>& directionSymbols, size_t numOfRule)
{
	for (const Symbol& symbol : directionSymbols)
	{
		Symbol endSymbol;
		endSymbol.name = END_SYMBOL_IN_TABLE;
		endSymbol.numOfRule = numOfRule;
		if (str.nextSymbols.find(symbol.name) != str.nextSymbols.end())
		{
			if (std::find(str.nextSymbols[symbol.name].begin(), str.nextSymbols[symbol.name].end(), endSymbol) == str.nextSymbols[symbol.name].end())
			{
				str.nextSymbols[symbol.name].push_back(endSymbol);
			}
		}
		else
		{
			str.nextSymbols[symbol.name] = { endSymbol };
		}
	}
}

bool HasStateInTable(const std::vector<TableStr>& tableStrs, const std::vector<Symbol>& symbolsOfState)
{
	bool hasStateInTable = false;

	for (const TableStr& tableStr : tableStrs)
	{
		if (tableStr.symbols == symbolsOfState)
		{
			return true;
		}
	}

	return false;
}

void DefineNextSymbols(const std::vector<Rule>& grammar, const size_t numOfRule, const size_t numOfRightPart, TableStr& str)
{
	std::string symbolName = grammar[numOfRule].rightPart[numOfRightPart];
	Symbol symbol;
	symbol.name = symbolName;
	symbol.numOfRule = numOfRule;
	symbol.numOfRightPart = numOfRightPart;
	bool isNonTerminal = IsNonTerminal(symbol.name, grammar);
	if (isNonTerminal)
	{
		std::vector<Symbol> directionSymbols;
		directionSymbols.push_back(symbol);
		std::vector<Rule> rules = GetNonterminalRules(grammar, symbolName);
		for (const Rule& r : rules)
		{
			directionSymbols.insert(directionSymbols.end(), r.directionSymbols.begin(), r.directionSymbols.end());
		}
		AddDirectionSymbols(str, directionSymbols, grammar);
		
	}
	if (symbol.name == END_SYMBOL)
	{
		AddEndDirectionSymbols(str, { symbol }, symbol.numOfRule.value());
		return;
	}
	AddDirectionSymbols(str, { symbol }, grammar);
}

void AddInfoInString(TableStr& str, const std::vector<Symbol>& symbols, const std::vector<Rule>& grammar)
{
	for (const Symbol& s : symbols)
	{
		if (!s.numOfRule.has_value() || !s.numOfRightPart.has_value())
		{
			continue;
		}
		str.symbols.push_back(s);
		bool isTheEndOfRule = grammar[s.numOfRule.value()].rightPart.size() - 1 == s.numOfRightPart.value();
		if (isTheEndOfRule)
		{
			std::vector<Symbol> directionSymbols = DefineDirectionSymbolsAfterNonTerminal({}, grammar[s.numOfRule.value()].nonTerminal, grammar);
			AddEndDirectionSymbols(str, directionSymbols, s.numOfRule.value());
			continue;
		}
		DefineNextSymbols(grammar, s.numOfRule.value(), s.numOfRightPart.value() + 1, str);
	}
}

void AddNewStrings(Table& table, const size_t numOfStr, const std::vector<Rule>& grammar)
{
	const TableStr& tableStr = table.strings[numOfStr];
	std::vector<TableStr> newStrs;
	for (auto nextSymbol : tableStr.nextSymbols)
	{
		if (HasStateInTable(table.strings, nextSymbol.second) || HasStateInTable(newStrs, nextSymbol.second))
		{
			continue;
		}
		TableStr newStr;
		AddInfoInString(newStr, nextSymbol.second, grammar);
		if (newStr.symbols.size() != 0)
		{
			newStrs.push_back(newStr);
		}
	}
	table.strings.insert(table.strings.end(), newStrs.begin(), newStrs.end());
	if (numOfStr + 1 < table.strings.size())
	{
		AddNewStrings(table, numOfStr + 1, grammar);
	}
}

Table CreateTable(const std::vector<Rule>& grammar)
{
	Table table;
	table.symbols = GetAllSymbols(grammar);

	TableStr firstStr;
	Symbol symbolOfFirstStr;
	symbolOfFirstStr.name = grammar[0].nonTerminal;
	firstStr.symbols.push_back(symbolOfFirstStr);
	AddDirectionSymbols(firstStr, grammar[0].directionSymbols, grammar);

	Symbol s;
	s.name = "OK";

	firstStr.nextSymbols[grammar[0].nonTerminal].push_back(s);

	for (size_t i = 1; i < grammar.size(); i++)
	{
		const Rule& r = grammar[i];
		if (r.nonTerminal == symbolOfFirstStr.name)
		{
			AddDirectionSymbols(firstStr, r.directionSymbols, grammar);
		}
	}

	table.strings.push_back({ firstStr });
	AddNewStrings(table, 0, grammar);

	return table;
}