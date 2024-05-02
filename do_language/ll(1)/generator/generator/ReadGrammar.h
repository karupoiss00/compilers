#pragma once
#include <vector>
#include <string>
#include <istream>
#include <algorithm>

#include "Rule.h"
#include "GetDirectionSymbols.h"
#include "StringHelpers.h"

void ReadRightPart(const std::string& rightPartStr, const std::string& nonTerminal, std::vector<Rule>& rules);

std::vector<Rule> ReadGrammar(std::istream& inputFile);