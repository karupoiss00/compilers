#include <iostream>
#include <optional>
#include <vector>
#include <fstream>

#include "TableRow.h"
#include "ReadTable.h"
#include "Analizator.h"

using namespace std;

struct Args
{
    string inputFileName, grammarFileName;
};

optional<Args> ParseArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    optional<Args> args = ParseArgs(argc, argv);

    if (!args.has_value())
    {
        return 1;
    }

    vector<TableRow> table;

    try
    {
        table = ReadTable(args->grammarFileName);
    }
    catch (const runtime_error&)
    {
        return 1;
    }

    try
    {
        Analyze(table, args->inputFileName);
        cout << "OK!!!" << endl;
    }
    catch (const std::exception& e)
    {
        cout << "ERROR: " << e.what() << endl;
    }

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
    args.grammarFileName = argv[2];

    return args;
}