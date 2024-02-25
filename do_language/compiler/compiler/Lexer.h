#pragma once
#include "ILexer.h"

class Lexer : public ILexer
{
public:
	Lexer(std::string input);

	std::vector<Token> Tokenize() override;

private:
	void AddToken(TokenType type, std::optional<std::string> value = std::nullopt);

	std::string m_input;
	std::vector<Token> m_tokens;
};