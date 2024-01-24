#include <iostream>
#include <string>
#include "TokenType.h"
#include "Lexer.h"
#include "Parser.h"

using namespace std;

int main() 
{
	string expression;

	getline(cin, expression);

	Lexer lexer(expression);

	auto tokens = lexer.Tokenize();

	for (auto token : tokens)
	{
		cout << token.ToString() << endl;
	}

	Parser parser(tokens);
	try
	{
		vector<IExpressionPtr> expressions = parser.Parse();

		for (auto& expr : expressions)
		{
			cout << expr->Eval() << endl;
		}
	}
	catch (exception const& e)
	{
		cout << e.what() << endl;
	}
	
	return 0;
}