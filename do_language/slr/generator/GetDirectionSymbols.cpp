#include "GetDirectionSymbols.h"

bool AddNewSymbols(std::vector<Symbol>& currentDirectionSymbols, const std::vector<Symbol>& newDirectionSymbols)
{
    bool hasChange = false;

    for (const Symbol& dirSymbol : newDirectionSymbols)
    {
        if (std::find(currentDirectionSymbols.begin(), currentDirectionSymbols.end(), dirSymbol) == currentDirectionSymbols.end())
        {
            currentDirectionSymbols.insert(currentDirectionSymbols.end(), dirSymbol);
            hasChange = true;
        }
    }

    return hasChange;
}

std::vector<Symbol> DefineNonTerminalDirectionSymbols(const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::vector<Symbol> directionSymbols;
    for (const Rule& rule : rules)
    {
        if (rule.nonTerminal == nonTerminalName)
        {
            directionSymbols.insert(directionSymbols.end(), rule.directionSymbols.begin(), rule.directionSymbols.end());
        }
    }

    return directionSymbols;
}

std::vector<Symbol> GetDirectionSymbolsAfterNonTerminal(const Rule& rule, size_t numOfRule, const std::string& nonTerminalName, const std::vector<Rule>& rules, std::set<size_t> checkedRulesIndexes)
{
    std::vector<Symbol> directionSymbols;
    auto it = std::find(rule.rightPart.begin(), rule.rightPart.end(), nonTerminalName);
    while (it != rule.rightPart.end())
    {
        it++;
        if (it == rule.rightPart.end())
        {
            std::vector<Symbol> symbols = DefineDirectionSymbolsAfterNonTerminal(checkedRulesIndexes, rule.nonTerminal, rules);
            directionSymbols.insert(directionSymbols.end(), symbols.begin(), symbols.end());
            continue;
        }
        if (IsNonTerminal(*it, rules))     {
            std::vector<Symbol> symbols = DefineNonTerminalDirectionSymbols(*it, rules);
            directionSymbols.insert(directionSymbols.end(), symbols.begin(), symbols.end());
        }
        Symbol symbol;
        symbol.name = *it;
        symbol.numOfRule = numOfRule;
        symbol.numOfRightPart = it - rule.rightPart.begin();
        directionSymbols.insert(directionSymbols.end(), symbol);
        it = std::find(it, rule.rightPart.end(), nonTerminalName);
    }
    return directionSymbols;
}

//Вызывается в случае, если нетерминал возвращает пустой символ и нужно узнать последующие направляющие символы
std::vector<Symbol> DefineDirectionSymbolsAfterNonTerminal(std::set<size_t> checkedRulesIndexes, const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::vector<Symbol> directionSymbols;
    for (size_t i = 0; i < rules.size(); i++)
    {
        if (checkedRulesIndexes.find(i) != checkedRulesIndexes.end())
        {
            continue;
        }
        std::set<size_t> newCheckedRulesIndexes = checkedRulesIndexes;
        newCheckedRulesIndexes.insert(i);
        const Rule& rule = rules[i];
        std::vector<Symbol> symbols = GetDirectionSymbolsAfterNonTerminal(rule, i, nonTerminalName, rules, newCheckedRulesIndexes);
        directionSymbols.insert(directionSymbols.end(), symbols.begin(), symbols.end());
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
            std::vector<Symbol> directionSymbols = DefineDirectionSymbolsAfterNonTerminal({}, rule.nonTerminal, rules);
            hasChanges = hasChanges ? true : AddNewSymbols(rule.directionSymbols, directionSymbols);
            continue;
        }
        if (IsNonTerminal(rule.rightPart[0], rules))
        {
            std::vector<Symbol> directionSymbols = DefineNonTerminalDirectionSymbols(rule.rightPart[0], rules);
            hasChanges = hasChanges ? true : AddNewSymbols(rule.directionSymbols, directionSymbols);
        }
        size_t sizeBefore = rule.directionSymbols.size();
        Symbol symbol;
        symbol.name = rule.rightPart[0];
        symbol.numOfRule = i;
        symbol.numOfRightPart = 0;
        hasChanges = hasChanges ? true : AddNewSymbols(rule.directionSymbols, { symbol });
    }

    if (hasChanges)
    {
        DefineDirectionSymbols(rules);
    }
}