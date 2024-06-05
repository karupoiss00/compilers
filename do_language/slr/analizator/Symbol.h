#pragma once
#include <string>
#include <optional>
#include <ostream>

struct Symbol
{
	std::string name;
	std::optional<size_t> numOfRule;
	std::optional<size_t> numOfRightPart;

	bool operator==(const Symbol& other) const
	{
		return this->name == other.name
			&& this->numOfRule == other.numOfRule
			&& this->numOfRightPart == other.numOfRightPart;
	}
};

inline std::ostream& operator<<(std::ostream& stream, const Symbol& symbol)
{
	stream << symbol.name;
	if (symbol.numOfRule.has_value())
	{
		stream << "·" << symbol.numOfRule.value() + 1;
	}
	if (symbol.numOfRightPart.has_value())
	{
		stream << "·" << symbol.numOfRightPart.value() + 1;
	}
	return stream;
}