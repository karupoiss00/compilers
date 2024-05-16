#include "GetDirectionSymbols.h"

std::set<std::string> DefineNonTerminalDirectionSymbols(const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::set<std::string> directionSymbols;
    for (const Rule& rule : rules)
    {
        if (rule.nonTerminal == nonTerminalName)
        {
            directionSymbols.insert(rule.directionSymbols.begin(), rule.directionSymbols.end());
        }
    }

    return directionSymbols;
}

std::set<std::string> GetDirectionSymbolsAfterNonTerminal(const Rule& rule, const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::set<std::string> directionSymbols;
    auto it = std::find(rule.rightPart.begin(), rule.rightPart.end(), nonTerminalName);
    while (it != rule.rightPart.end())
    {
        it++;
        if (it == rule.rightPart.end())
        {
            std::vector<Rule> currentRules = GetRulesWithNonterminal(rules, rule.nonTerminal);
            for (const Rule& r : currentRules)
            {
                if (std::find(rule.rightPart.begin(), rule.rightPart.end(), r.nonTerminal) == rule.rightPart.end())
                {
                    std::set<std::string> symbols = GetDirectionSymbolsAfterNonTerminal(r, rule.nonTerminal, rules);
                    directionSymbols.insert(symbols.begin(), symbols.end());
                }
            }
            return directionSymbols;
        }
        if (IsNonTerminal(*it, rules))
        {
            std::set<std::string> symbols = DefineNonTerminalDirectionSymbols(rule.nonTerminal, rules);
            directionSymbols.insert(symbols.begin(), symbols.end());
        }
        else
        {
            directionSymbols.insert(*it);
        }
        it = std::find(it, rule.rightPart.end(), nonTerminalName);
    }
    return directionSymbols;
}

//Вызывается в случае, если нетерминал возвращает пустой символ и нужно узнать последующие направляющие символы
std::set<std::string> DefineDirectionSymbolsAfterNonTerminal(const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::set<std::string> directionSymbols;
    for (const Rule& rule : rules)
    {
        std::set<std::string> symbols = GetDirectionSymbolsAfterNonTerminal(rule, nonTerminalName, rules);
        directionSymbols.insert(symbols.begin(), symbols.end());
    }

    return directionSymbols;
}

void DefineDirectionSymbols(std::vector<Rule>& rules)
{
    bool hasChanges = false;
    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule& rule = rules[i];
        if (rule.rightPart.size() == 0)
        {
            throw std::logic_error("right part is empty");
        }
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == EMPTY_SYMBOL)
        {
            std::set<std::string> directionSymbols = DefineDirectionSymbolsAfterNonTerminal(rule.nonTerminal, rules);
            size_t sizeBefore = rule.directionSymbols.size();
            rule.directionSymbols.insert(directionSymbols.begin(), directionSymbols.end());
            hasChanges = sizeBefore == rule.directionSymbols.size() ? false : true;
            continue;
        }
        if (IsNonTerminal(rule.rightPart[0], rules))
        {
            std::set<std::string> directionSymbols = DefineNonTerminalDirectionSymbols(rule.rightPart[0], rules);
            size_t sizeBefore = rule.directionSymbols.size();
            rule.directionSymbols.insert(directionSymbols.begin(), directionSymbols.end());
            hasChanges = sizeBefore == rule.directionSymbols.size() ? false : true;
        }
        else
        {
            size_t sizeBefore = rule.directionSymbols.size();
            rules[i].directionSymbols.insert(rule.rightPart[0]);
            hasChanges = sizeBefore == rule.directionSymbols.size() ? false : true;
        }
    }

    if (hasChanges)
    {
        DefineDirectionSymbols(rules);
    }
}

std::vector<Rule> GetRulesWithNonterminal(const std::vector<Rule>& rules, const std::string& nonTerminal)
{
    std::vector<Rule> neededRules;

    for (const Rule& rule : rules)
    {
        if (std::find(rule.rightPart.begin(), rule.rightPart.end(), nonTerminal) != rule.rightPart.end())
        {
            neededRules.push_back(Rule(rule));
        }
    }

    return neededRules;
}