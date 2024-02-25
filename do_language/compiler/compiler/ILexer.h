#pragma once
#include <vector>
#include "Token.h"

class ILexer
{
public:
	virtual std::vector<Token> Tokenize() = 0;
};