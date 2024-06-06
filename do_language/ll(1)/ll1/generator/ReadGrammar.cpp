#include "ReadGrammar.h"

std::string GetNameOfNonterminalWithIndex(const std::vector<Rule>& rules, const std::string& nonTerminalName)
{
    int index = 1;
    std::string updatedName = nonTerminalName;
    while (!GetRulesOfNonterminal(rules, updatedName + std::to_string(index)).empty())
    {
        index++;
    }
    return updatedName + std::to_string(index);
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
        if (rules.empty())
        {
            rule.hasEnd = true;
        }
        rules.push_back(rule);
    }
}

void UpdateRuleWithLeftRecursion(Rule& rule, std::vector<Rule>& rules, std::vector<Rule>& newRules)
{
    std::vector<Rule> rulesWithNonterminal = GetRulesOfNonterminal(rules, rule.nonTerminal);
    if (rulesWithNonterminal.size() < 2)
    {
        throw std::logic_error("Left recursion rule is looped");
    }

    std::string nameOfNewRule = GetNameOfNonterminalWithIndex(rules, rule.nonTerminal);

    Rule newRule;
    newRule.nonTerminal = nameOfNewRule;
    newRule.hasEnd = rule.hasEnd;
    for (size_t i = 1; i < rule.rightPart.size(); i++)
    {
        newRule.rightPart.push_back(rule.rightPart[i]);
    }
    newRule.rightPart.push_back(nameOfNewRule);

    Rule newEmptyRule;
    newEmptyRule.nonTerminal = nameOfNewRule;
    newEmptyRule.rightPart.push_back(EMPTY_SYMBOL);

    for (const Rule& r : rulesWithNonterminal)
    {
        if (r == rule)
        {
            continue;
        }
        Rule updatedRule = r;
        updatedRule.rightPart.push_back(nameOfNewRule);
        newRules.push_back(updatedRule);
        auto pos = std::find(rules.begin(), rules.end(), r);
        if (pos != rules.end())
        {
            rules.erase(pos);
        }
    }
    newRules.push_back(newRule);
    newRules.push_back(newEmptyRule);
}

void RemoveLeftRecursion(std::vector<Rule>& rules)
{
    std::vector<Rule> newRules;
    bool hasChanges = false;

    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule& rule = rules[i];
        if (rule.rightPart.size() == 0)
        {
            throw std::logic_error("Rule has not right part");
        }
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == rule.nonTerminal)
        {
            throw std::logic_error("ERROR: <Nonterminal> -> <Nonterminal>");
        }
        if (rule.nonTerminal != rule.rightPart[0])
        {
            newRules.push_back(rule);
            continue;
        }
        hasChanges = true;
        UpdateRuleWithLeftRecursion(rule, rules, newRules);
        continue;
    }

    rules = newRules;

    if (hasChanges)
    {
        RemoveLeftRecursion(rules);
    }
}

std::string GetNameForNewRuleWithoutSamePrefix(const std::string& nonTerminalName, const std::vector<Rule>& rules, const std::vector<Rule>& newRules)
{
    std::string name1 = GetNameOfNonterminalWithIndex(rules, nonTerminalName);
    std::string name2 = GetNameOfNonterminalWithIndex(newRules, nonTerminalName);

    if (name1 == name2)
    {
        return name1;
    }

    if (name1.length() == name2.length())
    {
        return name1 > name2 ? name1 : name2;
    }

    return name1.length() > name2.length() ? name1 : name2;
}

