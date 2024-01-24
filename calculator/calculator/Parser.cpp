#include <stdexcept>
#include <format>
#include "BinaryExpression.h"
#include "NumberExpression.h"
#include "Parser.h"

const Token EOF_TOKEN = Token(TokenType::END_OF_FILE);

Parser::Parser(std::vector<Token> m_tokens)
	: m_tokens(std::move(m_tokens))
	, m_currentPosition(0)
{

}

std::vector<IExpressionPtr> Parser::Parse()
{
	std::vector<IExpressionPtr> result;

	while (!MatchCurrentTokenType(TokenType::END_OF_FILE))
	{
		result.push_back(ParseExpression());
	}

	return result;
}

IExpressionPtr Parser::ParseExpression()
{
	return ParseAddition();
}

IExpressionPtr Parser::ParseAddition()
{
	IExpressionPtr result = ParseMultiplication();

	bool parsingAddition = true;
	while (parsingAddition)
	{
		if (MatchCurrentTokenType(TokenType::ADDITION))
		{
			result = make_shared<BinaryExpression>(result, ParseMultiplication(), '+');
			continue;
		}
		if (MatchCurrentTokenType(TokenType::SUBTRACTION))
		{
			result = make_shared<BinaryExpression>(result, ParseMultiplication(), '-');
			continue;
		}

		parsingAddition = false;
	}

	return result;
}

IExpressionPtr Parser::ParseMultiplication()
{
	IExpressionPtr result = ParseAtomic();

	bool parsingMultiplication = true;
	while (parsingMultiplication)
	{
		if (MatchCurrentTokenType(TokenType::MULTIPLICATION))
		{
			result = make_shared<BinaryExpression>(result, ParseAtomic(), '*');
			continue;
		}
		if (MatchCurrentTokenType(TokenType::DIVISION))
		{
			result = make_shared<BinaryExpression>(result, ParseAtomic(), '/');
			continue;
		}
		
		parsingMultiplication = false;
	}

	return result;
}

IExpressionPtr Parser::ParseAtomic()
{
	auto currentToken = Peek();

	if (MatchCurrentTokenType(TokenType::NUMBER))
	{
		double value = ParseNumberToken(currentToken);
		return std::make_shared<NumberExpression>(value);
	}

	auto msg = std::format("unknown atomic token {}", currentToken.ToString());
	throw std::logic_error(msg);
}

Token const& Parser::Peek(size_t relativePosition) const
{
	size_t position = m_currentPosition + relativePosition;

	if (position >= m_tokens.size())
	{
		return EOF_TOKEN;
	}

	return m_tokens[position];
}

bool Parser::MatchCurrentTokenType(TokenType tokenType)
{
	if (Peek().GetType() != tokenType)
	{
		return false;
	}

	m_currentPosition++;
	return true;
}

double Parser::ParseNumberToken(Token const& token)
{
	if (!token.GetValue().has_value())
	{
		auto msg = std::format("invalid number token state: {}", token.ToString());
		throw std::invalid_argument(msg);
	}

	try
	{
		return std::stod(*token.GetValue());
	}
	catch (...)
	{
		auto msg = std::format("{}: number parsing error", m_currentPosition);
		throw std::invalid_argument(msg);
	}
}