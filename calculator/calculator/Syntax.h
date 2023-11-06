#pragma once
#include <map>
#include "TokenType.h"

namespace Syntax
{
	bool isOperator(char ch);
	TokenType GetOperatorToken(char ch);
}