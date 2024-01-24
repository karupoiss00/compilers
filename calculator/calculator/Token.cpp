#include <format>
#include "Token.h"

Token::Token(TokenType type, std::optional<std::string> value)
	: m_type(type)
	, m_value(move(value))
{
}

TokenType Token::GetType() const
{
	return m_type;
}

std::optional<std::string> Token::GetValue() const
{
	return m_value;
}


std::string Token::TokenTypeToString() const
{
	switch (m_type)
	{
	case TokenType::ADDITION:
		return "ADDITION";
	case TokenType::SUBTRACTION:
		return "SUBTRACTION";
	case TokenType::MULTIPLICATION:
		return "MULTIPLICATION";
	case TokenType::DIVISION:
		return "DIVISION";
	case TokenType::NUMBER:
		return "NUMBER";
	case TokenType::END_OF_FILE:
		return "END_OF_FILE";
	default:
		return "UNKNOWN_TOKEN";
	}
}

bool Token::operator==(Token const& rhs) const
{
	return this->GetType() == rhs.GetType()
		&& this->GetValue() == rhs.GetValue();
}

std::string Token::ToString() const
{
	auto value = m_value.has_value() ? *m_value : "";
	return std::format(R"({} {})", TokenTypeToString(), value);
}