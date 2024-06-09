#include "Analizator.h"

std::vector<std::string> tokens;

void GenerateTokensFromFile(const std::string& inputFileName)
{
	std::ifstream input(inputFileName);

	if (!input.is_open())
	{
		throw std::runtime_error("Input file is not found");
	}

	std::string str;

	while (std::getline(input, str))
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

void Analyze(const std::vector<TableRow> table, const std::string& inputFileName)
{
	//–азбиваем выражение на токены
	GenerateTokensFromFile(inputFileName);

	size_t current = 0; /*номер строки, которую провер€ем*/
	std::vector<size_t> stack;
	bool isAnalyzed = true;
	while (isAnalyzed)
	{
		//ѕроверка строки под текущем номером
		TableRow state = table[current];
		//ѕроверка текущего токена на то, что он €вл€етс€ направл€ющим символом провер€емой строки
		bool isDirectionSymbol = std::find(state.directionSymbols.begin(), state.directionSymbols.end(), ReadToken().value()) != state.directionSymbols.end();
		//¬ случае, когда символ €вл€етс€ направл€ющим, пустой стек и в поле конца разбора - true,
		//разбор заканчиваетс€
		if (isDirectionSymbol && stack.empty() && state.end)
		{
			isAnalyzed = false;
			continue;
		}
		//¬ случае, когда символ не €вл€етс€ направл€ющим и поле ошибки - true,
		//выбрасиываетс€ исключение
		if (!isDirectionSymbol && state.error)
		{
			std::string msg = ReadToken().value() + " is incorrect symbol";
			throw std::exception(msg.c_str());
		}
		//≈сли текущий токен не направл€ющий символ
		if (!isDirectionSymbol)
		{
			//то переходим на следующую строку
			current++;
			//≈сли поле сдвига - true, то избавл€емс€ от текущего токена
			if (state.shift)
			{
				PopToken();
			}
			continue;
		}
		// ≈сли поле стека - true, то длбавл€ем в стек номер следующей строки
		if (state.stack)
		{
			stack.push_back(current + 1);
		}
		//≈сли текущий токен €вл€етс€ направл€ющим символом и есть указатель на строку,
		//то переходим на строку под номером, хрон€щемс€ в поле указател€
		if (isDirectionSymbol && state.pointer.has_value())
		{
			current = state.pointer.value();
		}
		//≈сли указател€ нет
		if (!state.pointer.has_value())
		{
			//то происходит переход на строку, под номером, хрон€щемс€ последним в стеке
			current = stack[stack.size() - 1];
			//ќчистка стека от этого номера строки
			stack.pop_back();
		}
		//≈сли поле сдвига - true, , то избавл€емс€ от текущего токена
		if (state.shift)
		{
			PopToken();
		}
	}
}