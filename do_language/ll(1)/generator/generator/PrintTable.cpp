#include "PrintTable.h"

void PrintDirectionSymbols(const TableRow& tableStr, std::ostream& outputFile)
{
    int index = 0;
    for (const std::string& symbol : tableStr.directionSymbols)
    {
        outputFile << symbol;
        if (index != tableStr.directionSymbols.size() - 1)
        {
            outputFile << ", ";
        }
        index++;
    }
    outputFile << ";";
}

void PrintBoolValue(const bool value, std::ostream& outputFile)
{
    if (value)
    {
        outputFile << "+";
    }
    else
    {
        outputFile << "-";
    }
    outputFile << ";";
}

void PrintPointer(const std::optional<size_t> pointer, std::ostream& outputFile)
{
    if (pointer.has_value())
    {
        outputFile << pointer.value() + 1;
    }
    else
    {
        outputFile << "NULL";
    }
    outputFile << ";";
}

void PrintTable(const std::vector<TableRow>& table, std::ostream& outputFile)
{
    outputFile << "index;symbol;directionSymbols;shift;error;pointer;stack;end" << std::endl;

    for (size_t i = 0; i < table.size(); i++)
    {
        const TableRow& tableStr = table[i];
        outputFile << i + 1 << ";"
            << tableStr.symbol << ";";
        PrintDirectionSymbols(tableStr, outputFile);
        PrintBoolValue(tableStr.shift, outputFile);
        PrintBoolValue(tableStr.error, outputFile);
        PrintPointer(tableStr.pointer, outputFile);
        PrintBoolValue(tableStr.stack, outputFile);
        PrintBoolValue(tableStr.end, outputFile);
        outputFile << std::endl;
    }
}