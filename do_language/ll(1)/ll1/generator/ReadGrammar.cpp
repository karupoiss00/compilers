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

//Получение частей правила для нетерминала
void ReadRightPart(const std::string& rightPartStr, const std::string& nonTerminal, std::vector<Rule>& rules)
{
    // Разбиваем строку с правилами
    std::vector<std::string> rightPart = Split(rightPartStr, "|");
    std::transform(rightPart.begin(), rightPart.end(), rightPart.begin(), RemoveSpacesInBeginAndEndOfWord);
    // Проходимся по правилам
    for (const std::string ruleStr : rightPart)
    {
        //Создаем объект, хранящий название нетерминала и элементы правила
        Rule rule;
        rule.nonTerminal = nonTerminal;
        std::vector<std::string> partOfRule = Split(ruleStr, " ");
        rule.rightPart = partOfRule;
        if (rules.empty())
        {
            rule.hasEnd = true;
        }
        //Добавляем правило в грамматику
        rules.push_back(rule);
    }
}

// Преобразование правила с левосторонней грамматикой
void UpdateRuleWithLeftRecursion(Rule& rule, std::vector<Rule>& rules, std::vector<Rule>& newRules)
{
    //Пример:
    // До
    // <S> -> <S> + <X> | <X>
    // 
    // После
    // <S> -> <X> <S1>
    // <S1> -> + <X> <S1> | e
    //Получаем все правила из грамматики для нетерминала
    std::vector<Rule> rulesWithNonterminal = GetRulesOfNonterminal(rules, rule.nonTerminal);

    //Проверяем, что количество правил для нетерминала больше одного
    //Если у нетерминала одно правило с левосторонней рекурсией, то это правило зацикливается
    if (rulesWithNonterminal.size() < 2)
    {
        throw std::logic_error("Left recursion rule is looped");
    }

    //Получаем имя для нового нетерминала, который будет использоваться для избавления от левосторонней рекурсией
    std::string nameOfNewRule = GetNameOfNonterminalWithIndex(rules, rule.nonTerminal);

    // Создаем новое правило
    Rule newRule;
    newRule.nonTerminal = nameOfNewRule;
    newRule.hasEnd = rule.hasEnd;
    //Передаем в это правило все части правила с левосторноонней рекурсией, кроме самого первого элемента правила
    //И добавляем новый нетерминал в конец правила
    for (size_t i = 1; i < rule.rightPart.size(); i++)
    {
        newRule.rightPart.push_back(rule.rightPart[i]);
    }
    newRule.rightPart.push_back(nameOfNewRule);

    //Создаем альтернативное пустое правило для нового нетерминала
    Rule newEmptyRule;
    newEmptyRule.nonTerminal = nameOfNewRule;
    newEmptyRule.rightPart.push_back(EMPTY_SYMBOL);

    //Проходимся по всем альтернативным правилам этого нетерминала и добавляем им в конец новый нетерминал
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
    //Добавляем новые правила в грамматику
    newRules.push_back(newRule);
    newRules.push_back(newEmptyRule);
}

// Избавление от левосторонней рекурсии в грамматике
void RemoveLeftRecursion(std::vector<Rule>& rules)
{
    std::vector<Rule> newRules;
    bool hasChanges = false;

    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule& rule = rules[i];
        //Проверяем, что части правила есть
        if (rule.rightPart.size() == 0)
        {
            throw std::logic_error("Rule has not right part");
        }
        //Проверка на то, что нетерминал не возвращает самого себя
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == rule.nonTerminal)
        {
            throw std::logic_error("ERROR: <Nonterminal> -> <Nonterminal>");
        }
        //Проверка на левостороннюю рекурсию
        if (rule.nonTerminal != rule.rightPart[0])
        {
            // Если левосторонней грамматики нет, то неизмененное правило добавляют в обновленную грамматику
            newRules.push_back(rule);
            continue;
        }
        // Если левосторонняя грамматика есть
        // Отмечаем, что есть изменения
        hasChanges = true;
        // Преобразуем правило с левосторонней грамматикой
        UpdateRuleWithLeftRecursion(rule, rules, newRules);
        continue;
    }

    rules = newRules;
    
    //Если есть изменения в грамматике, выполняется повторная проверка на левостороннюю грамматику
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

//Нахождение общего префикса и правил, у которых он есть
std::pair<std::vector<std::string>, std::vector<Rule>> DefineSamePrefixAndRules(
    size_t index,
    const std::vector<std::string>& prefix,
    const std::vector<Rule>& rulesWithPrefix)
{
    //Проверка на то, что есть префикс общий и проверяется не первый символ
    if (prefix.empty() && index > 0)
    {
        return std::make_pair(prefix, rulesWithPrefix);
    }

    //Проверка того, что список правил с общим префиксом не пуст
    if (rulesWithPrefix.empty())
    {
        return std::make_pair(prefix, rulesWithPrefix);
    }

    std::map<std::string, std::vector<Rule>> symbols;
    bool hasEnd = false;
    std::string symbolOfIndex;

    //Обход правил с общим префиксом
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

    //Если символ находящийся под этим индексом в правиле не у всех одинаков или индекс выходит за размеры правила,
    //то префикс не дополняется
    if (hasEnd || symbols.size() != 1)
    {
        return { prefix, rulesWithPrefix };
    }

    //Если у всех элемент по этому индексу одинков, то префикс дополняется
    std::vector<std::string> updatedPrefix = prefix;
    updatedPrefix.push_back(symbolOfIndex);
    //Происходит проверка элементов правил по следующему индексу
    return DefineSamePrefixAndRules(index + 1, updatedPrefix, symbols[symbolOfIndex]);
}

