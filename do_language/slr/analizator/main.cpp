#include <iostream>
#include <optional>
#include <fstream>

#include "ReadTable.h"
#include "ReadGrammar.h"

using namespace std;

struct Args
{
    string inputFileName, tableFileName, grammarFileName;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    optional<Args> args = ParseArgs(argc, argv);

    if (!args.has_value())
    {
        return 1;
    }

    Table table = ReadTable(args->tableFileName);

    ifstream grammarFile(args->grammarFileName);
    if (!grammarFile.is_open())
    {
        cout << "Grammar file is not found: " << args->inputFileName << endl;
        return 1;
    }

    std::vector<Rule> grammar = ReadGrammar(grammarFile);

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


    return 0;
}

optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "Invalid quantity of arguments" << endl;
        return nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.tableFileName = argv[2];
    args.grammarFileName = argv[3];

    return args;
}