#pragma once
#include <vector>
#include <string>
#include <istream>
#include <algorithm>

#include "Rule.h"
#include "GetDirectionSymbols.h"
#include "StringHelpers.h"

void ReadRightPart(const std::string& rightPartStr, const std::string& nonTerminal, std::vector<Rule>& rules);

std::vector<std::string> GetRightPartWithoutNonterminal(const Rule& rule, const std::string& nonTerminal);

void AddAlternativeRulesWithoutEmptyRule(const std::vector<Rule>& rules, std::vector<Rule>& newRules, const std::string& nonTerminal, bool& hasChanges);

void FindAlternativeRulesWithoutEmptySymbol(std::vector<Rule>& rules);

std::vector<Rule> ReadGrammar(std::istream& inputFile);