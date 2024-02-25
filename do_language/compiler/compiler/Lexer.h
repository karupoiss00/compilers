#pragma once
#include <optional>
#include "ILexer.h"

class Lexer : public ILexer
{
public:
	Lexer(std::string input);

	std::vector<Token> Tokenize() override;

private:
	std::optional<Token> ParseNextToken();

	std::string m_input;
	std::vector<Token> m_tokens;
};