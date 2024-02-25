#include <regex>
#include <iostream>
#include "Lexer.h"

const std::vector<std::pair<TokenType, std::string>> TOKEN_TYPE_TO_REGEX_MAP = {
	{TokenType::FUNCTION, R"(^(func)\b)"},
	{TokenType::CONST, R"(^(const)\b)"},
	{TokenType::ARRAY, R"(^(array)\b)"},
	{TokenType::VAR, R"(^(var)\b)"},
	{TokenType::INT_TYPE, R"(^(int)\b)"},
	{TokenType::FLOAT_TYPE, R"(^(float)\b)"},
	{TokenType::STRING_TYPE, R"(^(string)\b)"},
	{TokenType::BOOLEAN_TYPE, R"(^(boolean)\b)"},
	{TokenType::IF, R"(^\b(if)\b)"},
	{TokenType::ELSE, R"(^\b(else)\b)"},
	{TokenType::FOR, R"(^\b(for)\b)"},
	{TokenType::WHILE, R"(^\b(while)\b)"},
	{TokenType::PRINT, R"(^\b(print)\b)"},
	{TokenType::BOOLEAN_VALUE, R"(^\b(true|false)\b)"},
	{TokenType::NUMBER, R"(^(\d+))"},
	{TokenType::FLOAT_NUMBER, R"(^(\d+\.\d+))"},
	{TokenType::STRING_LITERAL, R"(^\"(.*)\")"},
	{TokenType::DOT, R"(^(\.))"},
	{TokenType::COMMA, R"(^(,))"},
	{TokenType::ARROW_RIGHT, R"(^(=>))"},
	{TokenType::MULTIPLICATION, R"(^(\*))"},
	{TokenType::DIVISION, R"(^(\/))"},
	{TokenType::ADDITION, R"(^(\+))"},
	{TokenType::SUBTRACTION, R"(^(-))"},
	{TokenType::EXCLAMATION_MARK, R"(^(!))"},
	{TokenType::AMPERSAND, R"(^(&))"},
	{TokenType::VERTICAL_LINE, R"(^(\|))"},
	{TokenType::EQUAL, R"(^(=))"},
	{TokenType::GREATER_THAN, R"(^(>))"},
	{TokenType::LESS_THAN, R"(^(<))"},
	{TokenType::LBRACE, R"(^(\{))"},
	{TokenType::RBRACE, R"(^(\}))"},
	{TokenType::LPAREN, R"(^(\())"},
	{TokenType::RPAREN, R"(^(\)))"},
	{TokenType::LBRACKET, R"(^(\[))"},
	{TokenType::RBRACKET, R"(^(\]))"},
	{TokenType::IDENTIFIER, R"(^\b([a-zA-Z_]+)\b)"},
};

std::string strip(const std::string &inpt)
{
    auto start_it = inpt.begin();
    auto end_it = inpt.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

Lexer::Lexer(std::string input)
	: m_input(input)
{
}

std::vector<Token> Lexer::Tokenize()
{
	bool unknownTokenEncountered = false;

	while (!m_input.empty() && !unknownTokenEncountered)
	{
		unknownTokenEncountered = true;

		for (auto [tokenType, tokenRegex] : TOKEN_TYPE_TO_REGEX_MAP)
		{
			m_input = strip(m_input);
			const std::regex regExp(tokenRegex, std::regex_constants::icase);
			std::smatch matches;

			if (!std::regex_search(m_input, matches, regExp))
			{
				continue;
			}

			auto tokenValue = matches[0];

			AddToken(tokenType, tokenValue);

			m_input = m_input.substr(tokenValue.length());
			unknownTokenEncountered = false;
			break;
		}
	}

	return m_tokens;
}

void Lexer::AddToken(TokenType type, std::optional<std::string> value)
{
	Token token(type, value);
	m_tokens.push_back(token);
}