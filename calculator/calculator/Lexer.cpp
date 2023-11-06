#include <cctype>
#include <map>
#include "Syntax.h"
#include "Lexer.h"

Lexer::Lexer(std::string input)
	: m_input(input)
	, m_currentPosition(0)
{
}

std::vector<Token> Lexer::Tokenize()
{
	while (m_currentPosition <= m_input.size())
	{
		char currentChar = Peek();

		if (std::isdigit(currentChar))
		{
			TokenizeNumber();
		}
		else if (Syntax::isOperator(currentChar))
		{
			TokenizeOperator();
		}
		else
		{
			Next();
		}
	}

	return m_tokens;
}

void Lexer::TokenizeOperator()
{
	char currentChar = Peek();
	auto operatorToken = Syntax::GetOperatorToken(currentChar);
	
	AddToken(operatorToken);
	Next();
}

void Lexer::TokenizeNumber()
{
	char currentChar = Peek();
	std::string value;

	while (std::isdigit(currentChar))
	{
		value += currentChar;
		currentChar = Next();
	}

	AddToken(TokenType::NUMBER, value);
	Next();
}

void Lexer::AddToken(TokenType type, std::optional<std::string> value)
{
	Token token(type, value);
	m_tokens.push_back(token);
}

char Lexer::Peek(size_t relativePosition) const
{
	size_t position = m_currentPosition + relativePosition;

	if (position >= m_input.size())
	{
		return '\0';
	}

	return m_input[position];
}

char Lexer::Next() 
{
	m_currentPosition++;

	return Peek();
}