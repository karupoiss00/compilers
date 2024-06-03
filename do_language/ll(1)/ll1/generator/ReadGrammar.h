#pragma once
#include <vector>
#include <string>
#include <istream>
#include <algorithm>
#include <map>

#include "Rule.h"
#include "GetDirectionSymbols.h"
#include "StringHelpers.h"

std::string GetNameOfNonterminalWithIndex(const std::vector<Rule>& rules, const std::string& nonTerminalName);

void ReadRightPart(const std::string& rightPartStr, const std::string& nonTerminal, std::vector<Rule>& rules);

void UpdateRuleWithLeftRecursion(Rule& rule, std::vector<Rule>& rules, std::vector<Rule>& newRules);

void RemoveLeftRecursion(std::vector<Rule>& rules);

std::string GetNameForNewRuleWithoutSamePrefix(const std::string& nonTerminalName, const std::vector<Rule>& rules, const std::vector<Rule>& newRules);

std::pair<std::vector<std::string>, std::vector<Rule>> DefineSamePrefixAndRules(
    size_t index,
    const std::vector<std::string>& prefix,
    const std::vector<Rule>& rulesWithPrefix);

void AddNewRulesAfterPrefix(
    std::vector<Rule>& rulesWithPrefix,
    const std::string& newNonTerminal,
    const size_t beginIndex,
    std::vector<Rule>& rules);

void Factorization(std::vector<Rule>& rules, const std::string& nonTerminalName, bool& hasChanges, std::vector<Rule>& newRules);

void UpdateRulesWithSamePrefix(std::vector<Rule>& rules);

std::vector<Rule> ReadGrammar(std::istream& inputFile);