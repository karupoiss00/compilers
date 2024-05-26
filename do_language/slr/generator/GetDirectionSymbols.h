#pragma once
#include <stdexcept>
#include <set>

#include "Rule.h"

bool AddNewSymbols(std::vector<Symbol>& currentDirectionSymbols, const std::vector<Symbol>& newDirectionSymbols);

std::vector<Symbol> DefineNonTerminalDirectionSymbols(const std::string& nonTerminalName, const std::vector<Rule>& rules);

std::vector<Symbol> GetDirectionSymbolsAfterNonTerminal(const Rule& rule, size_t numOfRule, const std::string& nonTerminalName, const std::vector<Rule>& rules, std::set<size_t> checkedRulesIndexes);

std::vector<Symbol> DefineDirectionSymbolsAfterNonTerminal(std::set<size_t> checkedRulesIndexes, const std::string& nonTerminalName, const std::vector<Rule>& rules);

//std::vector<Symbol> GetDirectionSymbolsIfNonterminalInEnd(const Rule& rule, const std::vector<Rule>& rules);

void DefineDirectionSymbols(std::vector<Rule>& rules);