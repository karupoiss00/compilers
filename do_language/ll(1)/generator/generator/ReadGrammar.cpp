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

    DefineDirectionSymbols(rules);

    return rules;
}