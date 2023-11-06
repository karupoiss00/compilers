#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"

class Lexer
{
public:
	Lexer(std::string input);
	std::vector<Token> Tokenize();

private:
	void AddToken(TokenType type, std::optional<std::string> value = std::nullopt);

	void TokenizeOperator();
	void TokenizeNumber();

	char Peek(size_t relativePosition = 0) const;
	char Next();

	std::string m_input;
	std::vector<Token> m_tokens;
	size_t m_currentPosition;
};