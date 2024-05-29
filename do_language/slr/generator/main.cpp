#include <iostream>
#include <fstream>

#include "ReadGrammar.h"
#include "CreateTable.h"
#include "PrintTable.h"

using namespace std;

struct Args
{
    string inputFileName, outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    optional<Args> args = ParseArgs(argc, argv);
    if (args == nullopt)
    {
        return 1;
    }

    ifstream inputFile(args->inputFileName);
    if (!inputFile.is_open())
    {
        cout << "Input file is not found: " << args->inputFileName << endl;
        return 1;
    }

    ofstream outputFile(args->outputFileName);
    if (!outputFile.is_open())
    {
        cout << "Output file is not found: " << args->outputFileName << endl;
        return 1;
    }

    vector<Rule> grammar = ReadGrammar(inputFile);

    for (const Rule& rule : grammar)
    {
        cout << rule.nonTerminal << " -> ";
        for (const string& str : rule.rightPart)
        {
            cout << str << " ";
        }
        cout << "/ ";
        for (const Symbol& s : rule.directionSymbols)
        {
            cout << s.name;
            if (s.numOfRule.has_value())
            {
                cout << s.numOfRule.value() + 1;
            }
            if (s.numOfRule.has_value())
            {
                cout << s.numOfRightPart.value() + 1;
            }
            cout << " | ";
        }
        cout << endl;
    }

    Table table = CreateTable(grammar);
    PrintTable(table, outputFile);

    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid quantity of arguments" << endl;
        return nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];

    return args;
}