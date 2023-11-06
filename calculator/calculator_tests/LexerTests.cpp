#include <string>
#include <vector>
#include <catch2jest/catch2jest.hpp>
#include "../calculator/Token.h"
#include "../calculator/Lexer.h"

using namespace std;

void TestTokenizing(string expression, vector<Token> expectedTokens)
{
	Lexer lexer(expression);

	auto tokens = lexer.Tokenize();

	expect(tokens.size())->toEqual(expectedTokens.size());

	for (size_t i = 0; i < tokens.size(); i++)
	{
		expect(tokens[i].GetType())->toEqual(expectedTokens[i].GetType());
		expect(tokens[i].GetValue())->toEqual(expectedTokens[i].GetValue());
	}
}

TEST_CASE("simple tokens") 
{
	TestTokenizing("2356",
		{
			Token(TokenType::NUMBER, "2356"),
		});
	TestTokenizing("+",
		{
			Token(TokenType::ADDITION),
		});
	TestTokenizing("-",
		{
			Token(TokenType::SUBTRACTION),
		});
	TestTokenizing("*",
		{
			Token(TokenType::MULTIPLICATION),
		});
	TestTokenizing("/",
		{
			Token(TokenType::DIVISION),
		});
}

TEST_CASE("simple expressions")
{
	TestTokenizing("2 + 2",
		{
			Token(TokenType::NUMBER, "2"),
			Token(TokenType::ADDITION),
			Token(TokenType::NUMBER, "2"),
		});

	TestTokenizing("2 - 2",
		{
			Token(TokenType::NUMBER, "2"),
			Token(TokenType::SUBTRACTION),
			Token(TokenType::NUMBER, "2"),
		});

	TestTokenizing("2 * 2",
		{
			Token(TokenType::NUMBER, "2"),
			Token(TokenType::MULTIPLICATION),
			Token(TokenType::NUMBER, "2"),
		});

	TestTokenizing("2 / 2",
		{
			Token(TokenType::NUMBER, "2"),
			Token(TokenType::DIVISION),
			Token(TokenType::NUMBER, "2"),
		});
}

TEST_CASE("long expression")
{
	TestTokenizing("284 + 1 / 3 * 92",
		{
			Token(TokenType::NUMBER, "284"),
			Token(TokenType::ADDITION),
			Token(TokenType::NUMBER, "1"),
			Token(TokenType::DIVISION),
			Token(TokenType::NUMBER, "3"),
			Token(TokenType::MULTIPLICATION),
			Token(TokenType::NUMBER, "92"),
		});
}