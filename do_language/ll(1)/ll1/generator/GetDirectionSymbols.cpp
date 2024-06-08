#include "GetDirectionSymbols.h"

//Получение всех направляющих символов у нетерминала
std::set<std::string> DefineNonTerminalDirectionSymbols(const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::set<std::string> directionSymbols;
    //Проходится по всем правилам заданного нетерминала
    //и добавяляет его направляющие символы
    for (const Rule& rule : rules)
    {
        if (rule.nonTerminal == nonTerminalName)
        {
            directionSymbols.insert(rule.directionSymbols.begin(), rule.directionSymbols.end());
        }
    }

    return directionSymbols;
}

//Определение символов, которые используюся после заданного нетерминала в правиле
std::set<std::string> GetDirectionSymbolsAfterNonTerminal(const Rule& rule, const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::set<std::string> directionSymbols;
    //Определение позиции нетерминала в правиле
    auto it = std::find(rule.rightPart.begin(), rule.rightPart.end(), nonTerminalName);
    // Обход всех позиций заданного нетерминала в правиле
    while (it != rule.rightPart.end())
    {
        it++;
        //Если нетерминал вызывается в конце правила,
        //то определяются символы, вызывающиеся после нетерминала,
        //в правиле которого используется заданный нетерминал
        if (it == rule.rightPart.end())
        {
            std::set<std::string> symbols = GetDirectionSymbolsIfNonterminalInEnd(rule, rules);
            directionSymbols.insert(symbols.begin(), symbols.end());
            continue;
        }
        // Если следующий элемент - нетерминал,
        //то находим направляющие символы этого нетерминала
        //Иначе добавляем этот символ в направляющие символы
        if (IsNonTerminal(*it, rules))
        {
            std::set<std::string> symbols = DefineNonTerminalDirectionSymbols(*it, rules);
            directionSymbols.insert(symbols.begin(), symbols.end());
        }
        else
        {
            directionSymbols.insert(*it);
        }
        // Определяем используется ли еще заданный нетерминал в этом правиле
        it = std::find(it, rule.rightPart.end(), nonTerminalName);
    }
    return directionSymbols;
}

//Нахождение символов, которые находятся после нетерминала в грамматике
std::set<std::string> DefineDirectionSymbolsAfterNonTerminal(const std::string& nonTerminalName, const std::vector<Rule>& rules)
{
    std::set<std::string> directionSymbols;
    //Обход правил в грамматике
    for (const Rule& rule : rules)
    {
        //Опредление символов, которые находятся после вызова нетерминала в правиле
        std::set<std::string> symbols = GetDirectionSymbolsAfterNonTerminal(rule, nonTerminalName, rules);
        directionSymbols.insert(symbols.begin(), symbols.end());
    }

    return directionSymbols;
}

std::set<std::string> GetDirectionSymbolsIfNonterminalInEnd(const Rule& rule, const std::vector<Rule>& rules)
{
    std::set<std::string> directionSymbols;
    // Определение правил, в которых используется заданный нетерминал
    std::vector<Rule> currentRules = GetRulesWithNonterminal(rules, rule.nonTerminal);
    if (rule.hasEnd)
    {
        directionSymbols.insert(END_SYMBOL);
    }
    for (const Rule& r : currentRules)
    {
        //Проверка использования нетерминала в заданном правиле
        if (std::find(rule.rightPart.begin(), rule.rightPart.end(), r.nonTerminal) == rule.rightPart.end())
        {
            //Опредление символов, которые находятся после вызова нетерминала в правиле
            std::set<std::string> symbols = GetDirectionSymbolsAfterNonTerminal(r, rule.nonTerminal, rules);
            directionSymbols.insert(symbols.begin(), symbols.end());
        }
    }
    return directionSymbols;
}

void DefineDirectionSymbols(std::vector<Rule>& rules)
{
    bool hasChanges = false;
    // Обход правил в грамматике
    for (size_t i = 0; i < rules.size(); i++)
    {
        Rule& rule = rules[i];
        //Проверка на то, что правило не имеет элементов
        if (rule.rightPart.size() == 0)
        {
            throw std::logic_error("right part is empty");
        }
        //Проверка на то, что правило пустое
        if (rule.rightPart.size() == 1 && rule.rightPart[0] == EMPTY_SYMBOL)
        {
            //Опредление символов, которые находятся после вызова нетерминала с пустым правилом в грамматике
            std::set<std::string> directionSymbols = DefineDirectionSymbolsAfterNonTerminal(rule.nonTerminal, rules);
            size_t sizeBefore = rule.directionSymbols.size();
            rule.directionSymbols.insert(directionSymbols.begin(), directionSymbols.end());
            hasChanges = sizeBefore == rule.directionSymbols.size() && !hasChanges ? false : true;
            continue;
        }
        // Проверка первого элемента правила на нетерминал
        if (IsNonTerminal(rule.rightPart[0], rules))
        {
            // Нахождение направляющих символов первого элемента правила
            std::set<std::string> directionSymbols = DefineNonTerminalDirectionSymbols(rule.rightPart[0], rules);
            size_t sizeBefore = rule.directionSymbols.size();
            rule.directionSymbols.insert(directionSymbols.begin(), directionSymbols.end());
            hasChanges = sizeBefore == rule.directionSymbols.size() && !hasChanges ? false : true;
            continue;
        }

        // Если первый элемент не является нетерминалом, то он является направляющим символом
        size_t sizeBefore = rule.directionSymbols.size();
        rules[i].directionSymbols.insert(rule.rightPart[0]);
        hasChanges = sizeBefore == rule.directionSymbols.size() && !hasChanges ? false : true;
    }

    // Если найдены новые направляющие символы для нетерминалов в грамматике,
    //то производится повторное нахождение направляющих символов
    if (hasChanges)
    {
        DefineDirectionSymbols(rules);
    }
}