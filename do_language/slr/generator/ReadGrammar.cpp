#include "ReadGrammar.h"

//Получение правила для нетерминала из строки
void ReadRightPart(const std::string& rightPartStr, const std::string& nonTerminal, std::vector<Rule>& rules)
{
    //Разбитие строки на правила
    std::vector<std::string> rightPart = Split(rightPartStr, "|");
    std::transform(rightPart.begin(), rightPart.end(), rightPart.begin(), RemoveSpacesInBeginAndEndOfWord);
    //Добавление всех альтернативных правил для нетерминала в грамматику
    for (const std::string ruleStr : rightPart)
    {
        Rule rule;
        rule.nonTerminal = nonTerminal;
        std::vector<std::string> partOfRule = Split(ruleStr, " ");
        rule.rightPart = partOfRule;
        rules.push_back(rule);
    }
}

//Получение правила без заданного нетерминала
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

//Изменение правил, в которых используется нетерминал с пустым правилом
void AddAlternativeRulesWithoutEmptyRule(const std::vector<Rule>& rules, std::vector<Rule>& newRules, const std::string& nonTerminal, bool& hasChanges)
{
    //Получение правил, в которых используется нетерминал с пустым правилом
    const std::vector<Rule> rulesWithEmptyRule = GetRulesWithNonterminal(rules, nonTerminal);

    //Обход правил, в которых используется нетерминал с пуствм правилом
    for (const Rule& r : rulesWithEmptyRule)
    {
        // Если правило состоит только из одного элемента,
        //то изменяются правила, где используется нетерминал, которому принадлежит данное правило 
        if (r.rightPart.size() == 1)
        {
            AddAlternativeRulesWithoutEmptyRule(rules, newRules, r.nonTerminal, hasChanges);
            continue;
        }
        //Создается копия правила без нетерминала с путым правилом
        Rule newRule;
        newRule.nonTerminal = r.nonTerminal;
        newRule.rightPart = GetRightPartWithoutNonterminal(r, nonTerminal);
        //Проверка на наличие правила в грамматике
        if (std::find(rules.begin(), rules.end(), newRule) == rules.end()
            && std::find(newRules.begin(), newRules.end(), newRule) == newRules.end())
        {
            hasChanges = true;
            newRules.push_back(newRule);
        }
    }
}

//Избавление от пустых правил
void RemoveRulesWithEmptySymbol(std::vector<Rule>& rules)
{
    std::vector<Rule> newRules;

    for (const Rule& rule : rules)
    {
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == EMPTY_SYMBOL)
        {
            continue;
        }
        newRules.push_back(rule);
    }

    rules = newRules;
}

//Добавление правил, которые заместят пустые правила
void FindAlternativeRulesWithoutEmptySymbol(std::vector<Rule>& rules)
{
    std::vector<Rule> newRules;
    bool hasChanges = false;

    //Обход грамматики
    for (const Rule& rule : rules)
    {
        //Если правило пустое, то создаются альтернаятивные правила, замещающие его
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == EMPTY_SYMBOL)
        {
            newRules.push_back(rule);
            AddAlternativeRulesWithoutEmptyRule(rules, newRules, rule.nonTerminal, hasChanges);
            continue;
        }
        newRules.push_back(rule);
    }

    rules = newRules;

    //Еслы были произведены изменения в грамматике,
    //то делаем повторную проверку на добавление альтернативных правил
    if (hasChanges)
    {
        FindAlternativeRulesWithoutEmptySymbol(rules);
    }
}

//Считывание грамматики
std::vector<Rule> ReadGrammar(std::istream& inputFile)
{
    std::vector<Rule> rules;
    std::string ruleStr;
    while (getline(inputFile, ruleStr))
    {
        //Получение нетерминала и правил для этого нетерминала
        std::vector<std::string> rule = Split(ruleStr, "->");
        std::string nonTerminal = RemoveSpacesInBeginAndEndOfWord(rule[0]);
        ReadRightPart(rule[1], nonTerminal, rules);
    }
    //Добавление правил, которые заместят пустые правила
    FindAlternativeRulesWithoutEmptySymbol(rules);
    //Избавление от пустых правил
    RemoveRulesWithEmptySymbol(rules);
    //Определение направиляющих символов для нетерминалов в грамматике
    DefineDirectionSymbols(rules);

    return rules;
}