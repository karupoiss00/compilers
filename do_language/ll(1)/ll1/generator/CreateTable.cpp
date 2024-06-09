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

// Определение количества правил для нетерминала
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

//Добавление строк для нетерминалов
void AddNonterminals(const std::vector<Rule>& rules, std::vector<TableRow>& table)
{
	//Обход правил
	for (const Rule& rule : rules)
	{
		//Создание строки, в которую передается символ(название нетерминала) и направляющие символы для данного правила
		TableRow tableStr;
		tableStr.symbol = rule.nonTerminal;
		tableStr.directionSymbols = rule.directionSymbols;
		table.push_back(tableStr);
	}
}

// Определение направляющих символов для терминала
std::set<std::string> GetTerminalDirectionSymbols(const std::vector<Rule>& rules, const std::string& terminalName, const std::string& nonTerminalName)
{
	//Если символ пустой, то находятся символы, которые используются после нетерминала
	//Иначе направляющим символом является сам терминал
	std::set<std::string> directionSymbols;
	if (terminalName == EMPTY_SYMBOL)
	{
		return DefineDirectionSymbolsAfterNonTerminal(nonTerminalName, rules);
	}

	return { terminalName };
}

//Добавение строк для элементов правила
void AddOtherTableStrFromRightPart(const std::vector<Rule>& rules, std::vector<TableRow>& table, const Rule& rule)
{
	//Обход правила
	for (size_t i = 0; i < rule.rightPart.size(); i++)
	{
		//Создание строки, в которую передается элемент правила
		const std::string& rightSymbol = rule.rightPart[i];
		TableRow tableStr;
		tableStr.symbol = rightSymbol;
		bool isNonTerminal = IsNonTerminal(rightSymbol, rules);
		tableStr.error = true;
		tableStr.end = false;
		// Если элемент правила - нетерминал
		if (isNonTerminal)
		{
			//В строку передаются все направляющие символы для этого нетерминала
			tableStr.directionSymbols = DefineNonTerminalDirectionSymbols(rightSymbol, rules);
			//сдвига нет 
			tableStr.shift = false;
			//Добавлять в стек, если нетерминал не в конце правила
			tableStr.stack = IsStack(rule, i);
			//Определение указателя на строку
			tableStr.pointer = GetIndexOfNonterminal(rules, rightSymbol);
		}
		else /*если не является нетерминалом*/
		{
			//Определение направляющих символов для терминала
			std::set<std::string> directionSymbols = GetTerminalDirectionSymbols(rules, rightSymbol, rule.nonTerminal);
			tableStr.directionSymbols.insert(directionSymbols.begin(), directionSymbols.end());
			//Сдвиг происходит, если это не пустой символ и не конец строки
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

//Создает таблицу
std::vector<TableRow> CreateTable(const std::vector<Rule>& rules)
{
	std::vector<TableRow> table;

	//Добавление строк для нетерминалов
	AddNonterminals(rules, table);
	//Добавление укзателя для каждой строки нетерминала и определение флаг ошибки
	for (size_t i = 0; i < rules.size(); i++)
	{
		table[i].pointer = table.size();
		table[i].error = !HasNonTerminal(i + 1, rules, rules[i].nonTerminal);
		//Добавение строк для элементов правила
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