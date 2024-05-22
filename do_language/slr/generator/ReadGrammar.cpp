#include "ReadGrammar.h"

void ReadRightPart(const std::string& rightPartStr, const std::string& nonTerminal, std::vector<Rule>& rules)
{
    std::vector<std::string> rightPart = Split(rightPartStr, "|");
    std::transform(rightPart.begin(), rightPart.end(), rightPart.begin(), RemoveSpacesInBeginAndEndOfWord);
    for (const std::string ruleStr : rightPart)
    {
        Rule rule;
        rule.nonTerminal = nonTerminal;
        std::vector<std::string> partOfRule = Split(ruleStr, " ");
        rule.rightPart = partOfRule;
        rules.push_back(rule);
    }
}

std::vector<std::string> GetRightPartWithoutNonterminal(const Rule& rule, const std::string& nonTerminal)
{
    std::vector<std::string> newRightPart;

    for (std::string symbol : rule.rightPart)
    {
        if (symbol != nonTerminal)
        {
            newRightPart.push_back(symbol);
        }
    }

    return newRightPart;
}

void AddAlternativeRulesWithoutEmptyRule(const std::vector<Rule>& rules, std::vector<Rule>& newRules, const std::string& nonTerminal)
{
    const std::vector<Rule> rulesWithEmptyRule = GetRulesWithNonterminal(rules, nonTerminal);

    for (const Rule& r : rulesWithEmptyRule)
    {
        if (r.rightPart.size() == 1)
        {
            AddAlternativeRulesWithoutEmptyRule(rules, newRules, r.nonTerminal);
            continue;
        }
        Rule newRule;
        newRule.nonTerminal = r.nonTerminal;
        newRule.rightPart = GetRightPartWithoutNonterminal(r, nonTerminal);
        if (std::find(rules.begin(), rules.end(), newRule) == rules.end()
            && std::find(newRules.begin(), newRules.end(), newRule) == newRules.end())
        {
            newRules.push_back(newRule);
        }
    }
}

void RemoveRulesWithEmptySymbol(std::vector<Rule>& rules)
{
    std::vector<Rule> newRules;

    for (const Rule& rule : rules)
    {
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == EMPTY_SYMBOL)
        {
            AddAlternativeRulesWithoutEmptyRule(rules, newRules, rule.nonTerminal);
            continue;
        }
        newRules.push_back(rule);
    }

    rules = newRules;
}

std::vector<Rule> ReadGrammar(std::istream& inputFile)
{
    std::vector<Rule> rules;
    std::string ruleStr;
    while (getline(inputFile, ruleStr))
    {
        std::vector<std::string> rule = Split(ruleStr, "->");
        std::string nonTerminal = RemoveSpacesInBeginAndEndOfWord(rule[0]);
        ReadRightPart(rule[1], nonTerminal, rules);
    }

    RemoveRulesWithEmptySymbol(rules);
    DefineDirectionSymbols(rules);

    return rules;
}