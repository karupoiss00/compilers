#pragma once
#include <string>
#include <optional>
#include <ostream>

struct SymbolPosition
{
	size_t numOfRule;
	size_t numOfRightPart;

	bool operator==(const SymbolPosition& other) const
	{
		return this->numOfRule == other.numOfRule
			&& this->numOfRightPart == other.numOfRightPart;
	}
};

struct Symbol
{
	std::string name;
	std::optional<SymbolPosition> position;

	bool operator==(const Symbol& other) const
	{
		if (this->position.has_value())
		{
			if (other.position.has_value())
			{
				return this->name == other.name
					&& this->position.value() == other.position.value();
			}
			return false;
		}
		if (other.position.has_value())
		{
			return false;
		}
		return this->name == other.name;
	}
};

inline std::ostream& operator<<(std::ostream& stream, const Symbol& symbol)
{
	stream << symbol.name;
	if (symbol.position.has_value())
	{
		stream << symbol.position.value().numOfRule + 1
			<< symbol.position.value().numOfRightPart + 1;
	}
	return stream;
}