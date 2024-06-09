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
	//–азбиваем выражение на токены
	GenerateTokensFromFile(input);

	std::vector<std::vector<Symbol>> stateStack;
	std::vector<std::string> tokensStack;

	//ѕроверка таблицы на пустоту
	if (table.strings.empty())
	{
		throw std::runtime_error("Table is empty!");
	}

	//–азбор начинаетс€ с первой строки в таблице
	TableStr currentStr = table.strings[0];

	bool isAnalyzing = true;

	while (isAnalyzing)
	{
		//ѕроверка текущего символа на токен
		bool isState = GetState() != std::nullopt;

		std::optional<std::string> symbol = isState ? GetState() : ReadToken();

		//≈сли не осталось ни токенов, ни состо€ний дл€ разбора, то выбрасываетс€ исключение
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

		//ќпредел€ем следующее состо€ние
		std::vector<Symbol> nextState = currentStr.nextSymbols[symbol.value()];

		//≈сли следующее состо€ние - состо€ние завершени€ разбора, то разбор завершаетс€
		if (nextState.size() == 1 && nextState[0].name == "OK")
		{
			isAnalyzing = false;
			continue;
		}

		//≈сли следующее состо€ние - состо€ние свертывани€, то происходит проверка свертывани€ токенов из стека в правило
		//»наче пополн€ем стеки состо€ний и токенов слеующим состо€нием и текущим токеном
		if (nextState.size() == 1 && nextState[0].name == "R")
		{
			size_t rowIndex = nextState[0].numOfRule.value();
			Rule row = grammar[rowIndex];

			auto end = row.rightPart.back() == "#"
				? tokensStack.begin() + (row.rightPart.size() - 1)
				: tokensStack.begin() + row.rightPart.size();

			std::vector<std::string> sliced(tokensStack.begin(), end);

			std::reverse(sliced.begin(), sliced.end());

			std::vector<std::string> slicedWithEnd = sliced;
			slicedWithEnd.push_back("#");

			//≈сли токены из стека свертываютс€ в правило, то очищаем стек токенов и состо€ний
			if (symbol == "#" && row.rightPart == slicedWithEnd || row.rightPart == sliced)
			{
				auto stateEnd = row.rightPart.back() == "#"
					? stateStack.begin() + (row.rightPart.size() - 1)
					: stateStack.begin() + row.rightPart.size();
				auto tokensEnd = row.rightPart.back() == "#"
					? tokensStack.begin() + (row.rightPart.size() - 1)
					: tokensStack.begin() + row.rightPart.size();
				stateStack.erase(stateStack.begin(), stateEnd);
				tokensStack.erase(tokensStack.begin(), tokensEnd);

				//ƒобавл€етс€ в список состо€ний нетерминал, полученный после свертывани€ 
				AppendState(row.nonTerminal);
				//ѕроверка стека состо€ний на пустоту
				if (stateStack.size() > 0)
				{
					//≈сли стек состо€ний не пустой, то следующее состо€ние дл€ разбора беретс€ из стека 
					currentStr = GetTableStr(table, stateStack[0]).value();
				}
				else
				{
					//≈сли стек состо€ний пустой, то разбираетс€ перва€ строка
					currentStr = table.strings[0];
				}
				// онец разбора текущего состо€ни€
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

		//≈сли текущий символ €вл€етс€ состо€нием, то очищаем список состо€ни€ от текущего нетерминала,
		//иначе очищаем список токенов от текущего символа
		if (isState)
		{
			PopState();
		}
		else
		{
			PopToken();
		}

		//ѕровер€ем, что в таблице есть информаци€ о следующем состо€нии
		if (GetTableStr(table, nextState) == std::nullopt)
		{
			throw std::runtime_error("Unknown state");
		}

		//ѕереход к разбору следующего состо€ни€
		currentStr = GetTableStr(table, nextState).value();
	}
}