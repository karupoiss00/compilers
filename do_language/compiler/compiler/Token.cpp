#include <format>
#include "Token.h"

Token::Token(TokenType type, std::string value)
	: m_type(type)
	, m_value(move(value))
{
}

TokenType Token::GetType() const
{
	return m_type;
}

std::string Token::GetValue() const
{
	return m_value;
}


std::string Token::TokenTypeToString() const
{
	try
	{
		return TOKEN_TYPE_TO_NAME_MAP.at(m_type);
	}
	catch (...)
	{
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
	return std::format(R"({} {})", TokenTypeToString(), m_value);
}