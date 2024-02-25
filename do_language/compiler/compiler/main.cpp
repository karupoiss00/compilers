#include <iostream>
#include <string>
#include "Lexer.h"

using namespace std;

int main(int argc, char* argv[])
{
	string input;
	string line;

	while (getline(cin, line))
	{
		input += line;
	}

	Lexer lexer(input);

	for (auto token : lexer.Tokenize())
	{
		cout << token.ToString() << " ";
	}

	return 0;
}