//Добавляются обновленные правила без общего префикса для нового нетерминала
void AddNewRulesAfterPrefix(
    std::vector<Rule>& rulesWithPrefix,
    const std::string& newNonTerminal,
    const size_t beginIndex,
    std::vector<Rule>& rules)
{
    // Обход правил с общим префиксом
    for (Rule& r : rulesWithPrefix)
    {
        //Создается правило для нового нетерминала
        Rule updatedRule;
        updatedRule.nonTerminal = newNonTerminal;
        updatedRule.hasEnd = r.hasEnd;
        //Если после общего префикса в правиле больше ничего нет, то новое правило - пустое
        if (beginIndex == r.rightPart.size())
        {
            updatedRule.rightPart.push_back(EMPTY_SYMBOL);
        }
        //Добавление в новое правило часть правила, находящаяся после общего префикса
        for (size_t i = beginIndex; i < r.rightPart.size(); i++)
        {
            updatedRule.rightPart.push_back(r.rightPart[i]);
        }
        //Проверка того, что такого правила нет
        if (std::find(rules.begin(), rules.end(), updatedRule) == rules.end())
        {
            rules.push_back(updatedRule);
        }
    }
}

void Factorization(std::vector<Rule>& rules, const std::string& nonTerminalName, bool& hasChanges, std::vector<Rule>& newRules)
{
    //Получаем все правила для нетерминала
    std::vector<Rule> neededRules = GetRulesOfNonterminal(rules, nonTerminalName);
    std::map<std::string, std::vector<Rule>> symbols;

    for (Rule& r : neededRules)
    {
        symbols[{r.rightPart[0]}].push_back(r);
    }

    //Если все правила начинаются с разных символов, правила не преобразуются
    if (symbols.size() == neededRules.size())
    {
        newRules.insert(newRules.end(), neededRules.begin(), neededRules.end());
        return;
    }

    std::map<std::vector<std::string>, std::vector<Rule>> prefixesWithRules;
    
    hasChanges = true;
    for (auto s : symbols)
    {
        //Проверка того, что правил начинающихся на один и тот же символ > 1
        if (s.second.size() == 1)
        {
            newRules.push_back(s.second[0]);
            continue;
        }
        std::vector<std::string> prefix = { s.first };
        //Получение общего префикса и правил, у которого он есть
        std::pair<std::vector<std::string>, std::vector<Rule>> rulesWithPrefix = DefineSamePrefixAndRules(1, prefix, s.second);
        prefixesWithRules[rulesWithPrefix.first] = rulesWithPrefix.second;
    }

    //Обход правил с одинаковым префиксом
    for (std::pair<std::vector<std::string>, std::vector<Rule>> prefixWithRules : prefixesWithRules)
    {
        std::vector<std::string> prefix = prefixWithRules.first;
        std::vector<Rule> rulesWithPrefix = prefixWithRules.second;

        //Получение названия для нового нетерминала
        std::string newNonTerminal = GetNameForNewRuleWithoutSamePrefix(nonTerminalName, rules, newRules);
        prefix.push_back(newNonTerminal);

        //В новую грамматику добавляется правило для нетерминала с общим префиксом и новым нетерминалом в конце
        Rule newRule;
        newRule.nonTerminal = nonTerminalName;
        newRule.rightPart = prefix;
        newRules.push_back(newRule);
        //Добавляются обновленные правила для нового нетерминала
        AddNewRulesAfterPrefix(rulesWithPrefix, newNonTerminal, prefix.size() - 1, newRules);
    }
}

void UpdateRulesWithSamePrefix(std::vector<Rule>& rules)
{
    std::vector<Rule> newRules;
    std::set<std::string> checkedRules;

    bool hasChanges = false;

    //Перебор правил
    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule& rule = rules[i];
        if (checkedRules.find(rule.nonTerminal) != checkedRules.end())
        {
            continue;
        }
        //Нетерминал отмечается проверенным
        checkedRules.insert(rule.nonTerminal);
        //Преобразование правил с одинаковым префиксом для нетерминала 
        Factorization(rules, rule.nonTerminal, hasChanges, newRules);
    }

    rules = newRules;

    //Если есть изменения в грамматике, выполняется повторная проверка на правила с одинаковым префиксом
    //для одного и того же правила
    if (hasChanges)
    {
        UpdateRulesWithSamePrefix(rules);
    }
}

//Считывание грамматики 
std::vector<Rule> ReadGrammar(std::istream& inputFile)
{
    std::vector<Rule> rules;
    std::string ruleStr;
    while (getline(inputFile, ruleStr))
    {
        //Разбивание строки на нетерминал и правило для него
        std::vector<std::string> rule = Split(ruleStr, "->");
        std::string nonTerminal = RemoveSpacesInBeginAndEndOfWord(rule[0]);
        //Разбивание правила на отдельные части
        ReadRightPart(rule[1], nonTerminal, rules);
    }
    //Избавление от левосторонней рекурсии в грамматике
    RemoveLeftRecursion(rules);
    //Преобразование правил с одинаковым префиксом для одного и того же нетерминала 
    UpdateRulesWithSamePrefix(rules);
    //Определяем направляющие символы для каждого правила
    DefineDirectionSymbols(rules);

    return rules;
}