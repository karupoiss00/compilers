#include "Syntax.h"

const std::map<char, TokenType> OPERATORS_MAP = 
{
	{ '+', TokenType::ADDITION },
	{ '-', TokenType::SUBTRACTION },
	{ '*', TokenType::MULTIPLICATION },
	{ '/', TokenType::DIVISION },
};

bool Syntax::isOperator(char ch)
{
	return OPERATORS_MAP.find(ch) != OPERATORS_MAP.end();
}

TokenType Syntax::GetOperatorToken(char ch)
{
	return OPERATORS_MAP.at(ch);
}