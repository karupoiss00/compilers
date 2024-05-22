#pragma once
#include <string>
#include <vector>
#include <optional>

#include "Symbol.h"

const std::string EMPTY_SYMBOL = "e";
const std::string END_SYMBOL = "#";

struct Rule
{
    std::string nonTerminal;
    std::vector<std::string> rightPart;
    std::vector<Symbol> directionSymbols;

    bool operator==(const Rule& other) const
    {
        return this->nonTerminal == other.nonTerminal
            && this->rightPart == other.rightPart
            && this->directionSymbols == other.directionSymbols;
    }
};

bool IsNonTerminal(const std::string& str, const std::vector<Rule>& rules);
std::optional<size_t> GetIndexOfNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal);
std::vector<Rule> GetRulesWithNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal);
std::vector<Rule> GetNonterminalRules(const std::vector<Rule>& rules, const std::string& nonTerminal);