std::pair<std::vector<std::string>, std::vector<Rule>> DefineSamePrefixAndRules(
    size_t index,
    const std::vector<std::string>& prefix,
    const std::vector<Rule>& rulesWithPrefix)
{
    if (prefix.empty() && index > 0)
    {
        return std::make_pair(prefix, rulesWithPrefix);
    }
    if (rulesWithPrefix.empty())
    {
        return std::make_pair(prefix, rulesWithPrefix);
    }

    std::map<std::string, std::vector<Rule>> symbols;
    bool hasEnd = false;
    std::string symbolOfIndex;

    for (const Rule& r : rulesWithPrefix)
    {
        if (index >= r.rightPart.size())
        {
            hasEnd = true;
            continue;
        }
        symbolOfIndex = r.rightPart[index];
        symbols[r.rightPart[index]].push_back(r);
    }

    if (hasEnd || symbols.size() != 1)
    {
        return { prefix, rulesWithPrefix };
    }

    std::vector<std::string> updatedPrefix = prefix;
    updatedPrefix.push_back(symbolOfIndex);
    return DefineSamePrefixAndRules(index + 1, updatedPrefix, symbols[symbolOfIndex]);
}

void AddNewRulesAfterPrefix(
    std::vector<Rule>& rulesWithPrefix,
    const std::string& newNonTerminal,
    const size_t beginIndex,
    std::vector<Rule>& rules)
{
    for (Rule& r : rulesWithPrefix)
    {
        Rule updatedRule;
        updatedRule.nonTerminal = newNonTerminal;
        updatedRule.hasEnd = r.hasEnd;
        if (beginIndex == r.rightPart.size())
        {
            updatedRule.rightPart.push_back(EMPTY_SYMBOL);
        }
        for (size_t i = beginIndex; i < r.rightPart.size(); i++)
        {
            updatedRule.rightPart.push_back(r.rightPart[i]);
        }
        if (std::find(rules.begin(), rules.end(), updatedRule) == rules.end())
        {
            rules.push_back(updatedRule);
        }
    }
}

void Factorization(std::vector<Rule>& rules, const std::string& nonTerminalName, bool& hasChanges, std::vector<Rule>& newRules)
{ 
    std::vector<Rule> neededRules = GetRulesOfNonterminal(rules, nonTerminalName);
    std::map<std::string, std::vector<Rule>> symbols;

    for (Rule& r : neededRules)
    {
        symbols[{r.rightPart[0]}].push_back(r);
    }

    if (symbols.size() == neededRules.size())
    {
        newRules.insert(newRules.end(), neededRules.begin(), neededRules.end());
        return;
    }

    std::map<std::vector<std::string>, std::vector<Rule>> prefixesWithRules;
    
    hasChanges = true;
    for (auto s : symbols)
    {
        if (s.second.size() == 1)
        {
            newRules.push_back(s.second[0]);
            continue;
        }
        std::vector<std::string> prefix = { s.first };
        std::pair<std::vector<std::string>, std::vector<Rule>> rulesWithPrefix = DefineSamePrefixAndRules(1, prefix, s.second);
        prefixesWithRules[rulesWithPrefix.first] = rulesWithPrefix.second;
    }

    for (std::pair<std::vector<std::string>, std::vector<Rule>> prefixWithRules : prefixesWithRules)
    {
        std::vector<std::string> prefix = prefixWithRules.first;
        std::vector<Rule> rulesWithPrefix = prefixWithRules.second;

        std::string newNonTerminal = GetNameForNewRuleWithoutSamePrefix(nonTerminalName, rules, newRules);
        prefix.push_back(newNonTerminal);

        Rule newRule;
        newRule.nonTerminal = nonTerminalName;
        newRule.rightPart = prefix;
        newRules.push_back(newRule);
        AddNewRulesAfterPrefix(rulesWithPrefix, newNonTerminal, prefix.size() - 1, newRules);
    }
}

void UpdateRulesWithSamePrefix(std::vector<Rule>& rules)
{
    std::vector<Rule> newRules;
    std::set<std::string> checkedRules;

    bool hasChanges = false;

    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule& rule = rules[i];
        if (checkedRules.find(rule.nonTerminal) != checkedRules.end())
        {
            continue;
        }
        checkedRules.insert(rule.nonTerminal);
        Factorization(rules, rule.nonTerminal, hasChanges, newRules);
    }

    rules = newRules;

    if (hasChanges)
    {
        UpdateRulesWithSamePrefix(rules);
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
    RemoveLeftRecursion(rules);
    UpdateRulesWithSamePrefix(rules);
    DefineDirectionSymbols(rules);

    return rules;
}