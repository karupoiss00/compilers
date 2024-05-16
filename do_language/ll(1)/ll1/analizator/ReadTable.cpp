#include "ReadTable.h"

std::vector<TableRow> ReadTable(const std::string& grammarFileName)
{
    std::ifstream grammarFile(grammarFileName);

    if (!grammarFile.is_open())
    {
        throw std::runtime_error("Grammar file is not found");
    }

    std::vector<TableRow> table;

    {
        std::string str;
        getline(grammarFile, str);
        while (getline(grammarFile, str))
        {
            table.push_back(ReadTableRow(str));
        }
    }

    return table;
}

TableRow ReadTableRow(const std::string& tableRowStr)
{
    TableRow tableRow;

    std::vector<std::string> splitedStr = Split(tableRowStr, ";");

    if (splitedStr.size() != 8)
    {
        throw std::logic_error("Incorrected quantity of parts of row");
    }

    tableRow.symbol = splitedStr[1];
    tableRow.directionSymbols = ReadDirectionSymbols(splitedStr[2]);
    tableRow.shift = splitedStr[3] == "+";
    tableRow.error = splitedStr[4] == "+";
    tableRow.pointer = ReadPointer(splitedStr[5]);
    tableRow.stack = splitedStr[6] == "+";
    tableRow.end = splitedStr[7] == "+";

    return tableRow;
}

std::set<std::string> ReadDirectionSymbols(const std::string& directionSymbolsStr)
{
    std::vector<std::string> dirtectionSymbols = Split(directionSymbolsStr, ", ");
    return std::set<std::string>(dirtectionSymbols.begin(), dirtectionSymbols.end());
}

std::optional<size_t> ReadPointer(const std::string& pointerStr)
{
    if (pointerStr == "NULL")
    {
        return std::nullopt;
    }

    std::stringstream stream(pointerStr);
    size_t pointer;
    stream >> pointer;

    return --pointer;
}