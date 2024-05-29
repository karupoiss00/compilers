#include "PrintTable.h"

void PrintNamesOfColumns(const Table& table, std::ostream& output)
{
	output << "\t";
	for (const std::string s : table.symbols)
	{
		output << "\'" << s << "\'\t";
	}
	output << std::endl;
}

void PrintSymbols(const std::vector<Symbol>& symbols, std::ostream& output)
{
	for (size_t i = 0; i < symbols.size(); i++)
	{
		output << "\'" << symbols[i] << "\'";
		if (i + 1 != symbols.size())
		{
			output << ", ";
		}
	}
	output << "\t";
}

void PrintNextSymbols(const TableStr& str, const std::set<std::string>& symbols, std::ostream& output)
{
	for (const std::string& s : symbols)
	{
		if (str.nextSymbols.find(s) == str.nextSymbols.end())
		{
			output << "\t";
		}
		else
		{
			PrintSymbols(str.nextSymbols.at(s), output);
		}
	}
}

void PrintTable(const Table& table, std::ostream& output)
{
	PrintNamesOfColumns(table, output);

	for (const TableStr& str : table.strings)
	{
		PrintSymbols(str.symbols, output);
		PrintNextSymbols(str, table.symbols, output);
		output << std::endl;
	}
}