#include "CreateTable.h"

//Добавление в список символов из правила
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

//Получение списка всех элементов, которые используются в этой грамматике
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

//Добавление следующих состояний в заданную строку
void AddDirectionSymbols(TableStr& str, const std::vector<Symbol>& directionSymbols, const std::vector<Rule>& grammar)
{
	//Обход направляющих символов состояния данной строки
	for (const Symbol& symbol : directionSymbols)
	{
		//Проверка на то, что состояние для данного символа есть
		if (str.nextSymbols.find(symbol.name) != str.nextSymbols.end())
		{
			//Если состояние есть, то оно дополняется символом
			if (std::find(str.nextSymbols[symbol.name].begin(), str.nextSymbols[symbol.name].end(), symbol) == str.nextSymbols[symbol.name].end())
			{
				str.nextSymbols[symbol.name].push_back(symbol);
			}
		}
		else /*если состояния нет, то добавляет состояние для этого символа*/
		{
			str.nextSymbols[symbol.name] = { symbol };
		}
	}
}

//Добавление состояния свертывания в строку
void AddEndDirectionSymbols(TableStr& str, const std::vector<Symbol>& directionSymbols, size_t numOfRule)
{
	//Обход направляющих символов
	for (const Symbol& symbol : directionSymbols)
	{
		//Создается состояние свертывания
		Symbol endSymbol;
		endSymbol.name = END_SYMBOL_IN_TABLE;
		endSymbol.numOfRule = numOfRule;
		//Проверка на то, что этого состяния свертывания нет
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

//Проверка на то, что данное состояние уже разобрано в таблице
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

//Определение следующих состояний
void DefineNextSymbols(const std::vector<Rule>& grammar, const size_t numOfRule, const size_t numOfRightPart, TableStr& str)
{
	//Определяется символ для разбора
	std::string symbolName = grammar[numOfRule].rightPart[numOfRightPart];
	Symbol symbol;
	symbol.name = symbolName;
	symbol.numOfRule = numOfRule;
	symbol.numOfRightPart = numOfRightPart;
	bool isNonTerminal = IsNonTerminal(symbol.name, grammar);
	//Если символ является нетерминалом,
	//то направляющие символы этого нетерминалы допоплняют следующие состояния
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

//Добавляется информация в заданную строку
void AddInfoInString(TableStr& str, const std::vector<Symbol>& symbols, const std::vector<Rule>& grammar)
{
	for (const Symbol& s : symbols)
	{
		//Проверка на то, что есть информация о расположении символа в грамматике и символ не является концом строки
		if (!s.numOfRule.has_value() || !s.numOfRightPart.has_value() || s.name == END_SYMBOL)
		{
			continue;
		}
		//Добавляется символ в состояние строки
		str.symbols.push_back(s);
		bool isTheEndOfRule = grammar[s.numOfRule.value()].rightPart.size() - 1 == s.numOfRightPart.value();
		//Если символ находится в конце правила,
		//то определяем символы, которые находятся после нетерминала в грамматике
		//и добавляем состояние свертывания 
		if (isTheEndOfRule)
		{
			std::vector<Symbol> directionSymbols = DefineDirectionSymbolsAfterNonTerminal({}, grammar[s.numOfRule.value()].nonTerminal, grammar);
			AddEndDirectionSymbols(str, directionSymbols, s.numOfRule.value());
			continue;
		}
		//Определяются следующие состояния
		DefineNextSymbols(grammar, s.numOfRule.value(), s.numOfRightPart.value() + 1, str);
	}
}

//Разбор состояний из заданной строки
void AddNewStrings(Table& table, const size_t numOfStr, const std::vector<Rule>& grammar)
{
	const TableStr& tableStr = table.strings[numOfStr];
	std::vector<TableStr> newStrs;
	//Обход состояний в заданной строке
	for (auto nextSymbol : tableStr.nextSymbols)
	{
		//Проверка на то, что состояние уже разобрано
		if (HasStateInTable(table.strings, nextSymbol.second) || HasStateInTable(newStrs, nextSymbol.second))
		{
			continue;
		}
		//Создается новая строка и добавляется информация для разбираемого состояния
		TableStr newStr;
		AddInfoInString(newStr, nextSymbol.second, grammar);
		if (newStr.symbols.size() != 0)
		{
			newStrs.push_back(newStr);
		}
	}
	table.strings.insert(table.strings.end(), newStrs.begin(), newStrs.end());

	//Если есть еще строка, то проверяем ее на состояния
	if (numOfStr + 1 < table.strings.size())
	{
		AddNewStrings(table, numOfStr + 1, grammar);
	}
}

//Создание таблицы
Table CreateTable(const std::vector<Rule>& grammar)
{
	Table table;
	//Получение списка всех элементов, которые используются в этой грамматике
	table.symbols = GetAllSymbols(grammar);

	//Создание первой строки для первого правила
	TableStr firstStr;
	Symbol symbolOfFirstStr;
	symbolOfFirstStr.name = grammar[0].nonTerminal;
	firstStr.symbols.push_back(symbolOfFirstStr);
	
	//Добавление последующих состояний для первой строки
	AddDirectionSymbols(firstStr, grammar[0].directionSymbols, grammar);
	//Добавление состояния завершения разбора
	Symbol s;
	s.name = "OK";
	firstStr.nextSymbols[grammar[0].nonTerminal].push_back(s);

	//Добавление последующих состояний из альтернативных правил для нетерминала 
	for (size_t i = 1; i < grammar.size(); i++)
	{
		const Rule& r = grammar[i];
		//Если правило с концом строки, добавляется состояние свертывания правила
		if (r.rightPart.size() == 1 && r.rightPart[0] == END_SYMBOL)
		{
			Symbol endSymbol;
			endSymbol.name = END_SYMBOL_IN_TABLE;
			endSymbol.numOfRule = i;
			firstStr.nextSymbols[END_SYMBOL].push_back(endSymbol);
			continue;
		}
		if (r.nonTerminal == symbolOfFirstStr.name)
		{
			AddDirectionSymbols(firstStr, r.directionSymbols, grammar);
		}
	}

	table.strings.push_back({ firstStr });
	//Разбор последующих состояний из первой строки
	AddNewStrings(table, 0, grammar);

	return table;
}