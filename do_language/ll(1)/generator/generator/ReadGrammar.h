#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "Rule.h"
#include "GetDirectionSymbols.h"

std::vector<std::string> Split(const std::string& str, const std::string& separator)
{
    std::vector<std::string> strs;
    size_t startPos = 0;
    size_t endPos = str.find(separator);
    while (endPos != std::string::npos)
    {
        std::string partOfStr = str.substr(startPos, endPos - startPos);
        if (partOfStr.length() != 0)
        {
            strs.push_back(partOfStr);
        }
        startPos = endPos + separator.length();
        endPos = str.find(separator, startPos);
    }

    if (startPos != str.length())
    {
        std::string partOfStr = str.substr(startPos);
        strs.push_back(partOfStr);
    }

    return strs;
}

std::string RemoveSpacesInBeginAndEndOfWord(const std::string& str)
{
    std::string newStr = str;
    while (newStr[newStr.length() - 1] == ' ')
    {
        newStr = newStr.substr(0, newStr.length() - 1);
    }
    while (newStr[0] == ' ')
    {
        newStr = newStr.substr(1);
    }

    return newStr;
}

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

std::vector<Rule> ReadGrammar(std::ifstream& inputFile)
{
    std::vector<Rule> rules;
    std::string ruleStr;
    while (getline(inputFile, ruleStr))
    {
        std::vector<std::string> partOfRuleStr = Split(ruleStr, "->");
        std::string nonTerminal = RemoveSpacesInBeginAndEndOfWord(partOfRuleStr[0]);
        ReadRightPart(partOfRuleStr[1], nonTerminal, rules);
    }

    DefineDirectionSymbols(rules);

    return rules;
}