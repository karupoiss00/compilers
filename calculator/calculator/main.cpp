#include <iostream>
#include <string>
#include "TokenType.h"
#include "Lexer.h"

using namespace std;

int main() 
{
	string expression = "1 + 2 - 3 / 10 * 23 + 1";

	Lexer lexer(expression);

	auto tokens = lexer.Tokenize();

	for (auto token : tokens)
	{
		cout << token.ToString() << endl;
	}

	return 0;
}