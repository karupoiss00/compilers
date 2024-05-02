#pragma once
#include <stdexcept>
#include "Rule.h"

std::set<std::string> DefineNonTerminalDirectionSymbols(const std::string& nonTerminalName, const std::vector<Rule>& rules);

std::set<std::string> GetDirectionSymbolsAfterNonTerminal(const Rule& rule, const std::string& nonTerminalName, const std::vector<Rule>& rules);

std::set<std::string> DefineDirectionSymbolsAfterNonTerminal(const std::string& nonTerminalName, const std::vector<Rule>& rules);

void DefineDirectionSymbols(std::vector<Rule>& rules);