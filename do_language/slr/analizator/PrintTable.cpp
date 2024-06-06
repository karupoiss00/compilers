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

void PrintTestTable(const Table& table)
{
	std::ofstream testTable("../data_samples/test_table.xls");

	if (!testTable.is_open())
	{
		return;
	}

	PrintNamesOfColumns(table, testTable);

	for (const TableStr& str : table.strings)
	{
		PrintSymbols(str.symbols, testTable);
		PrintNextSymbols(str, table.symbols, testTable);
		testTable << std::endl;
	}
}