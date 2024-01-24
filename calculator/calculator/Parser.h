#pragma once
#include <vector>
#include <memory>
#include "Token.h"
#include "IExpression.h"

class Parser
{
public:
	Parser(std::vector<Token> tokens);
	
	std::vector<IExpressionPtr> Parse();

private:
	IExpressionPtr ParseExpression();
	IExpressionPtr ParseAddition();
	IExpressionPtr ParseMultiplication();
	IExpressionPtr ParseAtomic();

	double ParseNumberToken(Token const& token);

	Token const& Peek(size_t relativePosition = 0) const;
	bool MatchCurrentTokenType(TokenType tokenType);

	std::vector<Token> m_tokens;
	size_t m_currentPosition;
};