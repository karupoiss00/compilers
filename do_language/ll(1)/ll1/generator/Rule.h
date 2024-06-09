#pragma once
#include <string>
#include <vector>
#include <set>
#include <optional>

const std::string EMPTY_SYMBOL = "e";
const std::string END_SYMBOL = "#";

struct Rule
{
    std::string nonTerminal; /*Имя нетерминала*/
    std::vector<std::string> rightPart; /*Части правила*/
    std::set<std::string> directionSymbols; /*Направляющие символы*/
    bool hasEnd = false;

    bool operator==(const Rule& other)
    {
        return this->nonTerminal == other.nonTerminal
            && this->rightPart == other.rightPart
            && this->directionSymbols == other.directionSymbols
            && this->hasEnd == hasEnd;
    }
};

bool IsNonTerminal(const std::string& str, const std::vector<Rule>& rules);
std::optional<size_t> GetIndexOfNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal);
std::vector<Rule> GetRulesWithNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal);
std::vector<Rule> GetRulesOfNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal);