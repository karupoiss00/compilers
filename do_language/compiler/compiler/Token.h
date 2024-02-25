#pragma once
#include <string>
#include <map>

#include "TokenType.h"

class Token
{
public:
	Token(TokenType type, std::string value);

	TokenType GetType() const;
	std::string GetValue() const;

	std::string ToString() const;

	bool operator==(Token const& rhs) const;
private:
	std::string TokenTypeToString() const;

	TokenType m_type;
	std::string m_value;
};