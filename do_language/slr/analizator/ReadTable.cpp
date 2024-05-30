#include "ReadTable.h"

Table ReadTable(const std::string& tableFileName)
{
    std::ifstream grammarFile(tableFileName);

    if (!grammarFile.is_open())
    {
        throw std::runtime_error("Grammar file is not found");
    }

    Table table;

    {
        std::string str;
        std::map<size_t, std::string> numOfColumns;
        getline(grammarFile, str);
        table.symbols = GetSymbols(str, numOfColumns);
        while (getline(grammarFile, str))
        {
            table.strings.push_back(ReadTableStr(str, numOfColumns));
        }
    }

    return table;
}

std::set<std::string> GetSymbols(const std::string& str, std::map<size_t, std::string>& numOfColumns)
{
    std::set<std::string> neededSymbols;
    std::vector<std::string> symbols = Split(str, "\t");
    for (size_t i = 0; i < symbols.size(); i++)
    {   
        if (symbols[i].length() != 0)
        {
            numOfColumns[i] = symbols[i];
            neededSymbols.insert(RemoveSubstringInBeginAndEndOfString(symbols[i], "\'"));
        }
    }
    neededSymbols.erase("");
    return neededSymbols;
}

TableStr ReadTableStr(const std::string& str, const std::map<size_t, std::string>& numOfColumns)
{
    TableStr tableStr;

    std::vector<std::string> columns = Split(str, "\t");
    tableStr.symbols = GetState(columns[0]);

    for (size_t i = 1; i < columns.size(); i++)
    {
        if (columns[i].length() == 0)
        {
            continue;
        }
        std::vector<Symbol> state = GetState(columns[i]);
        std::string symbol = numOfColumns.at(i);
        tableStr.nextSymbols[symbol] = state;
    }

    return tableStr;
}


std::vector<Symbol> GetState(const std::string& str)
{
    std::vector<Symbol> symbols;
    std::vector<std::string> strSymbols = Split(str, ", ");

    for (size_t i = 0; i < strSymbols.size(); i++)
    {
        if (strSymbols[i].length() == 0)
        {
            continue;
        }
        Symbol symbol;
        std::string s = RemoveSubstringInBeginAndEndOfString(strSymbols[i], "\'");
        std::vector<std::string> strS = Split(s, "·");
        symbol.name = strS[0];
        if (strS.size() == 3)
        {
            symbol.numOfRule = StringToSizeT(strS[1]);
            symbol.numOfRightPart = StringToSizeT(strS[2]);
        }
        if (strS.size() == 2)
        {
            symbol.numOfRule = StringToSizeT(strS[1]);
        }
        symbols.push_back(symbol);
    }

    return symbols;
}

size_t StringToSizeT(const std::string& str)
{
    std::stringstream stream(str);
    size_t num;
    stream >> num;
    return --num;
}