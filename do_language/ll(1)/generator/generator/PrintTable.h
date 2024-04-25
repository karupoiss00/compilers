#pragma once
#include "TableStr.h"

void PrintDirectionSymbols(const TableStr& tableStr, std::ofstream& outputFile)
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

void PrintBoolValue(const bool value, std::ofstream& outputFile)
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

void PrintPointer(const std::optional<unsigned int> pointer, std::ofstream& outputFile)
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

void PrintTable(const std::vector<TableStr>& table, std::ofstream& outputFile)
{
    outputFile << "index;symbol;directionSymbols;shift;error;pointer;stack;end" << std::endl;

    for (size_t i = 0; i < table.size(); i++)
    {
        const TableStr& tableStr = table[i];
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