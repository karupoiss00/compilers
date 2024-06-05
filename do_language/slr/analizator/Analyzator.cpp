#include "Analizator.h"

std::vector<std::string> tokens;
std::vector<std::string> states;

void GenerateTokensFromFile(std::istream& inputFile)
{
	std::string str;

	while (std::getline(inputFile, str))
	{
		std::vector<std::string> tokensOfStr = Split(str, " ");
		tokens.insert(tokens.end(), tokensOfStr.begin(), tokensOfStr.end());
	}

	if (tokens.empty())
	{
		throw std::runtime_error("Input file is empty");
	}
}

std::optional<std::string> ReadToken()
{
	if (tokens.empty())
	{
		return std::nullopt;
	}

	return tokens[0];
}

void PopToken()
{
	if (!tokens.empty())
	{
		tokens.erase(tokens.begin());
	}
}

std::optional<std::string> GetState()
{
	if (states.empty())
	{
		return std::nullopt;
	}
	return states[0];
}

void AppendState(std::string state)
{
	states.insert(states.begin(), state);
}

void PopState()
{
	if (!states.empty())
	{
		states.erase(states.begin());
	}
}

std::optional<TableStr> GetTableStr(const Table& table, const std::vector<Symbol>& state)
{
	for (TableStr str : table.strings)
	{
		if (state == str.symbols)
		{
			return str;
		}
	}
	return std::nullopt;
}

void Analyze(const Table& table, const std::vector<Rule>& grammar, std::istream& input)
{
	GenerateTokensFromFile(input);

	std::vector<std::vector<Symbol>> stateStack;
	std::vector<std::string> tokensStack;

	if (table.strings.empty())
	{
		throw std::runtime_error("Table is empty!");
	}

	TableStr currentStr = table.strings[0];

	bool isAnalyzing = true;

	while (isAnalyzing)
	{
		bool isState = GetState() != std::nullopt;

		std::optional<std::string> symbol = isState ? GetState() : ReadToken();

		if (!symbol.has_value())
		{
			throw std::runtime_error("Unexpected end");
		}

		std::cout << "Current token: " << symbol.value() << std::endl;
		std::cout << "State stack: ";
		for (std::vector<Symbol>& state : stateStack)
		{
			for (Symbol& s : state)
			{
				std::cout << s << " ";
			}
			std::cout << "|| ";
		}
		std::cout << std::endl;
		for (std::string& token : tokensStack)
		{
			std::cout << token << " ";
		}
		std::cout << std::endl << std::endl;

		std::vector<Symbol> nextState = currentStr.nextSymbols[symbol.value()];

		if (nextState.size() == 1 && nextState[0].name == "OK")
		{
			isAnalyzing = false;
			continue;
		}

		if (nextState.size() == 1 && nextState[0].name == "R")
		{
			size_t rowIndex = nextState[0].numOfRule.value();
			Rule row = grammar[rowIndex];

			for (std::string& token : tokensStack)
			{
				std::cout << token << " ";
			}
			std::cout << std::endl << std::endl;
			std::vector<std::string> sliced = {""};

			if (row.rightPart.back() == "#")
			{
				std::copy(tokensStack.begin(), tokensStack.end() - 1, sliced.begin());
			}
			else
			{
				std::copy(tokensStack.begin(), tokensStack.end(), sliced.begin());

			}

			std::reverse(sliced.begin(), sliced.end());

			std::vector<std::string> slicedWithEnd = sliced;
			slicedWithEnd.push_back("#");

			if (symbol == "#" && row.rightPart == slicedWithEnd || row.rightPart == sliced)
			{
				stateStack.erase(stateStack.begin(), stateStack.begin() + row.rightPart.size());
				tokensStack.erase(tokensStack.begin(), tokensStack.begin() + row.rightPart.size());;

				AppendState(row.nonTerminal);
				if (stateStack.size() > 0)
				{
					currentStr = GetTableStr(table, stateStack[0]).value();
				}
				else
				{
					currentStr = table.strings[0];
				}
				continue;
			}
			else
			{
				std::stringstream msg("Unable to collapse expression ");
				msg << nextState[0];
				throw std::runtime_error(msg.str());
			}
		}
		else
		{
			stateStack.insert(stateStack.begin(), nextState);
			tokensStack.insert(tokensStack.begin(), symbol.value());
		}

		if (isState)
		{
			PopState();
		}
		else
		{
			PopToken();
		}

		if (GetTableStr(table, nextState) == std::nullopt)
		{
			throw std::runtime_error("Unknown state");
		}

		currentStr = GetTableStr(table, nextState).value();
	}
}