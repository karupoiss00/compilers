#pragma once
#include <string>
#include <vector>
#include <set>
#include <optional>

const std::string EMPTY_SYMBOL = "e";
const std::string END_SYMBOL = "#";

struct Rule
{
    std::string nonTerminal;
    std::vector<std::string> rightPart;
    std::set<std::string> directionSymbols;
};

bool IsNonTerminal(const std::string& str, const std::vector<Rule>& rules);
std::optional<size_t> GetIndexOfNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal);