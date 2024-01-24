#pragma once
#include <string>
#include <optional>

#include "TokenType.h"

class Token
{
public:
	Token(TokenType type, std::optional<std::string> value = std::nullopt);

	TokenType GetType() const;
	std::optional<std::string> GetValue() const;

	std::string ToString() const;

	bool operator==(Token const& rhs) const;
private:
	std::string TokenTypeToString() const;

	TokenType m_type;
	std::optional<std::string> m_value;
};