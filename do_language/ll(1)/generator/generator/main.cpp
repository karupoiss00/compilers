#include <iostream>
#include <optional>
#include <fstream>
#include <iostream>

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

    vector<Rule> rules = ReadGrammar(inputFile);
    vector<TableStr> table = CreateTable(rules);
    PrintTable(table, outputFile);
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